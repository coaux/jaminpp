#pragma once

#include <giomm.h>
#include <catch2/catch_session.hpp>
#include <giomm/application.h>
#include <glibmm/main.h>

/// @brief Test harness for a Gio::Application
///
/// @tparm Base Implementing type for the Gio::Application
///
/// The caller is assumed to have both registered and activated the
/// application, after construction of the test harness and before
/// calling `run()` on the instance.
///
template <typename Base>
class GTestHarness : public Base {

    Catch::Session* ses;
    int             rs;

public:
    /// @brief initialize the application and store the `Catch::Session`
    /// pointer. The caller is assumed to retain ownership of the pointer.
    ///
    /// The application will be run as a Gio service. For certain `Base`
    /// types, this may require the availability of Gdk display.
    ///
    GTestHarness(Catch::Session* ses)
        : Base()
        , ses(ses)
        , rs(-1) {
#if GTK_MAJOR_VERSION < 4
        Base::set_flags(Gio::APPLICATION_HANDLES_COMMAND_LINE
                        | Gio::APPLICATION_HANDLES_OPEN
                        | Gio::APPLICATION_SEND_ENVIRONMENT
                        | Gio::APPLICATION_NON_UNIQUE
                        | Gio::APPLICATION_IS_SERVICE);
#else
        Base::set_flags(Gio::Application::Flags::HANDLES_COMMAND_LINE
                        | Gio::Application::Flags::HANDLES_OPEN
                        | Gio::Application::Flags::SEND_ENVIRONMENT
                        | Gio::Application::Flags::NON_UNIQUE
                        | Gio::Application::Flags::IS_SERVICE);
#endif
    };

    /// @brief return any value stored for the test session, or `-1`
    /// if no value was stored.
    int          getReturn() const { return rs; }

    /// @brief ensure that the test session will run within the event
    /// loop for the default Glib::MainContext
    virtual void on_activate() override {
        auto ctx = Glib::MainContext::get_default();
        ctx->signal_idle().connect_once([this] {
            rs = ses->run();
            Base::quit();
        });
    }
};
