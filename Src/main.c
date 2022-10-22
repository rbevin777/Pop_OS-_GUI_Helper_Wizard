#include "app_options.h"

#include <gtk/gtk.h>

static struct software_app software_app_list_s;

static void print_hello (GtkWidget *widget, gpointer data)
{
  g_print ("YOU CLICKED ME! AAAAAAAAAAAAHHHHHHHHHHHHHHHHH\n");
  char array[] = {"Steam & Discord"};
  memcpy(software_app_list_s.name, array, 16);
  app_options_get_list(&software_app_list_s);
}

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Installation Helper Wizard");
  gtk_window_set_default_size (GTK_WINDOW (window), 640, 480);

  button = gtk_button_new_with_label ("Click Me");
  gtk_icon_view_set_item_width(GTK_WINDOW(window), 20);
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  gtk_window_set_child (GTK_WINDOW (window), button);

  gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;
  app_options_init();
  
  app = gtk_application_new (NULL, G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
