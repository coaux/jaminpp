#pragma once

#ifndef JAMINPP_UI_PATH
#    define JAMINPP_UI_PATH "/io/github/coaux/jaminpp/ui/src/jam.ui"
#endif

#include <gtkmm.h>

// extern "C" {
// #include "gtkmeter.h"
// #include "gtkmeterscale.h"
// }

namespace jamui {

using BuilderPtr = Glib::RefPtr<Gtk::Builder>;

class MainWindow : public Gtk::ApplicationWindow {

public:
    MainWindow(BaseObjectType* obj, BuilderPtr const& builder)
        : Gtk::ApplicationWindow(obj) {}
};

template <typename Impl>
class BuildableWindow : public Gtk::Window {
public:
    BuildableWindow(BaseObjectType* obj, BuilderPtr const& builder)
        : Gtk::Window(obj) {}
};

class PrefsWindow : public BuildableWindow<PrefsWindow> {
public:
    using BuildableWindow<PrefsWindow>::BuildableWindow;
};

class MultiOutWindow : public BuildableWindow<MultiOutWindow> {
public:
    using BuildableWindow<MultiOutWindow>::BuildableWindow;
};

class JamUI {

    Glib::RefPtr<Gtk::Builder> m_builder;

    static Glib::ustring const main_window_id;
    static Glib::ustring const presets_window_id;
    static Glib::ustring const multiout_window_id;

    template <typename T, typename... Arg>
    T* derive(Glib::ustring const& id, Arg&&... arg) {
        // using the builder API for gtkmm-3.0
        T* ob{nullptr};
        m_builder->get_widget_derived<T>(id, ob, std::forward<Arg>(arg)...);
        return ob;
    }

public:
    static void init();

    JamUI();

    MainWindow* make_main_window() {
        return derive<MainWindow>(JamUI::main_window_id);
    }

    Gtk::Window* make_presets_window() {
        return derive<PrefsWindow>(JamUI::presets_window_id);
    }

    Gtk::Window* make_multiout_window() {
        return derive<MultiOutWindow>(JamUI::multiout_window_id);
    }
};


}  // namespace jamui
