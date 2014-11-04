//  merge_sort.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "merge_sort.h"

void    merge_sort_divide(tab_type *list, unsigned int size, tab_type *list_tmp);
void    merge_sort_merge(tab_type *list_01, unsigned int size_01, tab_type *list_02, unsigned int size_02, tab_type *list_tmp);

void merge_sort(tab_type *tab, unsigned int size)
{
    tab_type    *list_tmp;
    
    if (!(list_tmp = malloc(sizeof(*list_tmp) * (size / 2))))
    {
        perror("Merge sort error: cannot alloc memory.");
        exit(EXIT_FAILURE);
    }
    
    merge_sort_divide(tab, size, list_tmp);
    
    free(list_tmp);
}

void merge_sort_divide(tab_type *list, unsigned int size, tab_type *list_tmp)
{
    unsigned int    size_01;
    unsigned int    size_02;
    
    size_01 = size / 2;
    size_02 = size - size_01;

    if (size_01 > 1)
        merge_sort_divide(list, size_01, list_tmp);
    
    if (size_02 > 1)
        merge_sort_divide(list + size_01, size_02, list_tmp);
    
    merge_sort_merge(list, size_01, list + size_01, size_02, list_tmp);
}

void merge_sort_merge(tab_type *list_01, unsigned int size_01, tab_type *list_02, unsigned int size_02, tab_type *list_tmp)
{
    tab_type    *ptr;
    tab_type    *ptr_01;
    tab_type    *ptr_02;
    
    memcpy(list_tmp, list_01, size_01);

    ptr = list_01;
    ptr_01 = list_tmp;
    ptr_02 = list_02;
    while(size_01 > 0)
    {
        if (size_02 > 0 && *ptr_02 <= *ptr_01)
        {
            *ptr = *ptr_02;
            ptr_02++;
            size_02--;
        }
        else
        {
            *ptr = *ptr_01;
            ptr_01++;
            size_01--;
        }
        
        ptr++;
    }
}
