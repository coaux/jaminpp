#pragma once

#include <giomm.h>
#include <catch2/catch_session.hpp>
#include <giomm/application.h>
#include <glibmm/main.h>

template <typename Base>
class GTestHarness : public Base {

    Catch::Session* ses;
    int             rs;

public:
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

    int          getReturn() const { return rs; }

    virtual void on_activate() override {
        auto ctx = Glib::MainContext::get_default();
        ctx->signal_idle().connect_once([this] {
            rs = ses->run();
            Base::quit();
        });
    }
};
