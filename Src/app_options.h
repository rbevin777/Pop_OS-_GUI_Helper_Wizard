/* Description: In this header file we want to house common variables and function definitions
                of which software applications we want will offer the user an option to install.
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

#ifndef APP_OPTIONS_H
#define APP_OPTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/************ Let's have any public variables or definitions here ************/
#define MAX_APP_OPTION_NAME_LEN 100
#define APPS_LIST_LEN 6u

#define ARRAY_LEN(array) sizeof(array)/sizeof(array[0])
// We can use this struct to tell us what software is selected to be installed/if it already is installed.
struct software_app
{
    char name[MAX_APP_OPTION_NAME_LEN];
    bool installed;
};

extern struct software_app software_app_list_g[APPS_LIST_LEN];

/************ Then let's put our function definitions here ************/
void app_options_init(void);
bool app_options_get_list(struct software_app app_list[], uint16_t n);

#endif