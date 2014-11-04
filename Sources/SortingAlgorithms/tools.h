//  tools.h
//
// Copyright (c) 2014 Sébastien MICHOY
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer. Redistributions in binary
// form must reproduce the above copyright notice, this list of conditions and
// the following disclaimer in the documentation and/or other materials
// provided with the distribution. Neither the name of the nor the names of
// its contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "main.h"

struct tabs_list
{
    tab_type    *tab_original;
    tab_type    *tab_cpy;
    tab_type    *tab_verified;
    int         tab_verified_filled;
};

float   exec_sort(void(*sort)(tab_type *, unsigned int), char *name, struct tabs_list *tabs_list, unsigned int size);
void    display_results(char *name, float **results, unsigned int tab_sizes_length, unsigned int number_of_tests);
void    free_results(float ***results, unsigned int number_of_sorting, unsigned int tab_sizes_length);
void    free_tabs(tab_type **tab_original, tab_type **tab_cpy, tab_type **tab_verified);
void    generate_results(float ****results, unsigned int number_of_sorting, unsigned int tab_sizes_length, unsigned int number_of_tests);
void    generate_tabs(tab_type **tab_original, tab_type **tab_cpy, tab_type **tab_verified, unsigned int size);

#endif
