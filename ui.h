#ifndef MARQUEE_UI_HEADER
#define MARQUEE_UI_HEADER

// globals

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <deadbeef/deadbeef.h>
#include <deadbeef/gtkui_api.h>

// locals

// marquee widget
GtkWidget *marquee;

void create_marquee(void);

// lifecycle callbacks

void marquee_init(struct ddb_gtkui_widget_s *widget);

void marquee_config_changed(void);

void marquee_destroy(struct ddb_gtkui_widget_s *widget);

#endif
