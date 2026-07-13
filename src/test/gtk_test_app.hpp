#pragma once

#include <iostream>
#include <gtkmm.h>
#include <catch2/catch_session.hpp>
#include <test/gtest_harness.hpp>

class GtkTestApp final : public GTestHarness<Gtk::Application> {
public:
    GtkTestApp(Catch::Session* ses)
        : GTestHarness<Gtk::Application>(ses) {}
};

// NOLINTNEXTLINE(misc-definitions-in-headers)
int main(int argc, char* argv[]) {
    std::cerr << "Test environment: Gtk" << GTK_MAJOR_VERSION << std::endl;

    Catch::Session ses{};
    int            rs;

    if ((rs = ses.applyCommandLine(argc, argv))) { return rs; }

    if (ses.config().listTests() || ses.config().listTags()
        || ses.config().listListeners() || ses.config().listReporters()) {
        return ses.run();
    }

    GtkTestApp app(&ses);
    app.register_application();
    app.activate();
    app.run(argc, argv);
    return app.getReturn();
}
