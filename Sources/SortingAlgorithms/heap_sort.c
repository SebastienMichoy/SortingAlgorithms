//  heap_sort.c
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

#include "heap_sort.h"

typedef enum
{
    heap_sort_switch_left,
    heap_sort_switch_none,
    heap_sort_switch_right
}   heap_sort_switch_type;

void                    heap_sort_sort_all(tab_type *tab, unsigned int size);
heap_sort_switch_type   heap_sort_switch(tab_type *tab, unsigned int size, unsigned int offset);

void heap_sort(tab_type *tab, unsigned int size)
{
    int                     end_offset;
    int                     switch_offset;
    heap_sort_switch_type   switch_val;
    tab_type                tmp;
    
    heap_sort_sort_all(tab, size);
    
    end_offset = size - 1;
    while (end_offset > 0)
    {
        tmp = tab[0];
        tab[0] = tab[end_offset];
        tab[end_offset] = tmp;
        
        switch_offset = 0;
        while ((switch_val = heap_sort_switch(tab, end_offset, switch_offset)) != heap_sort_switch_none)
        {
            switch_offset = (2 * switch_offset) + 1;
            
            if (switch_val == heap_sort_switch_right)
                switch_offset++;
        }
        
        end_offset--;
    }
}

void heap_sort_sort_all(tab_type *tab, unsigned int size)
{
    int                     root_offset;
    int                     switch_offset;
    heap_sort_switch_type   switch_val;
    
    root_offset = ((size - 1) / 2);
    while (root_offset >= 0)
    {
        switch_offset = root_offset;
        while ((switch_val = heap_sort_switch(tab, size, switch_offset)) != heap_sort_switch_none)
        {
            switch_offset = (2 * switch_offset) + 1;
            
            if (switch_val == heap_sort_switch_right)
                switch_offset++;
        }
        
        root_offset--;
    }
}

heap_sort_switch_type heap_sort_switch(tab_type *tab, unsigned int size, unsigned int offset)
{
    unsigned int            son_offset;
    heap_sort_switch_type   switch_ret;
    tab_type                tmp;
    
    switch_ret = heap_sort_switch_none;
    
    if ((2 * offset) + 1 >= size)
        return (switch_ret);
    
    if ((son_offset = (2 * offset) + 2) < size)
    {
        if (tab[son_offset - 1] > tab[son_offset])
        {
            son_offset--;
            switch_ret = heap_sort_switch_left;
        }
        else
            switch_ret = heap_sort_switch_right;
    }
    else if ((son_offset = (2 * offset) + 1) < size)
        switch_ret = heap_sort_switch_right;
    
    if (tab[offset] < tab[son_offset])
    {
        tmp = tab[offset];
        tab[offset] = tab[son_offset];
        tab[son_offset] = tmp;
    }
    
    return (switch_ret);
}
