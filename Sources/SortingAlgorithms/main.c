//  main.c
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

#include "bubble_sort.h"
#include "insertion_sort.h"
#include "heap_sort.h"
#include "intro_sort.h"
#include "main.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "selection_sort.h"
#include "shell_sort.h"
#include "tools.h"

int main(__attribute__ ((unused)) int ac, __attribute__((unused)) char **av)
{
    sort_small_arrays();
    sort_medium_arrays();
    sort_big_arrays();
    
    return (EXIT_SUCCESS);
}

void sort_big_arrays(void)
{
    unsigned int        number_of_tests;
    float               ***results;
    tab_type            *tab_original;
    tab_type            *tab_cpy;
    unsigned int        tab_size;
    unsigned int        tab_sizes[6];
    unsigned int        tab_sizes_index;
    unsigned int        tab_sizes_length;
    tab_type            *tab_verified;
    struct tabs_list    tabs_list;
    unsigned int        test_number;
    
    tab_sizes[0] = 50000;
    tab_sizes[1] = 100000;
    tab_sizes[2] = 500000;
    tab_sizes[3] = 1000000;
    tab_sizes[4] = 5000000;
    tab_sizes[5] = 10000000;
    
    tab_sizes_length = 6;
    number_of_tests = 100;
    
    generate_results(&results, 3, tab_sizes_length, number_of_tests);
    
    for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
    {
        tab_size = tab_sizes[tab_sizes_index];
        
        for (test_number = 0; test_number < number_of_tests; test_number++)
        {
            generate_tabs(&tab_original, &tab_cpy, &tab_verified, tab_size);
            
            tabs_list.tab_original = tab_original;
            tabs_list.tab_cpy = tab_cpy;
            tabs_list.tab_verified = tab_verified;
            tabs_list.tab_verified_filled = 0;
            
            results[0][tab_sizes_index][test_number] = exec_sort(merge_sort, "Merge sort", &tabs_list, tab_size);
            results[1][tab_sizes_index][test_number] = exec_sort(heap_sort, "Heap sort", &tabs_list, tab_size);
            results[2][tab_sizes_index][test_number] = exec_sort(intro_sort, "Intro sort", &tabs_list, tab_size);
            
            free_tabs(&tab_original, &tab_cpy, &tab_verified);
        }
    }
    
    if (DISPLAY_RESULT_SUMMARY)
    {
        printf("\n\n|Name|");
        
        for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
            printf("%u|", tab_sizes[tab_sizes_index]);
        
        printf("\n|:-|");
        
        for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
            printf(":-:|");
        
        printf("\n");
        
        display_results("Merge sort", results[0], tab_sizes_length, number_of_tests);
        display_results("Heap sort", results[1], tab_sizes_length, number_of_tests);
        display_results("Intro sort", results[2], tab_sizes_length, number_of_tests);
    }
    
    free_results(results, 3, tab_sizes_length);
}

void sort_medium_arrays(void)
{
    unsigned int        number_of_tests;
    float               ***results;
    tab_type            *tab_original;
    tab_type            *tab_cpy;
    unsigned int        tab_size;
    unsigned int        tab_sizes[6];
    unsigned int        tab_sizes_index;
    unsigned int        tab_sizes_length;
    tab_type            *tab_verified;
    struct tabs_list    tabs_list;
    unsigned int        test_number;
    
    tab_sizes[0] = 100;
    tab_sizes[1] = 500;
    tab_sizes[2] = 1000;
    tab_sizes[3] = 5000;
    tab_sizes[4] = 10000;
    tab_sizes[5] = 50000;
    
    tab_sizes_length = 6;
    number_of_tests = 100;
    
    generate_results(&results, 5, tab_sizes_length, number_of_tests);
    
    for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
    {
        tab_size = tab_sizes[tab_sizes_index];
        
        for (test_number = 0; test_number < number_of_tests; test_number++)
        {
            generate_tabs(&tab_original, &tab_cpy, &tab_verified, tab_size);
            
            tabs_list.tab_original = tab_original;
            tabs_list.tab_cpy = tab_cpy;
            tabs_list.tab_verified = tab_verified;
            tabs_list.tab_verified_filled = 0;
            
            results[0][tab_sizes_index][test_number] = exec_sort(shell_sort, "Shell sort", &tabs_list, tab_size);
            results[1][tab_sizes_index][test_number] = exec_sort(merge_sort, "Merge sort", &tabs_list, tab_size);
            results[2][tab_sizes_index][test_number] = exec_sort(heap_sort, "Heap sort", &tabs_list, tab_size);
            results[3][tab_sizes_index][test_number] = exec_sort(quick_sort, "Quick sort", &tabs_list, tab_size);
            results[4][tab_sizes_index][test_number] = exec_sort(intro_sort, "Intro sort", &tabs_list, tab_size);
            
            free_tabs(&tab_original, &tab_cpy, &tab_verified);
        }
    }
    
    if (DISPLAY_RESULT_SUMMARY)
    {
        printf("\n\n|Name|");
        
        for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
            printf("%u|", tab_sizes[tab_sizes_index]);
        
        printf("\n|:-|");
        
        for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
            printf(":-:|");
        
        printf("\n");
        
        display_results("Shell sort", results[0], tab_sizes_length, number_of_tests);
        display_results("Merge sort", results[1], tab_sizes_length, number_of_tests);
        display_results("Heap sort", results[2], tab_sizes_length, number_of_tests);
        display_results("Quick sort", results[3], tab_sizes_length, number_of_tests);
        display_results("Intro sort", results[4], tab_sizes_length, number_of_tests);
    }
    
    free_results(results, 5, tab_sizes_length);
}

void sort_small_arrays(void)
{
    unsigned int        number_of_tests;
    float               ***results;
    tab_type            *tab_original;
    tab_type            *tab_cpy;
    unsigned int        tab_size;
    unsigned int        tab_sizes[10];
    unsigned int        tab_sizes_index;
    unsigned int        tab_sizes_length;
    tab_type            *tab_verified;
    struct tabs_list    tabs_list;
    unsigned int        test_number;
    
    tab_sizes[0] = 10;
    tab_sizes[1] = 20;
    tab_sizes[2] = 30;
    tab_sizes[3] = 40;
    tab_sizes[4] = 50;
    tab_sizes[5] = 60;
    tab_sizes[6] = 70;
    tab_sizes[7] = 80;
    tab_sizes[8] = 90;
    tab_sizes[9] = 100;
    
    tab_sizes_length = 10;
    number_of_tests = 100;
    
    generate_results(&results, 8, tab_sizes_length, number_of_tests);
    
    for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
    {
        tab_size = tab_sizes[tab_sizes_index];
        
        for (test_number = 0; test_number < number_of_tests; test_number++)
        {
            generate_tabs(&tab_original, &tab_cpy, &tab_verified, tab_size);
            
            tabs_list.tab_original = tab_original;
            tabs_list.tab_cpy = tab_cpy;
            tabs_list.tab_verified = tab_verified;
            tabs_list.tab_verified_filled = 0;
            
            results[0][tab_sizes_index][test_number] = exec_sort(bubble_sort, "Bubble sort", &tabs_list, tab_size);
            results[1][tab_sizes_index][test_number] = exec_sort(selection_sort, "Selection sort", &tabs_list, tab_size);
            results[2][tab_sizes_index][test_number] = exec_sort(insertion_sort, "Insertion sort", &tabs_list, tab_size);
            results[3][tab_sizes_index][test_number] = exec_sort(shell_sort, "Shell sort", &tabs_list, tab_size);
            results[4][tab_sizes_index][test_number] = exec_sort(merge_sort, "Merge sort", &tabs_list, tab_size);
            results[5][tab_sizes_index][test_number] = exec_sort(heap_sort, "Heap sort", &tabs_list, tab_size);
            results[6][tab_sizes_index][test_number] = exec_sort(quick_sort, "Quick sort", &tabs_list, tab_size);
            results[7][tab_sizes_index][test_number] = exec_sort(intro_sort, "Intro sort", &tabs_list, tab_size);
            
            free_tabs(&tab_original, &tab_cpy, &tab_verified);
        }
    }
    
    if (DISPLAY_RESULT_SUMMARY)
    {
        printf("\n\n|Name|");
        
        for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
            printf("%u|", tab_sizes[tab_sizes_index]);
        
        printf("\n|:-|");
        
        for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
            printf(":-:|");
        
        printf("\n");
        
        display_results("Bubble sort", results[0], tab_sizes_length, number_of_tests);
        display_results("Selection sort", results[1], tab_sizes_length, number_of_tests);
        display_results("Insertion sort", results[2], tab_sizes_length, number_of_tests);
        display_results("Shell sort", results[3], tab_sizes_length, number_of_tests);
        display_results("Merge sort", results[4], tab_sizes_length, number_of_tests);
        display_results("Heap sort", results[5], tab_sizes_length, number_of_tests);
        display_results("Quick sort", results[6], tab_sizes_length, number_of_tests);
        display_results("Intro sort", results[7], tab_sizes_length, number_of_tests);
    }
    
    free_results(results, 8, tab_sizes_length);
}
