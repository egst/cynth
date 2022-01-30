#pragma once

#include <windows.h>

#undef interface

#include <algorithm>
#include <array>
#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <iterator>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <string>
#include <type_traits>
#include <vector>

#include "asio.hpp"
#include "asiodrivers.h"

#include "driver/asio/errors.hpp"
#include "driver/asio/types.hpp"
#include "driver/asio/write.hpp"
#include "driver/interface.hpp"

// TMP
#include "debug.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

// TODO: Is this really the way to do this?
// (ASIO is missing these declarations in the headers.)
extern AsioDrivers * asioDrivers;
bool loadAsioDriver (char * name);

namespace cynth::driver::asio {

    // TODO: Change all the remaining names to match the local naming condition.

    class Controller {
    public:
        using Status = asio::Status;

        static std::string message (Status e) {
            return errorMessage(e);
        }

        static Status init () {
            Status result;
            result = choseDriver();     if (result != Status::ok) return result;
            result = initDriver();      if (result != Status::ok) return result;
            result = getChannelCount(); if (result != Status::ok) return result;
            result = getBufferSizes();  if (result != Status::ok) return result;
            result = getSampleRate();   if (result != Status::ok) return result;
            checkOutreadyOptimization();
            configureChannels();
            result = createBuffers();   if (result != Status::ok) return result;
            result = getChannelInfo();  if (result != Status::ok) return result;
            result = getLatencies();    if (result != Status::ok) return result;
            initialized_ = true;
            return Status::ok;
        }

        static Status start () {
            return startLoop();
        }

        static void stop () { requestStop(); }

        static double sampleRate () noexcept { return sample_rate_; }

        static bool initialized () noexcept { return initialized_; }

    private:
        enum class Stop { full, reset, srateReset };

        static Stop requestedStop () { return requested_stop_; }

        static std::unique_lock<std::mutex>        getStopGuard            () { return std::unique_lock<std::mutex>{stop_mutex_};                               }
        static std::unique_lock<std::shared_mutex> getOperationGuard       () { return std::unique_lock<std::shared_mutex>{operation_mutex_};                   }
        static std::shared_lock<std::shared_mutex> getSharedOperationGuard () { return std::shared_lock<std::shared_mutex>{operation_mutex_, std::try_to_lock}; }

        static void wait (std::unique_lock<std::mutex> & guard) { stop_signal_.wait(guard); }

        static Status startLoop () {
            Status result;
            while (true) {
                result = startDriver();
                if (result != Status::ok) return result;

                auto stop_guard = getStopGuard();
                wait(stop_guard);
                auto operation_guard = getOperationGuard();

                switch (requestedStop()) {
                case Stop::reset:
                    result = exitDriver();
                    if (result != Status::ok) return result;
                    init();
                    continue;
                case Stop::srateReset: // TODO
                case Stop::full: default:
                    result = exitDriver();
                    if (result != Status::ok) return result;
                    break;
                }
                break;
            }
            return Status::ok;
        }

        static Status initDriver () {
            return status(ASIOInit(&driver_info_));
        }

        static Status startDriver () {
            return status(ASIOStart());
        }

        static Status stopDriver () {
            initialized_ = false;
            return status(ASIOStop());
        }

        static Status exitDriver () {
            initialized_ = false;
            Status result;
            result = stopDriver();
            if (result != Status::ok) return result;
            result = status(ASIODisposeBuffers());
            if (result != Status::ok) return result;
            return status(ASIOExit());
        }

        static std::vector<std::string> listDrivers () {
            using names_t    = std::array<char [max_driver_name_size_], max_driver_count_>;
            using pointers_t = std::array<char *, max_driver_count_>;
            using result_t   = std::vector<std::string>;
            names_t     names;
            pointers_t  pointers;
            result_t    result;
            AsioDrivers drivers;
            std::transform(names.begin(), names.end(), pointers.begin(), [] (auto & e) -> char * { return e; });
            std::size_t const count = drivers.getDriverNames(pointers.data(), max_driver_count_);
            std::transform(names.begin(), names.begin() + count, std::back_inserter(result), [] (auto & e) -> std::string { return {e}; });
            return result;
        }

        static AsioDrivers * asioDrivers () {
            return ::asioDrivers;
        }

        static bool loadDriver (std::string name) {
            return loadAsioDriver(name.data());
        }

        static Status choseDriver () {
            auto const driver_names = listDrivers();
            std::size_t chosen = 0; // TODO
            if (!loadDriver(driver_names[chosen]))
                return Status::failedSetup;
            if constexpr (debug)
                std::cout << "device: " << driver_names[chosen] << '\n';
            return Status::ok;
        }

        static Status getChannelCount () {
            long i, o;
            auto result = status(ASIOGetChannels(&i, &o));
            if (result != Status::ok)
                return result;
            input_channel_count_  = i;
            output_channel_count_ = o;
            return Status::ok;
        }

        static Status getBufferSizes () {
            long min, max, pref, gran;
            auto result = status(ASIOGetBufferSize(&min, &max, &pref, &gran));
            if (result != Status::ok)
                return result;
            min_buffer_size_          = min;
            max_buffer_size_          = max;
            preferred_buffer_size_    = pref;
            buffer_sizes_granularity_ = gran;
            return Status::ok;
        }

        static Status getSampleRate () {
            double rate;
            auto result = status(ASIOGetSampleRate(reinterpret_cast<ASIOSampleRate*>(&rate)));
            if (result != Status::ok)
                return result;
            sample_rate_ = rate;
            std::cout << "sample rate: " << rate << '\n';
            return Status::ok;
            // TODO: ASIOCanSampleRate, ASIOSetSampleRate when the sample rate is not stored in the driver.
        }

        static void checkOutreadyOptimization () {
            outready_optimization_ = ASIOOutputReady() == ASE_OK;
        }

        static void configureChannels () {
            input_buffer_count_ = std::min(input_channel_count_, max_input_channel_count_);
            for(std::size_t i = 0; i < input_buffer_count_; ++i) {
                auto& buffer_info      = buffer_infos_[i];
                buffer_info.isInput    = ASIOTrue;
                buffer_info.channelNum = i;
                buffer_info.buffers[0] = 0;
                buffer_info.buffers[1] = 0;
            }

            output_buffer_count_ = std::min(output_channel_count_, max_output_channel_count_);
            for(std::size_t i = 0; i < output_buffer_count_; ++i) {
                auto& buffer_info      = buffer_infos_[i + input_buffer_count_];
                buffer_info.isInput    = ASIOFalse;
                buffer_info.channelNum = i;
                buffer_info.buffers[0] = 0;
                buffer_info.buffers[1] = 0;
            }
        }

        static Status createBuffers () {
            return status(ASIOCreateBuffers (
                buffer_infos_.data(),
                input_channel_count_ + output_channel_count_,
                preferred_buffer_size_,
                &callbacks_
            ));
        }

        static Status getChannelInfo () {
            for (std::size_t i = 0; i < buffer_count(); ++i) {
                auto& buffer_info    = buffer_infos_[i];
                auto& channel_info   = channel_infos_[i];
                channel_info.channel = buffer_info.channelNum;
                channel_info.isInput = buffer_info.isInput;
                auto result = status(ASIOGetChannelInfo(&channel_info));
                if (result != Status::ok)
                    return result;
            }
            return Status::ok;
        }

        static Status getLatencies () {
            /*
             *  From the docs:
             *  input latency is the age of the first sample in the currently returned audio block
             *  output latency is the time the first sample in the currently returned audio block requires to get to the output
             */
            long in, out;
            auto result = status(ASIOGetLatencies(&in, &out));
            if (result != Status::ok)
                return result;
            input_latency_  = in;
            output_latency_ = out;
            return Status::ok;
        }

        static void requestStop (Stop requested = Stop::full) {
            requested_stop_ = requested;
            stop_signal_.notify_all();
        }

        static void bufferSwitch (long index, ASIOBool directProcess) {
            ASIOTime time;
            if (status(ASIOGetSamplePosition(&time.timeInfo.samplePosition, &time.timeInfo.systemTime)) == Status::ok)
                time.timeInfo.flags = AsioTimeInfoFlags::kSystemTimeValid | AsioTimeInfoFlags::kSamplePositionValid;

            bufferSwitchTimeInfo(&time, index, directProcess);
        }

        // TODO: Sample rate change not implemented yet.
        // Check that a full stop would be requested in this case.
        static void sampleRateChanged ([[maybe_unused]] ASIOSampleRate sRate) {
            auto guard = getSharedOperationGuard();
            if (!guard.owns_lock()) return;

            /*
             *  From the docs:
             *  Do whatever you need to do if the sample rate changed.
             *  Usually this only happens during external sync.
             *  Audio processing is not stopped by the driver, actual sample rate
             *  might not have even changed, maybe only the sample rate status of an
             *  AES/EBU or S/PDIF digital input at the audio device.
             *  You might have to update time/sample related conversion routines, etc.
             */

            requestStop(Stop::srateReset);
        }

        static long asioMessages (long selector, long value, [[maybe_unused]] void* message, [[maybe_unused]] double* opt) {
            auto guard = getSharedOperationGuard();
            if (!guard.owns_lock()) return 0;

            // This was just coppied from the docs.
            // The messages, that are not implemented perform a full stop of the driver.
            switch (selector) {
            case kAsioSelectorSupported:
                if (value == kAsioResetRequest     ||
                    value == kAsioEngineVersion    ||
                    value == kAsioResyncRequest    ||
                    value == kAsioLatenciesChanged ||
                    value == kAsioSupportsTimeInfo ||
                    value == kAsioSupportsTimeCode ||
                    value == kAsioSupportsInputMonitor) {
                    requestStop();
                    return 1;
                }
                break;
            case kAsioResetRequest:
                /*
                 *  From the docs:
                 *  defer the task and perform the reset of the driver during the next "safe" situation
                 *  You cannot reset the driver right now, as this code is called from the driver.
                 *  Reset the driver is done by completely destruct is. I.e. ASIOStop(), ASIODisposeBuffers(), Destruction
                 *  Afterwards you initialize the driver again.
                 */
                requestStop(Stop::reset);
                return 1;
            case kAsioResyncRequest:
                /*
                 *  From the docs:
                 *  This informs the application, that the driver encountered some non fatal data loss.
                 *  It is used for synchronization purposes of different media.
                 *  Added mainly to work around the Win16Mutex problems in Windows 95/98 with the
                 *  Windows Multimedia system, which could loose data because the Mutex was hold too long
                 *  by another thread.
                 *  However a driver can issue it in other situations, too.
                 */
                requestStop();
                return 1;
            case kAsioLatenciesChanged:
                /*
                 *  From the docs:
                 *  This will inform the host application that the drivers were latencies changed.
                 *  Beware, it this does not mean that the buffer sizes have changed!
                 *  You might need to update internal delay data.
                 */
                requestStop();
                return 1;
            case kAsioEngineVersion:
                /*
                 *  From the docs:
                 *  return the supported ASIO version of the host application
                 *  If a host applications does not implement this selector, ASIO 1.0 is assumed
                 *  by the driver
                 */
                requestStop();
                return 2;
            case kAsioSupportsTimeInfo:
                /*
                 *  From the docs:
                 *  informs the driver wether the asioCallbacks.bufferSwitchTimeInfo() callback
                 *  is supported.
                 *  For compatibility with ASIO 1.0 drivers the host application should always support
                 *  the "old" bufferSwitch method, too.
                 */
                //stop_type = full;
                //stop_signal.notify_all();
                return 1;
            case kAsioSupportsTimeCode:
                /*
                 *  From the docs:
                 *  informs the driver wether application is interested in time code info.
                 *  If an application does not need to know about time code, the driver has less work
                 *  to do.
                 */
                requestStop();
                return 0;
            }
            return 0;
        }

        static ASIOTime * bufferSwitchTimeInfo (ASIOTime * timePtr, long index, [[maybe_unused]] ASIOBool directProcess) {
            // TODO: Docs, page 8: First few call to bufferSwitch should be ignored.

            auto guard = getSharedOperationGuard();
            if (!guard.owns_lock())
                return 0;

            // From the docs:
            //asio_time_ = *timePtr;

            // From the docs:
            //asio_time_.timeInfo.systemTime

            /*
            sample_pos_ns_ = timePtr->timeInfo.flags & kSystemTimeValid
                ? nativeInt64(timePtr->timeInfo.systemTime) : 0;
            time_code_pos_ = timePtr->timeCode.flags & kTcValid
                ? nativeInt64(timePtr->timeCode.timeCodeSamples) : 0;
            */
            sample_pos_ = timePtr->timeInfo.flags & kSamplePositionValid
                ? nativeInt64(timePtr->timeInfo.samplePosition) : 0;

            // From the docs:
            //system_reference_time_ = timeGetTime();

            auto buffer_size = preferred_buffer_size_;

            for (std::size_t j = 0; j < buffer_size; ++j) {
                Time time = sample_pos_ + j;
                Rack::eval(time);

                /*
                double offset  = static_cast<double>(time) / 41000.0;
                double amp     = 1.0;
                double freq    = 440.0;
                //Sample sample = amp * (2 * std::fmod(freq * offset, 1) - 1);
                Sample sample = amp * std::sin((offset * 2 * 3.1415926 * freq));
                */

                for (std::size_t i = input_buffer_count_; i < buffer_count(); ++i) {
                    std::size_t chan = i - input_buffer_count_;
                    Sample sample = chan == 0
                        ? Rack::outChan1(time)
                        : Rack::outChan2(time);
                    auto const & buffer_info  = buffer_infos_[i];
                    auto const & channel_info = channel_infos_[i];

                    auto result = write(channel_info.type, buffer_info.buffers[index], j, 0.8 * sample);
                    if (result != Status::ok) return 0; // TODO: How to notify about the error?
                    // Actually, the write operation doesn't really have to fail here,
                    // since the only point of failure is a potentially unsupported sample type, which should have been checked in advance.
                }
            }

            // From the docs:
            if (outready_optimization_)
                ASIOOutputReady();// >> util::ase_handler{"ASIOOutputReady"};

            return 0;
        }

        // Note: The numeric types below correspond to the types used in ASIO and Windows libraries.

        inline static bool initialized_ = false;

        constexpr inline static std::size_t
            max_driver_count_     = 16,
            max_driver_name_size_ = 32;

        inline static ASIODriverInfo driver_info_;

        inline static std::size_t
            input_channel_count_,
            output_channel_count_;

        inline static std::size_t
            min_buffer_size_,
            max_buffer_size_,
            preferred_buffer_size_,
            buffer_sizes_granularity_;

        inline static double sample_rate_;

        inline static bool outready_optimization_;

        inline static ASIOCallbacks callbacks_ = {
            bufferSwitch,
            sampleRateChanged,
            asioMessages,
            bufferSwitchTimeInfo
        };

        constexpr inline static const std::size_t
            max_input_channel_count_  = 16,
            max_output_channel_count_ = 16,
            max_channel_count_        = max_input_channel_count_ + max_output_channel_count_;

        inline static std::size_t
            input_buffer_count_,
            output_buffer_count_;

        static std::size_t buffer_count () { return input_buffer_count_ + output_buffer_count_; }

        inline static std::array<ASIOBufferInfo,  max_channel_count_> buffer_infos_;
        inline static std::array<ASIOChannelInfo, max_channel_count_> channel_infos_;

        inline static long
            input_latency_,
            output_latency_;

        inline static ASIOTime asio_time_;

        inline static std::int64_t sample_pos_; // sample_pos_ns_, time_code_pos_;

        //inline static std::int32_t system_reference_time_;

        inline static std::mutex              stop_mutex_;
        inline static std::shared_mutex       operation_mutex_;
        inline static std::condition_variable stop_signal_;
        inline static std::atomic<Stop>       requested_stop_;

        constexpr static bool debug = true;
    };

}
