/* Description: This is where we will setup our GTK window, notebook, tabs and widgets.
*/

/********************************************************************************
Copyright (c) 2022 Ryan Bevin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*********************************************************************************/
#include "help_wiz_widgets.h"
#include "app_options.h"

#include <stdbool.h>

/************ Let's Init our private variables and definitions up here ************/
// Boolean to indicate if the module has been initialized or not.
static bool module_init_s = false;

// We can use this struct to create multiple check button widgets and store their info
struct check_button_info
{
  GtkWidget *check_button_widg;
  char button_name[MAX_APP_OPTION_NAME_LEN];
  bool active;
};

// private variable to call our callbacks from.
static struct help_wiz_widg_cbks widg_cbks_s;

/************ Let's have our private function prototypes for this file up here too ************/
static void set_up_window(GtkApplication *app);
static void set_up_checkbox_widget(GtkWidget *vbox, GtkSizeGroup *size_group, struct check_button_info *check_button, char *name_of_app, bool installed);
static void set_up_button_widget(GtkWidget *vbox, char *name, void(*button_clicked));
static void set_up_our_notebook(GtkWidget *window, GtkWidget *vbox);

/************ Let's add our public functions in this section ************/
/*!
 *    \brief    Let's make sure we have everything cocked, locked and ready to rock
 *              before we start using the other functions in this file.
 */
void help_wiz_widg_init(struct help_wiz_widg_cbks *widg_cbks)
{   
    if(widg_cbks == NULL)
    {
        printf("ERROR: help_wiz_widg_init NOT INITIALIZED!");
        module_init_s = false;
    }
    else
    {
        widg_cbks_s = *widg_cbks;
        module_init_s = true;
    }
}

/*!
 *    \brief    This function will do the heavy lifting by setting up the main window
 *    \param    app - pointer to the application that was created.
 */
void help_wiz_widg_setup_window(GtkApplication *app)
{
    if(module_init_s)
    {
        set_up_window(app);
    }
    else
    {
        printf("ERROR: help_wiz_widg_init NOT INITIALIZED!");
    }
}

/************ Let's have our private functions for this file down here. ************/
/*!
 *    \brief    In this function we can setup our intial window for the post installation wizard.
 *    \param    app - pointer to the application that was created.
 */
static void set_up_window(GtkApplication *app)
{
  // Set up the initial app window
  GtkWidget *main_window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(main_window), "Post Installation Wizard");
  gtk_window_set_default_size(GTK_WINDOW(main_window), 720, 480);

  // This is used to setup the checkbox array later
  GtkSizeGroup *size_group = gtk_size_group_new(GTK_SIZE_GROUP_HORIZONTAL);
  g_object_set_data_full(G_OBJECT(main_window), "size-group", size_group, g_object_unref);

  // gtk_check_button_get_active(); I'll need this function later


/* From here...*/
  // Create our accessories page child box to contain our check buttons.
  GtkWidget *accessories_child_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, APPS_LIST_LEN);

  // Get a list of our installed apps
  app_options_get_list(&software_app_list_g, APPS_LIST_LEN);

  static struct check_button_info check_button_info_s[APPS_LIST_LEN];
  // Let's setup some check button widgets.
  for (uint16_t i = 0; i < APPS_LIST_LEN; i++)
  {
    set_up_checkbox_widget(accessories_child_vbox, size_group, check_button_info_s, software_app_list_g[i].name, software_app_list_g[i].installed);
  }

  // Let's see if we can add an install button.
  set_up_button_widget(accessories_child_vbox, "Install", widg_cbks_s.install_routine); //!< install button only appears in accessories child box.
  set_up_our_notebook(main_window, accessories_child_vbox);
/* To here... is specific to the accessory page. Need to tidy this up*/



  gtk_window_present(GTK_WINDOW(main_window));
}

/*!
 *    \brief    This  function will create a signle checkbox widget based on a given input name and boolean.
 *    \param    vbox - Pointer to the container which will house each of these checkbox widgets.
 *    \param    size_group - Pointer to size_group which provides a mechanism for grouping a number of widgets together so they all request the same amount of space.
 *    \param    check_button - Pointer to a struct containing a check button widget and button info.
 *    \param    name - Name of the checkbox.
 *    \param    installed - initial value when created, True/False.
 */
static void set_up_checkbox_widget(GtkWidget *vbox, GtkSizeGroup *size_group, struct check_button_info *check_button, char *name, bool installed)
{
  // Set up a check button
  check_button->check_button_widg = gtk_check_button_new_with_mnemonic(name);
  gtk_box_append(GTK_BOX(vbox), check_button->check_button_widg);
  gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button->check_button_widg), installed);

  // populate our check button widg with information about the app name and if it is installed or not.
  memcpy(check_button->button_name, name, APPS_LIST_LEN);
  check_button->active = installed;
}

/*!
 *    \brief    This function will help us setup button widgets easier.
 *    \param    vbox - Pointer to the container which will house each of these checkbox widgets.
 */
static void set_up_button_widget(GtkWidget *vbox, char *name, void(*button_clicked))
{
  GtkWidget *button = gtk_button_new_with_label(name);
  g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL); // This will allow us to hook into a function.
  gtk_box_append(GTK_BOX(vbox), button);
}

/*!
 *    \brief    This function helps us setup the notebook and it's correcsponding tabs/pages.
 *    \param    window - Pointer to the main window so that our notebook can be added to the main window.
 *    \param    vbox - Pointer to the container which will house each of these checkbox widgets.
 */
static void set_up_our_notebook(GtkWidget *window, GtkWidget *vbox)
{
  // Setup our notebook
  GtkWidget *notebook = gtk_notebook_new();
/* This can be dried up */
  // Setup the children for within the notebook tabs/pages
  GtkWidget *auido_video_label = gtk_label_new("Aduio and Video Page");
  GtkWidget *development_label = gtk_label_new("Development Page");
  GtkWidget *gaming_page_label = gtk_label_new("Gaming Page");
  GtkWidget *browser_page_label = gtk_label_new("Browser Page");
  GtkWidget *tools_page_label = gtk_label_new("Tools Page");

  // Set the notebook starting poistion
  gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);

  // tab labels for notebook
  GtkWidget *accessories_page = gtk_label_new("Accessories");
  GtkWidget *audio_video_page = gtk_label_new("Audio and Video");
  GtkWidget *development_page = gtk_label_new("Development");
  GtkWidget *gaming_page = gtk_label_new("Gaming");
  GtkWidget *browser_page = gtk_label_new("Browsers");
  GtkWidget *tools_page = gtk_label_new("Tools");

  // add the pages/tabs to the notebook
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, accessories_page);
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), auido_video_label, audio_video_page);
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), development_label, development_page);
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), gaming_page_label, gaming_page);
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), browser_page_label, browser_page);

  // make the notebook a child of the window
  gtk_window_set_child(GTK_NOTEBOOK(window), notebook);
}