#include "app_options.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <gtk/gtk.h>


static void print_hello(GtkWidget *widget, gpointer data)
{
  // g_print("YOU CLICKED ME! AAAAAAAAAAAAHHHHHHHHHHHHHHHHH\n");
  app_options_get_list(&software_app_list_g, APPS_LIST_LEN);
  for(uint16_t i = 0; i < APPS_LIST_LEN; i++)
  {
      if(software_app_list_g[i].installed)
      {
        printf("APP: %s Is Installed\n", software_app_list_g[i].name);
      }
      else
      {
        printf("APP: %s Is NOT Installed\n", software_app_list_g[i].name);
      }
  }

}

// static void toggle_button(GtkWidget *widget, gpointer data)
// {
//   char array[] = {"Steam & Discord"};
//   memcpy(software_app_list_s.name, array, 16);
//   app_options_get_list(&software_app_list_s);
// }

static void activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  /* create a new window, and set its title */
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new();

  /* Pack the container in the window */
  gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
  gtk_window_set_child(GTK_WINDOW(window), grid);

  button = gtk_button_new_with_label("Button 1");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label("Button 2");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

  button = gtk_button_new_with_label("Quit");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);

  /* Place the Quit button in the grid cell (0, 1), and make it
   * span 2 columns.
   */
  gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

  gtk_widget_show(window);
}

// static void output_state(GtkToggleButton *source, gpointer user_data)
// {
//   printf("Active: %d\n", gtk_toggle_button_get_active(source));
// }

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;
  app_options_init();
  app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
