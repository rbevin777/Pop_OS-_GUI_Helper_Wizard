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

/************ Let's Init our private variables and definitions up here ************/

#define WHICH_AND_SPACE_CHAR_LEN 6u //< Length of the characters in the word "which "

static bool module_init_s = false;


// Let's curate a basic app list for now in this 2D array.
// These can be moved into their own 2D char arrays when more are added.
extern struct software_app software_app_list_g[APPS_LIST_LEN] = {
    {"steam", false},
    {"obs-studio", false},
    {"discord", false},
    {"vlc", false},
    {"audacity", false},
    {"chromium-bsu", false}
};

static char pre_defined_apps_list_s[][MAX_APP_OPTION_NAME_LEN] = 
{
    "Steam",
    "OBS-Studio",
    "Discord",
    "VLC",
    "Audacity"
};


/************ Let's have our private function prototypes for this file up here too ************/
static bool check_if_app_installed(char *app_name);

/************ Let's add our public functions in this section ************/

/*!
 *    \brief    Let's make sure we have everything cocked, locked and ready to rock
 *              before we start using the other functions in this file.
 */
void app_options_init(void)
{
    module_init_s = true;
}

/*!
 *    \brief         This function will figure out, from the input app list is, if the apps are installed or not.
 *    \param[in/out] app_list - Pointer to structure array with name of an app 
 *                              and corresponding bool to indicate if an app is installed (true) or it not (false).
 *    \param[in]     n        - Number of elements in the app_list parameter.
 *    \retval        app_check_ran - indicates that we ran the check on the app list. True if we ran the check. False if not.
 */
bool app_options_get_list(struct software_app app_list[], uint16_t n)
{
    bool app_check_ran = false;

    if (module_init_s)
    {   
        // We want to check if any of these apps are already installed.
        for(uint16_t i = 0; i < n; i++)
        {
            app_list[i].installed = check_if_app_installed(app_list[i].name);
        }
        app_check_ran = true;
    }

    return app_check_ran;
}


/************ Let's have our private functions for this file down here. ************/
/*!
 *    \brief     Runs a check using the which keyword if an app is installed or not, based on a given input app name.
 *    \param[in] app_list - name of the app we want to check if it's installed or not
 *    \retval    installed - indicates if the app is installed or not. True is it's installed. False if not.
 */
static bool check_if_app_installed(char *app_name)
{   
    // init some variables
    bool installed = false;

    // need to create an array with the max length of an app name + 6. 
    char which[MAX_APP_OPTION_NAME_LEN + WHICH_AND_SPACE_CHAR_LEN] = "which ";
    
    // concatenate our app name with the "which" termianl command
    strcat(which, app_name);

    // system() will run a check as if being ran in the terminal e.g. "which steam" to check if steam is installed.
    if(system(which) == 0) 
    {
        installed = true;
    }
    return installed;
}
