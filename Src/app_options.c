/* Description: This is where we can do the heavy lifting for working out which apps are installed
                and which apps we want to install.
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

#include <stdio.h>
#include <stdbool.h>

/* Let's Init our private variables and definitions up here */
static bool module_init_s = false;

// Let's curate a basic app list for now in this 2D array. 
// These can be moved into their own 2D char arrays when more are added.
static char software_app_list[][MAX_APP_OPTION_NAME_LEN] = {
    "steam",
    "obs-studio",
    "discord",
    "vlc",
    "audacity"
};
/* Let's have our private functions for this file up here too */

/* Let's add our public functions in this section */
/*!
 *    \brief    Let's make sure we have everything cocked, locked and ready to rock
 *              before we start using the other functions in this file.
*/
void app_options_init(void)
{
    module_init_s = true;
}

bool app_options_get_list(struct software_app app_list[])
{
    bool app_options_get_okay = false;
    if(module_init_s)
    {
        printf("%s", app_list[0].name);
    }
    else
    {
        printf("app_options module not initialized.");
    }
    return app_options_get_okay;
}




