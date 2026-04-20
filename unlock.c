#include <gtk/gtk.h>

/* ================= MODAL ================= */
static void on_add_clicked(GtkButton *btn, gpointer window) {

    GtkWidget *dialog = gtk_window_new();

    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);

    gtk_window_set_default_size(GTK_WINDOW(dialog), 600, 520);
    gtk_window_set_decorated(GTK_WINDOW(dialog), FALSE);

    GtkWidget *overlay = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(overlay, "modal-bg");
    gtk_window_set_child(GTK_WINDOW(dialog), overlay);

    GtkWidget *card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_name(card, "modal-card");

    gtk_widget_set_hexpand(card, TRUE);
    gtk_widget_set_vexpand(card, TRUE);
    gtk_widget_set_halign(card, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(card, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(card, 420, 420);

    gtk_box_append(GTK_BOX(overlay), card);

    /* TITLE */
    GtkWidget *title = gtk_label_new("Add New Credential");
    gtk_widget_set_name(title, "modal-title");
    gtk_box_append(GTK_BOX(card), title);

    /* ENTRIES */
    GtkWidget *platform = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(platform), "Platform");

    GtkWidget *username = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username), "Username");

    GtkWidget *password = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(password), FALSE);

    gtk_box_append(GTK_BOX(card), platform);
    gtk_box_append(GTK_BOX(card), username);
    gtk_box_append(GTK_BOX(card), password);

    /* SAVE */
    GtkWidget *save = gtk_button_new_with_label("Save");
    gtk_widget_set_name(save, "modal-save");
    gtk_box_append(GTK_BOX(card), save);

    /* CANCEL */
    GtkWidget *cancel = gtk_button_new_with_label("Cancel");
    gtk_widget_set_name(cancel, "modal-cancel");
    gtk_box_append(GTK_BOX(card), cancel);

    g_signal_connect(cancel, "clicked", G_CALLBACK(gtk_window_destroy), dialog);
    g_signal_connect(save, "clicked", G_CALLBACK(gtk_window_destroy), dialog);

    gtk_window_present(GTK_WINDOW(dialog));
}

/* ================= APP ================= */
static void activate(GtkApplication *app, gpointer user_data) {

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Password Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 650);

    GtkWidget *root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), root);

    GtkWidget *center = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(center, TRUE);
    gtk_widget_set_vexpand(center, TRUE);
    gtk_widget_set_halign(center, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(center, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(root), center);

    GtkWidget *card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 18);
    gtk_widget_set_name(card, "card");
    gtk_widget_set_size_request(card, 750, 350);
    gtk_box_append(GTK_BOX(center), card);

    /* TOP BAR */
    GtkWidget *top = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    GtkWidget *edit_btn = gtk_button_new_with_label("Edit");
    GtkWidget *spacer = gtk_label_new("");
    GtkWidget *add_btn = gtk_button_new_with_label("Add New");

    gtk_widget_set_name(edit_btn, "btn");
    gtk_widget_set_name(add_btn, "btn");

    gtk_widget_set_hexpand(spacer, TRUE);

    gtk_box_append(GTK_BOX(top), edit_btn);
    gtk_box_append(GTK_BOX(top), spacer);
    gtk_box_append(GTK_BOX(top), add_btn);

    gtk_box_append(GTK_BOX(card), top);

    /* LIST */
    GtkWidget *scroll = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroll, TRUE);

    GtkWidget *list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), list);

    gtk_box_append(GTK_BOX(card), scroll);

    /* SAMPLE ROW */
    for (int i = 0; i < 2; i++) {

        GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_name(row, "row");

        GtkWidget *left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

        GtkWidget *user = gtk_label_new("Username");
        GtkWidget *pass = gtk_label_new("Password");

        gtk_widget_set_halign(user, GTK_ALIGN_START);
        gtk_widget_set_halign(pass, GTK_ALIGN_START);

        gtk_box_append(GTK_BOX(left), user);
        gtk_box_append(GTK_BOX(left), pass);

        gtk_widget_set_hexpand(left, TRUE);

        GtkWidget *actions = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

        GtkWidget *copy = gtk_button_new_with_label("📋");
        GtkWidget *edit = gtk_button_new_with_label("✏️");
        GtkWidget *del  = gtk_button_new_with_label("🗑");

        gtk_widget_set_name(copy, "icon");
        gtk_widget_set_name(edit, "icon");
        gtk_widget_set_name(del, "danger");

        gtk_widget_set_size_request(copy, 45, 45);
        gtk_widget_set_size_request(edit, 45, 45);
        gtk_widget_set_size_request(del, 45, 45);

        gtk_box_append(GTK_BOX(actions), copy);
        gtk_box_append(GTK_BOX(actions), edit);
        gtk_box_append(GTK_BOX(actions), del);

        gtk_box_append(GTK_BOX(row), left);
        gtk_box_append(GTK_BOX(row), actions);

        gtk_box_append(GTK_BOX(list), row);
    }

    g_signal_connect(add_btn, "clicked", G_CALLBACK(on_add_clicked), window);

    /* ================= CSS ================= */
    const char *css =
        "window { background: #cffff4; }"

        "#card {"
        " background: #d9fbf3;"
        " border-radius: 30px;"
        " padding: 25px;"
        " box-shadow: 0 14px 35px rgba(0,0,0,0.18);"
        "}"

        "#btn {"
        " background: #0f9d8f;"
        " color: white;"
        " border-radius: 14px;"
        " padding: 10px 22px;"
        " box-shadow: 0 8px 20px rgba(0,0,0,0.20);"
        "}"

        "#row {"
        " background: #f4fffd;"
        " padding: 18px;"
        " border-radius: 18px;"
        "}"

        "#icon {"
        " background: white;"
        " border-radius: 14px;"
        " padding: 10px;"
        "}"

        "#danger {"
        " background: #ffecec;"
        " border-radius: 14px;"
        " padding: 10px;"
        "}"

        /* MODAL */
        "#modal-bg {"
        " background: rgba(0,0,0,0.15);"
        "}"

        "#modal-card {"
        " background: #f4fffd;"
        " border-radius: 25px;"
        " padding: 25px;"
        "}"

        "#modal-title {"
        " font-size: 22px;"
        " font-weight: bold;"
        " color: #134e4a;"
        "}"

        "entry {"
        " background: #eafff9;"
        " border-radius: 20px;"
        " padding: 14px;"
        "}"

        "#modal-save {"
        " background: #0f9d8f;"
        " color: white;"
        " border-radius: 14px;"
        " padding: 12px;"
        "}"

        "#modal-cancel {"
        " background: transparent;"
        " color: #0f9d8f;"
        "}"

        /* 🔥 GLOBAL BUTTON EFFECT */
        "button {"
        " transition: all 0.2s ease;"
        "}"

        "button:hover {"
        " opacity: 0.9;"
        "}"

        "button:active {"
        " transform: scale(0.95);"
        "}";

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, css);

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    gtk_window_present(GTK_WINDOW(window));
}

/* ================= MAIN ================= */
int main(int argc, char **argv) {

    GtkApplication *app =
        gtk_application_new("com.example.password", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    return g_application_run(G_APPLICATION(app), argc, argv);
}