#include <QCoreApplication>

// Prevent C++ linkage conflicts
#undef signals
extern "C" {
#include <gtk/gtk.h>
}
#define signals Q_SIGNALS

// Global GTK widgets
GtkWidget *window;
GtkWidget *gtkButtonGo;
GtkWidget *gtkButtonPrevSite;
GtkWidget *gtkButtonNextSite;
GtkWidget *gtkButtonNextUnviewed;
GtkWidget *gtkTextViewResponse;
GtkBuilder *builder;
GMainLoop *loop;

void set_red_text_in_textview(const char* message) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkTextViewResponse));

    // Create a new tag
    GtkTextTag *red_tag = gtk_text_buffer_create_tag(buffer, NULL,
                                                     "foreground", "#FF0000",
                                                     "weight", PANGO_WEIGHT_BOLD,
                                                     NULL);

    // Clear previous content
    gtk_text_buffer_set_text(buffer, "", 0);

    // Get start position
    GtkTextIter start;
    gtk_text_buffer_get_start_iter(buffer, &start);

    // Insert the text and mark its start
    gtk_text_buffer_create_mark(buffer, "start_mark", &start, TRUE);

    // Insert the message
    gtk_text_buffer_insert(buffer, &start, message, -1);

    // Get the marked position and current end
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    GtkTextMark *start_mark = gtk_text_buffer_get_mark(buffer, "start_mark");
    gtk_text_buffer_get_iter_at_mark(buffer, &start, start_mark);

    // Apply the tag
    gtk_text_buffer_apply_tag(buffer, red_tag, &start, &end);
}

// Button click handlers
static void on_button_go_clicked(GtkButton *button, gpointer data) {
    set_red_text_in_textview("GO button clicked!\n");
}

static void on_button_prev_site_clicked(GtkButton *button, gpointer data) {
    set_red_text_in_textview("Previous Site button clicked!\n");
}

static void on_button_next_site_clicked(GtkButton *button, gpointer data) {
    set_red_text_in_textview("Next Site button clicked!\n");
}

static void on_button_next_unviewed_clicked(GtkButton *button, gpointer data) {
    set_red_text_in_textview("Next Unviewed button clicked!\n");
}

// Function to handle window closing
static void on_window_destroy(GtkWidget *widget, gpointer data) {
    GMainLoop *loop = static_cast<GMainLoop*>(data);
    g_main_loop_quit(loop);
    gtk_window_destroy(GTK_WINDOW(widget));
    exit(0);
}

int main(int argc, char *argv[])
{
    // Initialize Qt
    QCoreApplication app(argc, argv);

    // Initialize GTK
    gtk_init();

    // Create main loop
    loop = g_main_loop_new(NULL, FALSE);

    // Load GTK builder file
    builder = gtk_builder_new_from_file("Pandda2InspectGTK4Window.xml");

    // Get the window
    window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    if (!window) {
        g_critical("Window widget not found!");
        return 1;
    }

    // Connect window close signal
    g_signal_connect(window, "close-request", G_CALLBACK(on_window_destroy), loop);

    // Get other widgets
    gtkButtonGo = GTK_WIDGET(gtk_builder_get_object(builder, "gtkButtonGo"));
    gtkButtonPrevSite = GTK_WIDGET(gtk_builder_get_object(builder, "gtkButtonPrevSite"));
    gtkButtonNextSite = GTK_WIDGET(gtk_builder_get_object(builder, "gtkButtonNextSite"));
    gtkButtonNextUnviewed = GTK_WIDGET(gtk_builder_get_object(builder, "gtkButtonNextUnviewed"));
    gtkTextViewResponse = GTK_WIDGET(gtk_builder_get_object(builder, "gtkTextViewResponse"));

    // Connect button signals
    g_signal_connect(gtkButtonGo, "clicked", G_CALLBACK(on_button_go_clicked), NULL);
    g_signal_connect(gtkButtonPrevSite, "clicked", G_CALLBACK(on_button_prev_site_clicked), NULL);
    g_signal_connect(gtkButtonNextSite, "clicked", G_CALLBACK(on_button_next_site_clicked), NULL);
    g_signal_connect(gtkButtonNextUnviewed, "clicked", G_CALLBACK(on_button_next_unviewed_clicked), NULL);

    // Show window
    gtk_widget_show(window);

    // Start GTK main loop
    g_main_loop_run(loop);

    // Cleanup
    g_main_loop_unref(loop);
    g_object_unref(builder);

    return 0;
}
