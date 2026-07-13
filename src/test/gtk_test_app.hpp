
#include <giomm/application.h>
#include <iostream>
#include <gtkmm.h>
#include <catch2/catch_session.hpp>

class GtkTestApp final : public Gtk::Application {

    Catch::Session* ses;

public:
    GtkTestApp(Catch::Session* ses)
        : Gtk::Application()
        , ses(ses) {
#if GTK_MAJOR_VERSION == 3
        set_flags(Gio::APPLICATION_HANDLES_COMMAND_LINE
                  | Gio::APPLICATION_HANDLES_OPEN
                  | Gio::APPLICATION_SEND_ENVIRONMENT
                  | Gio::APPLICATION_NON_UNIQUE);
#else
        set_flags(Gio::Application::Flags::HANDLES_COMMAND_LINE
                  | Gio::Application::Flags::HANDLES_OPEN
                  | Gio::Application::Flags::SEND_ENVIRONMENT
                  | Gio::Application::Flags::NON_UNIQUE);
#endif
    };

    int run(int argc, char** argv) {
        int rs = ses->run();
        if (rs) { return rs; }
        Gtk::Application::run(argc, argv);
        return rs;
    }
};

// NOLINTNEXTLINE(misc-definitions-in-headers)
int main(int argc, char* argv[]) {
    std::cerr << "Test environment: Gtk" << GTK_MAJOR_VERSION << std::endl;

    Catch::Session ses{};
    int            rs;

    if ((rs = ses.applyCommandLine(argc, argv))) { return rs; }

    GtkTestApp app(&ses);
    app.register_application();

    return app.run(argc, argv);
}
