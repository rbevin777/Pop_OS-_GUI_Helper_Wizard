/* Description: This is our main file where we do the linking between our helper modules
                and hookups to the app insterface.
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
#include "app_options.h"
#include "help_wiz_widgets.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/************ Let's Init our private variables and definitions up here ************/
static void install_programs(void);

struct help_wiz_widg_cbks func_cbks_s = 
{
  .install_routine = install_programs
};

/************ Let's have our private function prototypes for this file up here too ************/
static void print_hello(void);

/************ Let's add our public functions in this section ************/

/*!
 *    \brief    This is our main where we will run our app.
 */
int main(int argc, char **argv)
{
  // Create some initial variables first
  GtkApplication *app;
  int status;

  // initialise our modules first
  app_options_init();
  help_wiz_widg_init(&func_cbks_s);

  // Then proceed to create the window
  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(help_wiz_widg_setup_window), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}

/************ Let's have our private functions for this file down here. ************/
/*!
 *    \brief    At the moment, this function is just used to indiacte that the checkboxes are hooked up.
 */
static void print_hello(void)
{ 
  int arra_len = app_options_get_app_list_len(APP_OP_ACCESSORIES);
  printf("array len: %d\n", arra_len);
  app_options_get_list(&software_app_list_g, APPS_LIST_LEN);
  for (uint16_t i = 0; i < APPS_LIST_LEN; i++)
  {
    if (software_app_list_g[i].installed)
    {
      printf("APP: %s Is Installed\n", software_app_list_g[i].name);
    }
    else
    {
      printf("APP: %s Is NOT Installed\n", software_app_list_g[i].name);
    }
  }
}

/*!
 *    \brief    This function will eventually install our programs
 */
static void install_programs(void)
{
  print_hello();
}

