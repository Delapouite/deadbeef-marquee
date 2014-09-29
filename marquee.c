#include "marquee.h"

static void
marquee_songstarted(ddb_event_track_t *ev) {

}

static int
marquee_message(struct ddb_gtkui_widget_s *w, uint32_t id, uintptr_t ctx, uint32_t p1, uint32_t p2) {

    switch (id) {
    case DB_EV_SONGSTARTED:
    {
        ddb_event_track_t* event = (ddb_event_track_t*) ctx;

        if (!event->track)
            return 0;

        marquee_songstarted(event);
    }
        break;
    case DB_EV_TRACKINFOCHANGED:
    {
        ddb_event_track_t* event = (ddb_event_track_t*) ctx;

        if (!event->track)
            return 0;

        marquee_songstarted(event);
    }
        break;
    case DB_EV_CONFIGCHANGED:
        gdk_threads_enter();
        marquee_config_changed();
        gdk_threads_leave();
        break;
    }
    return 0;
}

static ddb_gtkui_widget_t
*w_infobar_create (void) {
    ddb_gtkui_widget_t *widget = malloc(sizeof(ddb_gtkui_widget_t));
    memset(widget, 0, sizeof(ddb_gtkui_widget_t));

    create_marquee();
    widget->widget = marquee;
    widget->init = marquee_init;
    widget->destroy = marquee_destroy;
    widget->message = marquee_message;

    gtkui_plugin->w_override_signals(widget->widget, widget);
    return widget;
}

static int
marquee_connect(void) {
    gtkui_plugin = (ddb_gtkui_t *)deadbeef->plug_get_for_id(DDB_GTKUI_PLUGIN_ID);
    if (!gtkui_plugin) {
        fprintf(stderr, "infobar: can't find gtkui plugin\n");
        return -1;
    }
    gtkui_plugin->w_reg_widget(WIDGET_LABEL, 0, w_infobar_create, WIDGET_ID, NULL);
    return 0;
}

static int
marquee_disconnect(void) {
    if (gtkui_plugin) {
        gtkui_plugin->w_unreg_widget(WIDGET_ID);
    }
    return 0;
}
static DB_misc_t plugin = {
    .plugin.api_vmajor = 1,
    .plugin.api_vminor = 5,
    .plugin.version_major = 1,
    .plugin.version_minor = 0,
    .plugin.type = DB_PLUGIN_MISC,
    .plugin.name = "marquee",
    .plugin.descr = "marquee",
    .plugin.copyright = "MIT",
    .plugin.website = "http://delapouite.com",
    .plugin.connect = marquee_connect,
    .plugin.disconnect = marquee_disconnect
};

#if GTK_CHECK_VERSION(3, 0, 0)
DB_plugin_t *ddb_marquee_gtk3_load(DB_functions_t *ddb) {
#else
DB_plugin_t *ddb_marquee_gtk2_load(DB_functions_t *ddb) {
#endif
    deadbeef = ddb;
    return DB_PLUGIN(&plugin);
}
