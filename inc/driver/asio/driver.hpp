#pragma once

#ifdef WIN32
#warning bar
#endif
#ifdef WIN64
#warning foo
#endif
#ifdef _WIN32
#warning foo
#endif
#ifdef _WIN64
#warning foo
#endif
#ifdef __WIN32
#warning foo
#endif
#ifdef __WIN64
#warning foo
#endif
#ifdef __WIN32__
#warning foo
#endif
#ifdef __WIN64__
#warning foo
#endif
#ifdef __MINGW32
#warning foo
#endif
#ifdef __MINGW64
#warning foo
#endif
#ifdef __MINGW32__
#warning foo
#endif
#ifdef __MINGW64__
#warning foo
#endif
#ifdef UNIX
#warning foo
#endif
#ifdef unix
#warning foo
#endif
#ifdef WINNT
#warning foo
#endif
#ifdef __WINNT
#warning foo
#endif
#ifdef __WINNT__
#warning foo
#endif

#include <windows.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <iterator>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <vector>
//#include <thread>

#include "debug.hpp"

#include "asio.h"
#include "asiodrivers.h"

#include "driver/asio/errors.hpp"

#include "debug.hpp"

namespace cynth::asio {

    class driver {
    public:
        static void init () {
            choseDriver();
            asioInit();
            getChannelCount();
            getBufferSizes();
            getSampleRate();
            checkOutreadyOptimization();
            configureChannels();
            createBuffers();
            getChannelInfo();
            getLatencies();
            initialized_ = true;
        }

        static void start () {
            // TODO
            //std::thread{startLoop}.detach();
            startLoop();
        }

        static void stop () { requestStop(); }

        static std::size_t sampleRate () noexcept { return sample_rate_; }

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
                result = status(ASIOStart());
                if (result != Status::ok) return result;

                auto stop_guard = getStopGuard();
                wait(stop_guard);
                auto operation_guard = getOperationGuard();

                switch (requestedStop()) {
                case Stop::reset:
                    result = status(ASIOStop());
                    if (result != Status::ok) return result;
                    result = status(ASIODisposeBuffers());
                    if (result != Status::ok) return result;
                    result = status(ASIOExit());
                    if (result != Status::ok) return result;
                    initialized_ = false;
                    init();
                    continue;
                case Stop::srateReset:
                    // TODO
                    initialized_ = false;
                    init();
                    continue;
                case Stop::full: default:
                    break;
                }

                result = status(ASIOStop());
                if (result != Status::ok) return result;
                initialized_ = false;
                break;
            }
            return Status::ok;
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

        static AsioDrivers & asio_drivers () {
            ESL_INSPECT(asioDrivers);
            if (!asioDrivers)
                throw util::asio_exception{"asioDrivers not initialized"};
            return *asioDrivers;
        }

        static bool load_driver (std::string name) { return loadAsioDriver(name.data());  }

        static void choseDriver () {
            auto const driver_names = listDrivers();
            std::size_t chosen = 0; // TODO
            if (!driver::load_driver(driver_names[chosen]))
                throw util::asio_exception{"Unable to load the chosen driver."};
            //std::cout << driver_names[chosen] << '\n';
        }

        static void asioInit () {
            ASIOInit(&driver_info_) >> util::ase_handler{"ASIOInit"};
        }

        static void getChannelCount () {
            long i, o;
            ASIOGetChannels(&i, &o) >> util::ase_handler{"ASIOGetChannels"};
            input_channel_count_  = i;
            output_channel_count_ = o;
        }

        static void getBufferSizes () {
            long min, max, pref, gran;
            ASIOGetBufferSize(&min, &max, &pref, &gran) >> util::ase_handler{"ASIOGetBufferSize"};
            min_buffer_size_          = min;
            max_buffer_size_          = max;
            preferred_buffer_size_    = pref;
            buffer_sizes_granularity_ = gran;
        }

        static void getSampleRate () {
            double rate;
            ASIOGetSampleRate(reinterpret_cast<ASIOSampleRate*>(&rate)) >> util::ase_handler{"ASIOGetSampleRate"};
            sample_rate_ = rate;
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

        static void createBuffers () {
            ASIOCreateBuffers (
                buffer_infos_.data(),
                input_channel_count_ + output_channel_count_,
                preferred_buffer_size_,
                &callbacks_
            ) >> util::ase_handler{"ASIOCreateBuffers"};
        }

        static void getChannelInfo () {
            for (std::size_t i = 0; i < buffer_count(); ++i) {
                auto& buffer_info    = buffer_infos_[i];
                auto& channel_info   = channel_infos_[i];
                channel_info.channel = buffer_info.channelNum;
                channel_info.isInput = buffer_info.isInput;
                ASIOGetChannelInfo(&channel_info) >> util::ase_handler{"ASIOGetChannelInfo"};
            }
        }

        static void getLatencies () {
            /* From the docs:
               input latency is the age of the first sample in the currently returned audio block
               output latency is the time the first sample in the currently returned audio block requires to get to the output */
            long in, out;
            ASIOGetLatencies(&in, &out) >> util::ase_handler{"ASIOGetLatencies"};
            input_latency_  = in;
            output_latency_ = out;
        }

        static void requestStop (Stop requested = Stop::full) {
            requested_stop_ = requested;
            stop_signal_.notify_all();
        }

        static void bufferSwitch (long index, ASIOBool directProcess) {
            ASIOTime time;
            if (ASIOGetSamplePosition(&time.timeInfo.samplePosition, &time.timeInfo.systemTime) == ASE_OK)
                time.timeInfo.flags = AsioTimeInfoFlags::kSystemTimeValid | AsioTimeInfoFlags::kSamplePositionValid;

            driver::bufferSwitchTimeInfo (&time, index, directProcess);
        }

        static void sampleRateChanged ([[maybe_unused]] ASIOSampleRate sRate) {
            auto guard = getSharedOperationGuard();
            if (!guard.owns_lock()) return;

            /* From the docs:
               Do whatever you need to do if the sample rate changed.
               Usually this only happens during external sync.
               Audio processing is not stopped by the driver, actual sample rate
               might not have even changed, maybe only the sample rate status of an
               AES/EBU or S/PDIF digital input at the audio device.
               You might have to update time/sample related conversion routines, etc. */

            driver::requestStop(Stop::srateReset);
        }

        static long asioMessages (long selector, long value, [[maybe_unused]] void* message, [[maybe_unused]] double* opt) {
            auto guard = getSharedOperationGuard();
            if (!guard.owns_lock()) return 0;

            // This was just coppied from the docs.
            // The messages, that are not implemented perform a full stop of the driver.
            switch (selector) {
            case kAsioSelectorSupported:
                if(value == kAsioResetRequest
                        || value == kAsioEngineVersion
                        || value == kAsioResyncRequest
                        || value == kAsioLatenciesChanged
                        || value == kAsioSupportsTimeInfo
                        || value == kAsioSupportsTimeCode
                        || value == kAsioSupportsInputMonitor) {
                    requestStop();
                    return 1;
                }
                break;
            case kAsioResetRequest:
                /* From the docs:
                   defer the task and perform the reset of the driver during the next "safe" situation
                   You cannot reset the driver right now, as this code is called from the driver.
                   Reset the driver is done by completely destruct is. I.e. ASIOStop(), ASIODisposeBuffers(), Destruction
                   Afterwards you initialize the driver again. */
                requestStop(Stop::reset);
                return 1;
            case kAsioResyncRequest:
                /* From the docs:
                   This informs the application, that the driver encountered some non fatal data loss.
                   It is used for synchronization purposes of different media.
                   Added mainly to work around the Win16Mutex problems in Windows 95/98 with the
                   Windows Multimedia system, which could loose data because the Mutex was hold too long
                   by another thread.
                   However a driver can issue it in other situations, too. */
                requestStop();
                return 1;
            case kAsioLatenciesChanged:
                /* From the docs:
                   This will inform the host application that the drivers were latencies changed.
                   Beware, it this does not mean that the buffer sizes have changed!
                   You might need to update internal delay data. */
                requestStop();
                return 1;
            case kAsioEngineVersion:
                /* From the docs:
                   return the supported ASIO version of the host application
                   If a host applications does not implement this selector, ASIO 1.0 is assumed
                   by the driver */
                requestStop();
                return 2;
            case kAsioSupportsTimeInfo:
                /* From the docs:
                   informs the driver wether the asioCallbacks.bufferSwitchTimeInfo() callback
                   is supported.
                   For compatibility with ASIO 1.0 drivers the host application should always support
                   the "old" bufferSwitch method, too. */
                /*driver::stop_type = full;
                  driver::stop_signal.notify_all();*/
                return 1;
            case kAsioSupportsTimeCode:
                /* From the docs:
                   informs the driver wether application is interested in time code info.
                   If an application does not need to know about time code, the driver has less work
                   to do. */
                requestStop();
                return 0;
            }
            return 0;
        }

        static ASIOTime* bufferSwitchTimeInfo (ASIOTime* timePtr, long index, [[maybe_unused]] ASIOBool directProcess) {
            // TODO: Docs, page 8: First few call to bufferSwitch should be ignored.

            auto guard = getSharedOperationGuard();
            if (!guard.owns_lock())
                return 0;

            // From the docs:
            asio_time_ = *timePtr;

            // From the docs:
            driver::sample_pos_ns_ = asio_time_.timeInfo.flags & kSystemTimeValid
                ? util::native_double(asio_time_.timeInfo.systemTime) : 0;
            driver::sample_pos_ = asio_time_.timeInfo.flags & kSamplePositionValid
                ? util::native_int64(asio_time_.timeInfo.samplePosition) : 0;
            driver::time_code_pos_ = asio_time_.timeCode.flags & kTcValid
                ? util::native_int64(asio_time_.timeCode.timeCodeSamples) : 0;

            // From the docs:
            driver::system_reference_time_ = timeGetTime(); // TODO: From which header is this?

            auto buffer_size = preferred_buffer_size_;

            for (std::size_t j = 0; j < buffer_size; ++j) {
                integral const time   = sample_pos_ + j;
                floating const sample = cynth::util::driver<driver>::output_signal(time);
                for (std::size_t i = input_buffer_count_; i < buffer_count(); ++i) {
                    auto const & buffer_info  = buffer_infos_[i];
                    auto const & channel_info = channel_infos_[i];
                    util::write(channel_info.type, buffer_info.buffers[index], j, 0.8 * sample);
                }
            }

            // From the docs:
            if (outready_optimization_)
                ASIOOutputReady();// >> util::ase_handler{"ASIOOutputReady"};

            return 0;
        }

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
            preferred_buffer_size_;
        inline static std::size_t buffer_sizes_granularity_;

        inline static floating sample_rate_;

        inline static bool outready_optimization_;

        inline static ASIOCallbacks callbacks_ = {
            driver::bufferSwitch,
            driver::sampleRateChanged,
            driver::asioMessages,
            driver::bufferSwitchTimeInfo
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

        inline static std::size_t
            input_latency_,
            output_latency_;

        inline static ASIOTime asio_time_;

        inline static floating sample_pos_ns_;
        inline static std::size_t
            sample_pos_,
            time_code_pos_;

        inline static std::size_t system_reference_time_;

        inline static std::mutex              stop_mutex_;
        inline static std::shared_mutex       operation_mutex_;
        inline static std::condition_variable stop_signal_;
        inline static std::atomic<Stop>       requested_stop_;
    };
