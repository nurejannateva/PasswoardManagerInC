#include <gtk/gtk.h>

// Unlock button click
static void on_unlock_clicked(GtkWidget *widget, gpointer data) {
    GtkEntry *entry = GTK_ENTRY(data);
    const char *password = gtk_editable_get_text(GTK_EDITABLE(entry));

    g_print("Password: %s\n", password);
}

// Settings click
static void on_settings_clicked(GtkWidget *widget, gpointer data) {
    g_print("Settings clicked\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window, *box, *title, *entry, *button, *settings_btn;

    // Window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Unlock Vault");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 400); // size fix

    // Main box
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_margin_top(box, 70);
    gtk_widget_set_margin_bottom(box, 70);
    gtk_widget_set_margin_start(box, 70);
    gtk_widget_set_margin_end(box, 70);
    gtk_window_set_child(GTK_WINDOW(window), box);

    // Settings button (top right)
    settings_btn = gtk_button_new_with_label("⚙");
    gtk_widget_set_halign(settings_btn, GTK_ALIGN_END);
    gtk_widget_add_css_class(settings_btn, "icon-btn");
    g_signal_connect(settings_btn, "clicked", G_CALLBACK(on_settings_clicked), NULL);
    gtk_box_append(GTK_BOX(box), settings_btn);

    // Title
    title = gtk_label_new("Please unlock your vault");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_widget_add_css_class(title, "title");
    gtk_box_append(GTK_BOX(box), title);

    // Password input
    entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "••••••••");
    gtk_widget_add_css_class(entry, "input");
    gtk_box_append(GTK_BOX(box), entry);

    // Unlock button
    button = gtk_button_new_with_label("Unlock");
    gtk_widget_add_css_class(button, "main-btn");
    g_signal_connect(button, "clicked", G_CALLBACK(on_unlock_clicked), entry);
    gtk_box_append(GTK_BOX(box), button);

    // ✅ CSS Styling
    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_data(provider,
        "* {"
        "  font-family: Poppins, sans-serif;"
        "}"
        "window {"
        "  background: #ccfbf1;" /* teal-100 */
        "}"
        ".title {"
        "  font-size: 18px;"
        "  font-weight: bold;"
        "  color: #134e4a;"
        "}"
        ".input {"
        "  padding: 12px;"
        "  border-radius: 12px;"
        "  border: 2px solid #99f6e4;"
        "  font-size: 18px;"
        "}"
        ".input:focus {"
        "  border: 2px solid #14b8a6;"
        "}"
        ".main-btn {"
        "  background: #0d9488;"
        "  color: white;"
        "  padding: 12px;"
        "  border-radius: 12px;"
        "  font-weight: bold;"
        "}"
        ".main-btn:hover {"
        "  background: #0f766e;"
        "}"
        ".icon-btn {"
        "  background: transparent;"
        "  color: #0d9488;"
        "  font-size: 18px;"
        "}",
        -1
    );

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.unlock", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}