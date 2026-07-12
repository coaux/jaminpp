
#include <glibmm/refptr.h>
#include <iostream>
#ifndef JAMINPP_DOT_RESOURCE_NAME
#    define JAMINPP_DOT_RESOURCE_NAME "io.github.coaux.jaminpp"
#endif

#include <gtkmm.h>
#include "jamui.hpp"

using namespace jamui;

int main(int argc, char* argv[]) {

    auto app =
          Gtk::Application::create(JAMINPP_DOT_RESOURCE_NAME);

    JamUI::init();

    Glib::RefPtr<JamUI> ui{};

    try {
        Glib::RefPtr<JamUI> real_ui(new JamUI());
        ui.swap(real_ui);
    } catch (Glib::Error const& err) {
        std::cerr << "Error creating JamUI: " << err.what() << std::endl;
        return 1;
    }

    try {
        MainWindow* wdw = ui->make_main_window();
        wdw->show();
    }  catch (Glib::Error const& err) {
        std::cerr << "Error creating MainWindow: " << err.what() << std::endl;
        return 1;
    }

   return app->run(argc, argv);
}
