/* Description: In this header file we want to house our GTK window, notebook, tabs and widgets function definitions
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

#ifndef HELP_WIZ_WIDGETS_H
#define HELP_WIZ_WIDGETS_H

#include <stdio.h>
#include <gtk/gtk.h>


/************ Let's have any public variables or definitions here ************/
// Struct of function pointers used to callback to our main module which will connect everything together.
struct help_wiz_widg_cbks
{   
    /*!
    *    \brief    This callback will relay to a function that will eventually install our programs
    */
    void (*install_routine)(void);
};

/************ Then let's put our function definitions here ************/
void help_wiz_widg_init(struct help_wiz_widg_cbks *func_cbks);
void help_wiz_widg_setup_window(GtkApplication *app);


#endif