#pragma once

#include <cstddef>
#include <cstdio>
#include <functional>

#include "AppCore/App.h"
#include "AppCore/JSHelpers.h"
#include "AppCore/Overlay.h"
#include "AppCore/Window.h"

#include "config.hpp"
#include "controls.hpp"

namespace cynth {

    struct Listener: ultralight::LoadListener {
        virtual ~Listener () {}

        constexpr static bool log = true;

        void print (ultralight::JSObject const & thisObject, ultralight::JSArgs const & args) {
            auto message = static_cast<ultralight::String>(args[0].ToString()).utf8().data();
            std::puts(message);
        }

        void setBool (ultralight::JSObject const & thisObject, ultralight::JSArgs const & args) {
            auto name  = static_cast<ultralight::String>(args[0].ToString()).utf8().data();
            auto value = args[1].ToBoolean();
            Controls::boolSet(name, value, log);
        }

        void setInt (ultralight::JSObject const & thisObject, ultralight::JSArgs const & args) {
            auto name  = static_cast<ultralight::String>(args[0].ToString()).utf8().data();
            auto value = static_cast<Integral>(args[1].ToInteger());
            Controls::intSet(name, value, log);
        }

        ultralight::JSValue getBool (ultralight::JSObject const & thisObject, ultralight::JSArgs const & args) {
            auto name = static_cast<ultralight::String>(args[0].ToString()).utf8().data();
            return {Controls::boolGet(name)};
        }

        ultralight::JSValue getInt (ultralight::JSObject const & thisObject, ultralight::JSArgs const & args) {
            auto name = static_cast<ultralight::String>(args[0].ToString()).utf8().data();
            return {Controls::intGet(name)};
        }

        virtual void OnDOMReady (ultralight::View * caller, uint64_t, bool, ultralight::String const &) override {
            ultralight::Ref<ultralight::JSContext> context = caller->LockJSContext();
            ultralight::SetJSContext(context.get());

            ultralight::JSObject global = ultralight::JSGlobalObject();

            global["print"] = static_cast<ultralight::JSCallback>(
                std::bind(&Listener::print, this, std::placeholders::_1, std::placeholders::_2)
            );
            global["setInt"] = static_cast<ultralight::JSCallback>(
                std::bind(&Listener::setInt, this, std::placeholders::_1, std::placeholders::_2)
            );
            global["setBool"] = static_cast<ultralight::JSCallback>(
                std::bind(&Listener::setBool, this, std::placeholders::_1, std::placeholders::_2)
            );
            global["getBool"] = static_cast<ultralight::JSCallbackWithRetval>(
                std::bind(&Listener::getBool, this, std::placeholders::_1, std::placeholders::_2)
            );
            global["getInt"] = static_cast<ultralight::JSCallbackWithRetval>(
                std::bind(&Listener::getInt, this, std::placeholders::_1, std::placeholders::_2)
            );
            global["defaultBool"] = ultralight::JSValue{Controls::boolDefault};
            global["defaultInt"]  = ultralight::JSValue{Controls::intDefault};
        }
    };

    struct Gui {

        struct Handle {
            ultralight::Ref<ultralight::App>     app;
            ultralight::Ref<ultralight::Window>  window;
            ultralight::Ref<ultralight::Overlay> overlay;
        };

        inline static Listener listener = {};

        inline static bool initialized () { return ultralight::App::instance(); }

        inline static ultralight::App & app () {
            if (!initialized()) init();
            return *ultralight::App::instance();
        }

        inline static Handle init (
            char const * title = "Cynth",
            std::size_t width  = 900,
            std::size_t height = 600
        ) {
            auto app = ultralight::App::Create();
            auto window = ultralight::Window::Create(
                app->main_monitor(), width, height, false, ultralight::kWindowFlags_Titled
            );
            window->SetTitle(title);
            app->set_window(window);
            auto overlay = ultralight::Overlay::Create(
                window, window->width(), window->height(), 0, 0
            );
            overlay->view()->set_load_listener(&listener);
            overlay->view()->LoadHTML(view());
            return {app, window, overlay};
        }

        inline static void start () {
            app().Run();
        }

        inline static char const * view () {
            return R"(
                <html>
                    <head>

                        <style>
                            * {
                                -webkit-user-select: none;
                            }
                            body { 
                                overflow: hidden;
                                margin: 0;
                                padding: 0;
                                background-color: #e0e3ed;
                                background: linear-gradient(-45deg, #e0e3ed, #f7f9fc);
                                width: 100%;
                                height: 100%;
                                font-family: -apple-system, 'Segoe UI', Ubuntu, Arial, sans-serif;
                            }
                            h2, h3 {
                                margin: 0;
                            }
                            p, li { 
                                font-size: 1em;
                            }
                        </style>

                        <script>
                            try {
                                window.onload = () => {
                                    logger = document.querySelector('#logger')
                                    const log = msg => {
                                        logger.innerHTML += '<br>'
                                        logger.innerHTML += msg
                                    }
                                    document.querySelectorAll('input[type=range]').forEach(knob => {
                                        knob.value = defaultInt
                                        knob.addEventListener('change', () => {
                                            setInt(knob.id, knob.value)
                                            log(`change: ${knob.id} ${knob.value}`)
                                        })
                                    })
                                }
                            } catch (e) {
                                document.write(`Error: ${e}`)
                            }
                        </script>

                    </head>
                    <body>

                        <header>
                            <h2>Cynth GUI Controls</h2>
                        </header>
                        <main>
                            <div class=control>
                                <input type=range id=knob1 min=0 max=100>
                                <input type=range id=knob2 min=0 max=100>
                            </div>
                        </main>
                        <footer id=logger>
                        </footer>

                    </body>
                </html>
            )";
        }

    };

    //inline ultralight::Ref<ultralight::App> Gui::app = ultralight::App::Create();

}
