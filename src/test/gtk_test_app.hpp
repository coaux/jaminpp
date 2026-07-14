#pragma once

#include <iostream>
#include <gtkmm.h>
#include <catch2/catch_session.hpp>
#include <test/gtest_harness.hpp>

/// @brief Test harness as a Gtk::Application
///
/// This application will run tests within the Gio event loop
///
class GtkTestApp final : public GTestHarness<Gtk::Application> {
public:
    GtkTestApp(Catch::Session* ses)
        : GTestHarness<Gtk::Application>(ses) {}
};

/// @brief main test function
///
/// For Catch2 `--list-tests` and similar `--list-%` args, this will
/// return without running the `Gio::Application`.
///
/// For test cases, this will run the tests within a Gio event loop.
///
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
    app.run();
    return app.getReturn();
}
