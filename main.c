#include <gtk/gtk.h>

// Unlock click
static void on_unlock_clicked(GtkWidget *widget, gpointer data) {
    GtkEntry *entry = GTK_ENTRY(data);
    const char *password = gtk_editable_get_text(GTK_EDITABLE(entry));

    g_print("Password: %s\n", password);
}

// 👉 Settings window open function
static void open_settings_window(GtkWidget *widget, gpointer data) {
    GtkApplication *app = GTK_APPLICATION(data);

    GtkWidget *win, *label;

    win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(win), "Settings");
    gtk_window_set_default_size(GTK_WINDOW(win), 300, 200);

    label = gtk_label_new("Settings Page");
    gtk_window_set_child(GTK_WINDOW(win), label);

    gtk_window_present(GTK_WINDOW(win));
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window, *overlay, *card, *box;
    GtkWidget *title, *entry, *button, *icon, *settings_btn;

    // Window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Password Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 600);

    // Overlay
    overlay = gtk_overlay_new();
    gtk_window_set_child(GTK_WINDOW(window), overlay);

    // Card
    card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_add_css_class(card, "card");
    gtk_widget_set_valign(card, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(card, GTK_ALIGN_CENTER);

    gtk_widget_set_margin_top(card, 40);
    gtk_widget_set_margin_bottom(card, 40);
    gtk_widget_set_margin_start(card, 40);
    gtk_widget_set_margin_end(card, 40);

    gtk_overlay_set_child(GTK_OVERLAY(overlay), card);

    // Inner box
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_box_append(GTK_BOX(card), box);

    // Settings button (top right)
    settings_btn = gtk_button_new_with_label("⚙");
    gtk_widget_add_css_class(settings_btn, "icon-btn");
    gtk_widget_set_halign(settings_btn, GTK_ALIGN_END);
    gtk_widget_set_valign(settings_btn, GTK_ALIGN_START);
    gtk_widget_set_margin_top(settings_btn, 15);
    gtk_widget_set_margin_end(settings_btn, 15);

    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), settings_btn);

    //  CONNECT SETTINGS BUTTON
    g_signal_connect(settings_btn, "clicked", G_CALLBACK(open_settings_window), app);

    // Lock icon
    icon = gtk_label_new("🔒");
    gtk_widget_add_css_class(icon, "lock-icon");
    gtk_widget_set_halign(icon, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(box), icon);

    // Title
    title = gtk_label_new("Please unlock your vault");
    gtk_widget_add_css_class(title, "title");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(box), title);

    // Entry
    entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "••••••••");
    gtk_widget_add_css_class(entry, "input");
    gtk_widget_set_hexpand(entry, TRUE);
    gtk_box_append(GTK_BOX(box), entry);

    // Button
    button = gtk_button_new_with_label("UNLOCK");
    gtk_widget_add_css_class(button, "main-btn");
    gtk_widget_set_hexpand(button, TRUE);
    g_signal_connect(button, "clicked", G_CALLBACK(on_unlock_clicked), entry);
    gtk_box_append(GTK_BOX(box), button);

    // CSS
    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_data(provider,
        "* {"
        "  font-family: Poppins, sans-serif;"
        "}"
        "window {"
        "  background: #a7d7cc;"
        "}"

        ".card {"
        "  background: #d8ebe6;"
        "  padding: 50px;"
        "  border-radius: 20px;"
        "  box-shadow: 0 25px 50px rgba(0,0,0,0.12);"
        "  min-width: 420px;"
        "  min-height: 380px;"
        "}"

        ".lock-icon {"
        "  font-size: 40px;"
        "  background: #bfe5dc;"
        "  padding: 20px;"
        "  border-radius: 100px;"
        "}"

        ".title {"
        "  font-size: 22px;"
        "  font-weight: bold;"
        "  color: #1f4f49;"
        "}"

        ".input {"
        "  padding: 15px;"
        "  border-radius: 15px;"
        "  border: 2px solid #bfe5dc;"
        "  background: #eaf6f3;"
        "  font-size: 18px;"
        "}"

        ".main-btn {"
        "  background: #1c8c7a;"
        "  color: white;"
        "  padding: 15px;"
        "  border-radius: 15px;"
        "  font-weight: bold;"
        "  font-size: 16px;"
        "}"

        ".main-btn:hover {"
        "  background: #176f62;"
        "}"

        ".icon-btn {"
        "  background: transparent;"
        "  font-size: 18px;"
        "  color: #1c8c7a;"
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

    app = gtk_application_new("com.example.vault", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}