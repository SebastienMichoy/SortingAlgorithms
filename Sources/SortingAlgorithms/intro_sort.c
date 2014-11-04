//  intro_sort.c
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

#include <tgmath.h>

#include "heap_sort.h"
#include "intro_sort.h"
#include "main.h"
#include "shell_sort.h"

void intro_sort_rec(tab_type *tab, unsigned int size, unsigned int deep, double deep_max);
unsigned int    intro_sort_sort(tab_type *tab, unsigned int size);

void intro_sort(tab_type *tab, unsigned int size)
{
    double  deep_max;
    
    deep_max = 2 * log(size);
    intro_sort_rec(tab, size, 0, deep_max);
}

void intro_sort_rec(tab_type *tab, unsigned int size, unsigned int deep, double deep_max)
{
    unsigned int    pivot;
    
    if (size < 2)
        return ;
    
    if (size < 15)
    {
        shell_sort(tab, size);
        return ;
    }
    
    if (deep > deep_max)
    {
        heap_sort(tab, size);
        return ;
    }
    
    pivot = intro_sort_sort(tab, size);
    intro_sort_rec(tab, pivot, deep + 1, deep_max);
    
    if (size > pivot + 1)
        intro_sort_rec(tab + pivot + 1, size - pivot - 1, deep + 1, deep_max);
}

unsigned int intro_sort_sort(tab_type *tab, unsigned int size)
{
    unsigned int    i;
    unsigned int    j;
    tab_type        pivot;
    tab_type        tmp;
    
    i = 0;
    j = size - 2;
    pivot = tab[size - 1];
    while (i < j)
    {
        if (tab[i] > pivot)
        {
            while (i < j && tab[j] > pivot)
                j--;
            
            if (i < j)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
                i++;
            }
        }
        else
            i++;
    }
    
    if (tab[i] > tab[size - 1])
    {
        tmp = tab[i];
        tab[i] = tab[size - 1];
        tab[size - 1] = tmp;
    }
    else
        i = size - 1;
    
    return (i);
}
