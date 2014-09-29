#include "ui.h"

static GtkWidget *marquee_text_view;
static GtkTextBuffer *marquee_buffer;

void create_marquee(void) {

#if GTK_CHECK_VERSION(3, 0, 0)
	marquee = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
#else
	marquee = gtk_vbox_new(FALSE, 0);
#endif

	marquee_text_view = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(marquee), marquee_text_view);

	marquee_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(marquee_text_view));
	GtkTextIter begin = {0}, end = {0};
	gtk_text_buffer_get_iter_at_line (marquee_buffer, &begin, 0);
	gtk_text_buffer_get_end_iter (marquee_buffer, &end);
	gtk_text_buffer_delete (marquee_buffer, &begin, &end);
	const char *text = "Marquee!";
	gtk_text_buffer_insert(marquee_buffer, &begin, text, strlen(text));

	gtk_widget_show_all(marquee);
}

void marquee_init(struct ddb_gtkui_widget_s *widget) {
	marquee_config_changed();
}

void marquee_config_changed(void) {

}

void marquee_destroy(struct ddb_gtkui_widget_s *widget) {
	// memory cleanup
}
