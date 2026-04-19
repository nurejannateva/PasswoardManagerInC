// #include <gtk/gtk.h>

// static void activate(GtkApplication *app, gpointer user_data) {

//     GtkWidget *window = gtk_application_window_new(app);
//     gtk_window_set_title(GTK_WINDOW(window), "Change PIN");
//     gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);

//     // Root container
//     GtkWidget *root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//     gtk_window_set_child(GTK_WINDOW(window), root);

//     // Center box
//     GtkWidget *center = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
//     gtk_widget_set_halign(center, GTK_ALIGN_CENTER);
//     gtk_widget_set_valign(center, GTK_ALIGN_CENTER);
//     gtk_widget_set_size_request(center, 420, -1);
//     gtk_widget_set_name(center, "card");

//     gtk_box_append(GTK_BOX(root), center);

//     // Title
//     GtkWidget *title = gtk_label_new("Change your pin");
//     gtk_widget_set_name(title, "title");
//     gtk_box_append(GTK_BOX(center), title);

//     // Inputs
//     GtkWidget *old_pass = gtk_entry_new();
//     gtk_entry_set_placeholder_text(GTK_ENTRY(old_pass), "Old Password");
//     gtk_widget_set_name(old_pass, "input");

//     GtkWidget *new_pass = gtk_entry_new();
//     gtk_entry_set_placeholder_text(GTK_ENTRY(new_pass), "New Password");
//     gtk_widget_set_name(new_pass, "input");

//     GtkWidget *confirm_pass = gtk_entry_new();
//     gtk_entry_set_placeholder_text(GTK_ENTRY(confirm_pass), "Confirm New Password");
//     gtk_widget_set_name(confirm_pass, "input");

//     gtk_box_append(GTK_BOX(center), old_pass);
//     gtk_box_append(GTK_BOX(center), new_pass);
//     gtk_box_append(GTK_BOX(center), confirm_pass);

//     // Button
//     GtkWidget *btn = gtk_button_new_with_label("Save");
//     gtk_widget_set_name(btn, "btn");
//     gtk_box_append(GTK_BOX(center), btn);

//     // =========================
//     // CSS (INLINE)
//     // =========================
//     const char *css_data =
//         "window {"
//         "   background: #cffff4;"
//         "}"
//         "#card {"
//         // "   background: #e6fffb;"
       
//         "  background: #d8ebe6;"
//         "  padding: 50px;"
//         "  border-radius: 20px;"
//         "  box-shadow: 0 25px 50px rgba(0,0,0,0.12);"
//         "  min-width: 420px;"
//         "  min-height: 380px;"
//         "}"

//         "#title {"
//         "   font-size: 22px;"
//         "   font-weight: bold;"
//         "   color: #1f4d4a;"
//         "   margin-bottom: 20px;"
//         "}"
//         "#input {"
//         "   padding: 12px;"
//         "   border-radius: 15px;"
//         "   border: 1px solid #7fe7d6;"
//         "   background: #f7fffd;"
//         "   margin-bottom: 10px;"
//         "}"
//         "#btn {"
//         "   background: #0f9d8f;"
//         "   color: white;"
//         "   padding: 12px;"
//         "   border-radius: 15px;"
//         "   margin-top: 10px;"
//         "   font-weight: bold;"
//         "}"
//         "#btn:hover {"
//         "   background: #0c7f74;"
//         "}";

//     GtkCssProvider *css = gtk_css_provider_new();
//     gtk_css_provider_load_from_data(css, css_data, -1);

//     gtk_style_context_add_provider_for_display(
//         gdk_display_get_default(),
//         GTK_STYLE_PROVIDER(css),
//         GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
//     );

//     gtk_window_present(GTK_WINDOW(window));
// }

// int main(int argc, char **argv) {
//     GtkApplication *app = gtk_application_new("com.example.pin", G_APPLICATION_DEFAULT_FLAGS);
//     g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
//     return g_application_run(G_APPLICATION(app), argc, argv);
// }




#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data) {

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Change PIN");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);

    // Root container (full page center control)
    GtkWidget *root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(root, TRUE);
    gtk_widget_set_vexpand(root, TRUE);
    gtk_window_set_child(GTK_WINDOW(window), root);

    // Center wrapper (THIS makes card center in page)
    GtkWidget *wrapper = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(wrapper, TRUE);
    gtk_widget_set_vexpand(wrapper, TRUE);
    gtk_widget_set_halign(wrapper, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(wrapper, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(root), wrapper);

    // CARD
    GtkWidget *center = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
    gtk_widget_set_name(center, "card");
    gtk_widget_set_size_request(center, 420, -1);

    gtk_box_append(GTK_BOX(wrapper), center);

    // Title
    GtkWidget *title = gtk_label_new("Change your pin");
    gtk_widget_set_name(title, "title");
    gtk_box_append(GTK_BOX(center), title);

    // Inputs
    GtkWidget *old_pass = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(old_pass), "Old Password");
    gtk_widget_set_name(old_pass, "input");

    GtkWidget *new_pass = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_pass), "New Password");
    gtk_widget_set_name(new_pass, "input");

    GtkWidget *confirm_pass = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(confirm_pass), "Confirm New Password");
    gtk_widget_set_name(confirm_pass, "input");

    gtk_box_append(GTK_BOX(center), old_pass);
    gtk_box_append(GTK_BOX(center), new_pass);
    gtk_box_append(GTK_BOX(center), confirm_pass);

    // Button
    GtkWidget *btn = gtk_button_new_with_label("Save");
    gtk_widget_set_name(btn, "btn");
    gtk_box_append(GTK_BOX(center), btn);

    // CSS
    const char *css_data =
        "window {"
        "   background: #cffff4;"
        "}"

        "#card {"
        "   background: #d8ebe6;"
        "   padding: 50px;"
        "   border-radius: 20px;"
        "   box-shadow: 0 25px 50px rgba(0,0,0,0.12);"
        "}"

        "#title {"
        "   font-size: 22px;"
        "   font-weight: bold;"
        "   color: #1f4d4a;"
        "   margin-bottom: 20px;"
        "}"

        "#input {"
        "   padding: 12px;"
        "   border-radius: 15px;"
        "   border: 1px solid #7fe7d6;"
        "   background: #f7fffd;"
        "}"

        "#btn {"
        "   background: #0f9d8f;"
        "   color: white;"
        "   padding: 12px;"
        "   border-radius: 15px;"
        "   font-weight: bold;"
        "}"

        "#btn:hover {"
        "   background: #0c7f74;"
        "}";

    GtkCssProvider *css = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css, css_data, -1);

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.example.pin", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}