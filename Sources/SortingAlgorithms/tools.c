//  tools.c
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "tools.h"

void    display_tab(tab_type *tab, tab_type *tab_cpy, unsigned int size);
int     is_tab_sorted(tab_type *tab, unsigned int size);
int     is_tab_sorted_like_others_sorts(tab_type *tab, tab_type *tab_verified, unsigned int size);

void display_tab(tab_type *tab, tab_type *tab_cpy, unsigned int size)
{
    unsigned int    i;

    puts("--------------------------------------");
    puts("   Index    |   Sorted   |  Original  |");
    puts("------------|------------|------------|");
    
    i = 0;
    while (i < size)
    {
        printf("%10u. | %10u | %10u |\n", i, tab[i], tab_cpy[i]);
        i++;
    }
}

void display_results(char *name, float **results, unsigned int tab_sizes_length, unsigned int number_of_tests)
{
    float           average;
    unsigned int    tab_sizes_index;
    unsigned int    test_number;
    
    printf("|%s|", name);
    
    for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
    {
        average = 0;
        for (test_number = 0; test_number < number_of_tests; test_number++)
            average += results[tab_sizes_index][test_number];
        
        average /= number_of_tests;
        
        printf("%f|", average);
    }
    
    printf("\n");
}

float exec_sort(void(*sort)(tab_type *, unsigned int), char *name, struct tabs_list *tabs_list, unsigned int size)
{
    clock_t time_begin;
    clock_t time_end;
    float   time;
    
    memcpy(tabs_list->tab_cpy, tabs_list->tab_original, size);
   
    time_begin = clock();
    sort(tabs_list->tab_cpy, size);
    time_end = clock();
    
    if (DISPLAY_TABS_RESULT)
        display_tab(tabs_list->tab_cpy, tabs_list->tab_original, size);
    
    time = (float)(time_end - time_begin) / CLOCKS_PER_SEC;
    
    if (!tabs_list->tab_verified_filled)
    {
        if (is_tab_sorted(tabs_list->tab_cpy, size))
        {
            memcpy(tabs_list->tab_verified, tabs_list->tab_cpy, size);
            tabs_list->tab_verified_filled = 1;
            
            if (DISPLAY_EXEC_TIME)
                printf("%s's time: %f\n", name, time);
        }
        else
        {
            printf("%s: ERROR\n", name);
            time = -1;
        }
    }
    else
    {
        if (!is_tab_sorted_like_others_sorts(tabs_list->tab_cpy, tabs_list->tab_verified, size))
        {
            printf("%s: ERROR\n", name);
            time = -1;
        }
        else if (DISPLAY_EXEC_TIME)
            printf("%s's time: %f\n", name, time);
    }
    
    return (time);
}

void free_results(float ***results, unsigned int number_of_sorting, unsigned int tab_sizes_length)
{
    unsigned int    sorting_number;
    unsigned int    tab_sizes_index;
    
    for (sorting_number = 0; sorting_number < number_of_sorting; sorting_number++)
    {
        for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
            free(results[sorting_number][tab_sizes_index]);
        
        free(results[sorting_number]);
    }
    
    free(results);
}

void free_tabs(tab_type **tab_original, tab_type **tab_cpy, tab_type **tab_verified)
{
    free(*tab_original);
    free(*tab_cpy);
    free(*tab_verified);
    
    *tab_original = NULL;
    *tab_cpy = NULL;
    *tab_verified = NULL;
}

void generate_results(float ****results, unsigned int number_of_sorting, unsigned int tab_sizes_length, unsigned int number_of_tests)
{
    unsigned int    sorting_number;
    unsigned int    tab_sizes_index;
    unsigned int    test_number;
    
    if ((*results = malloc(sizeof(**results) * number_of_sorting)) == NULL)
    {
        perror("Malloc error.");
        exit(EXIT_FAILURE);
    }
    
    for (sorting_number = 0; sorting_number < number_of_sorting; sorting_number++)
    {
        if (((*results)[sorting_number] = malloc(sizeof(***results) * tab_sizes_length)) == NULL)
        {
            perror("Malloc error.");
            exit(EXIT_FAILURE);
        }
        
        for (tab_sizes_index = 0; tab_sizes_index < tab_sizes_length; tab_sizes_index++)
        {
            if (((*results)[sorting_number][tab_sizes_index] = malloc(sizeof(****results) * number_of_tests)) == NULL)
            {
                perror("Malloc error.");
                exit(EXIT_FAILURE);
            }
            
            for (test_number = 0; test_number < number_of_tests; test_number++)
                (*results)[sorting_number][tab_sizes_index][test_number] = 0;
        }
    }
}

void generate_tabs(tab_type **tab_original, tab_type **tab_cpy, tab_type **tab_verified, unsigned int size)
{
    unsigned int    i;

    srandom((unsigned int)time(NULL));

    if ((*tab_original = malloc(sizeof(**tab_original) * size)) == NULL)
    {
        perror("Malloc error.");
        exit(EXIT_FAILURE);
    }
    
    if ((*tab_cpy = malloc(sizeof(**tab_cpy) * size)) == NULL)
    {
        perror("Malloc error.");
        exit(EXIT_FAILURE);
    }
    
    if ((*tab_verified = malloc(sizeof(**tab_verified) * size)) == NULL)
    {
        perror("Malloc error.");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (i < size)
    {
        (*tab_original)[i] = random() * 255;
        i++;
    }
}

int is_tab_sorted(tab_type *tab, unsigned int size)
{
    unsigned int    i;

    i = 0;
    while (i < size - 1)
    {
        if (tab[i] > tab[i + 1])
            return (0);

        i++;
    }

    return (1);
}

int is_tab_sorted_like_others_sorts(tab_type *tab, tab_type *tab_verified, unsigned int size)
{
    unsigned int    i;
    
    i = 0;
    while (i < size)
    {
        if (tab[i] != tab_verified[i])
            return (0);
        
        i++;
    }
    
    return (1);
}
