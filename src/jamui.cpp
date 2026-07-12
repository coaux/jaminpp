
#include "jamui.hpp"

extern "C" {
#include "jaminpp_resource.h"
}

namespace jamui {

void JamUI::init() {
    g_resources_register(jaminpp_get_resource());
}

JamUI::JamUI()
    : m_builder(Gtk::Builder::create_from_resource(JAMINPP_UI_PATH)) {}

Glib::ustring const JamUI::main_window_id     = "window1";
Glib::ustring const JamUI::presets_window_id  = "window3";
Glib::ustring const JamUI::multiout_window_id = "window4";


}  // namespace jamui
