/* This file contains all array operations */
#ifndef CARRAY
#define CARRAY
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef enum{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING
} type_t;

typedef struct Array{
    int size;
    type_t type;
    void *data;
} array;

/* Basic Array Ops */
// This function creates an array of given size and type
array* create_array(int size, type_t type){
    array *arr = (array*)malloc(sizeof(array));
    arr->size = size;
    arr->type = type;
    switch(type){
        case TYPE_INT:
            arr->data = malloc(size * sizeof(int));
            break;
        case TYPE_FLOAT:
            arr->data = malloc(size * sizeof(float));
            break;
        case TYPE_DOUBLE:
            arr->data = malloc(size * sizeof(double));
            break;
        case TYPE_CHAR:
            arr->data = malloc(size * sizeof(char));
            break;
        case TYPE_STRING:
            arr->data = malloc(size * sizeof(char*));
            break;
    }
    return arr;
}

// This function fills the array with given values
void fill_array(array *arr, ...){
    va_list valist;
    va_start(valist, arr);
    for(int i = 0; i < arr->size; i++){
        switch(arr->type){
            case TYPE_INT:
                ((int*)arr->data)[i] = va_arg(valist, int);
                break;
            case TYPE_FLOAT:
                ((float*)arr->data)[i] = (float)va_arg(valist, double);
                break;
            case TYPE_DOUBLE:
                ((double*)arr->data)[i] = va_arg(valist, double);
                break;
            case TYPE_CHAR:
                ((char*)arr->data)[i] = (char)va_arg(valist, int);
                break;
            case TYPE_STRING:
                ((char**)arr->data)[i] = va_arg(valist, char*);
        }
    }
    
    va_end(valist);
}

// This function creates and returns an array filled with random values
array* create_filled_array(int size, type_t type){
    srand(time(NULL));
    array *arr = create_array(size, type);
    for(int i = 0; i < size; i++){
        switch(type){
            case TYPE_INT:
                ((int*)arr->data)[i] = rand() % 100;
                break;
            case TYPE_FLOAT:
                ((float*)arr->data)[i] = (float)(rand() % 100) / 3.0f;
                break;
            case TYPE_DOUBLE:
                ((double*)arr->data)[i] = (double)(rand() % 100) / 7.0;
                break;
            case TYPE_CHAR:
                ((char*)arr->data)[i] = (char)(rand() % 26 + 65);
                break;
            case TYPE_STRING:
                // For simplicity, filling with single character strings
                {
                    char *str = (char*)malloc(2 * sizeof(char));
                    str[0] = (char)(rand() % 26 + 65);
                    str[1] = '\0';
                    ((char**)arr->data)[i] = str;
                }
                break;
        }
    }
    return arr;
}

// This function frees the allocated memory for the array
void free_array(array *arr){
    if (arr->type == TYPE_STRING) {
        for (int i = 0; i < arr->size; i++) {
            free(((char**)arr->data)[i]);
        }
    }
    free(arr->data);
    free(arr);
}


/* Array element manipulations */

// This function adds a new element at the end of the array
void add_new_element(void *data, array *arr){
    arr->size += 1;
    arr->data = realloc(arr->data, arr->size * 
        (arr->type == TYPE_INT ? sizeof(int) : 
        arr->type == TYPE_FLOAT ? sizeof(float) : 
        arr->type == TYPE_DOUBLE ? sizeof(double) : sizeof(char)));
    switch(arr->type){
        case TYPE_INT:
            ((int*)arr->data)[arr->size - 1] = *(int*)data;
            break;
        case TYPE_FLOAT:
            ((float*)arr->data)[arr->size - 1] = *(float*)data;
            break;
        case TYPE_DOUBLE:
            ((double*)arr->data)[arr->size - 1] = *(double*)data;
            break;
        case TYPE_CHAR:
            ((char*)arr->data)[arr->size - 1] = *(char*)data;
            break;
        case TYPE_STRING:
            ((char**)arr->data)[arr->size - 1] = *(char**)data;
    }
}

// This function puts an element at a given position in the array and overwrites existing data
void push_element_at_pos(int pos, void *data, array *arr){
    if(pos < 0 || pos > arr->size){
        fprintf(stderr,"Index out of bounds\n");
        return;
    }
    switch(arr->type){
        case TYPE_INT:
            ((int*)arr->data)[pos] = *(int*)data;
            break;
        case TYPE_FLOAT:
            ((float*)arr->data)[pos] = *(float*)data;
            break;
        case TYPE_DOUBLE:
            ((double*)arr->data)[pos] = *(double*)data;
            break;
        case TYPE_CHAR:
            ((char*)arr->data)[pos] = *(char*)data;
            break;
        case TYPE_STRING:
            ((char**)arr->data)[pos] = *(char**)data;
    }
}

void delete_element_at_pos(int pos, array *arr){
    if(pos < 0 || pos >= arr->size){
        fprintf(stderr,"Index out of bounds\n");
        return;
    }
    for(int i = pos; i < arr->size - 1; i++){
        switch(arr->type){
            case TYPE_INT:
                ((int*)arr->data)[i] = ((int*)arr->data)[i + 1];
                break;
            case TYPE_FLOAT:
                ((float*)arr->data)[i] = ((float*)arr->data)[i + 1];
                break;
            case TYPE_DOUBLE:
                ((double*)arr->data)[i] = ((double*)arr->data)[i + 1];
                break;
            case TYPE_CHAR:
                ((char*)arr->data)[i] = ((char*)arr->data)[i + 1];
                break;
            case TYPE_STRING:
                ((char**)arr->data)[i] = ((char**)arr->data)[i + 1];
        }
    }
    arr->size -= 1;
    arr->data = realloc(arr->data, arr->size * 
        (arr->type == TYPE_INT ? sizeof(int) : 
        arr->type == TYPE_FLOAT ? sizeof(float) : 
        arr->type == TYPE_DOUBLE ? sizeof(double) : sizeof(char)));
}

// This function gets the size of the array
size_t get_size(array *arr){
    return arr->size;
}

// This function returns the array ekement at a given position
void* get_element_at_pos(int pos, array *arr){
    if(pos < 0 || pos >= arr->size){
        fprintf(stderr,"Index out of bounds\n");
        return NULL;
    }
    switch(arr->type){
        case TYPE_INT:
            return &((int*)arr->data)[pos];
        case TYPE_FLOAT:
            return &((float*)arr->data)[pos];
        case TYPE_DOUBLE:
            return &((double*)arr->data)[pos];
        case TYPE_CHAR:
            return &((char*)arr->data)[pos];
        case TYPE_STRING:
            return &((char**)arr->data)[pos];
    }
    return NULL;
}

/* Print Functions */

// This function prints the array elements
void print_array(array *arr){
    printf("{");
    for(int i = 0; i < arr->size; i++){
        switch(arr->type){
            case TYPE_INT:
                printf(" %d ", ((int*)arr->data)[i]);
                break;
            case TYPE_FLOAT:
                printf(" %f ", ((float*)arr->data)[i]);
                break;
            case TYPE_DOUBLE:
                printf(" %lf ", ((double*)arr->data)[i]);
                break;
            case TYPE_CHAR:
                printf( "%c ", ((char*)arr->data)[i]);
                break;
            case TYPE_STRING:
                printf(" %s ", ((char**)arr->data)[i]);
                break;
        }
    }
    printf("} \n");
}

void print_element_at_pos(int pos, array *arr){
    if(pos < 0 || pos >= arr->size){
        fprintf(stderr,"Index out of bounds\n");
        return;
    }
    switch(arr->type){
        case TYPE_INT:
            printf("%d\n", ((int*)arr->data)[pos]);
            break;
        case TYPE_FLOAT:
            printf("%f\n", ((float*)arr->data)[pos]);
            break;
        case TYPE_DOUBLE:
            printf("%lf\n", ((double*)arr->data)[pos]);
            break;
        case TYPE_CHAR:
            printf("%c\n", ((char*)arr->data)[pos]);
            break;
        case TYPE_STRING:
            printf("%s\n", ((char**)arr->data)[pos]);
            break;
    }
}

/* Scan functions */
void get_array_input(array *arr){
    for(int i = 0; i < arr->size; i++){
        switch(arr->type){
            case TYPE_INT:
                scanf("%d", &((int*)arr->data)[i]);
                break;
            case TYPE_FLOAT:
                scanf("%f", &((float*)arr->data)[i]);
                break;
            case TYPE_DOUBLE:
                scanf("%lf", &((double*)arr->data)[i]);
                break;
            case TYPE_CHAR:
                scanf(" %c", &((char*)arr->data)[i]);
                break;
            case TYPE_STRING:
                {
                    char buffer[100];
                    scanf("%s", buffer);
                    ((char**)arr->data)[i] = strdup(buffer);
                }
        }
    }
}

void get_element_input_at_pos(int pos, array *arr){
    if(pos < 0 || pos >= arr->size){
        fprintf(stderr,"Index out of bounds\n");
        return;
    }
    switch(arr->type){
        case TYPE_INT:
            scanf("%d", &((int*)arr->data)[pos]);
            break;
        case TYPE_FLOAT:
            scanf("%f", &((float*)arr->data)[pos]);
            break;
        case TYPE_DOUBLE:
            scanf("%lf", &((double*)arr->data)[pos]);
            break;
        case TYPE_CHAR:
            scanf(" %c", &((char*)arr->data)[pos]);
            break;
        case TYPE_STRING:
            {
                char buffer[100];
                scanf("%s", buffer);
                ((char**)arr->data)[pos] = strdup(buffer);
            }
    }
}

/* Search Algorithms */

// This function searches for a value in the array and returns its position
void search_pos_by_value(void *value, array *arr, int *indexs, int *count){
    int found = 0;
    for(int i = 0; i < arr->size; i++){
        switch(arr->type){
            case TYPE_INT:
                if(((int*)arr->data)[i] == *(int*)value){
                    indexs[found++] = i;
                }
                break;
            case TYPE_FLOAT:
                if(((float*)arr->data)[i] == *(float*)value){
                    indexs[found++] = i;
                }
                break;
            case TYPE_DOUBLE:
                if(((double*)arr->data)[i] == *(double*)value){
                    indexs[found++] = i;
                }
                break;
            case TYPE_CHAR:
                if(((char*)arr->data)[i] == *(char*)value){
                    indexs[found++] = i;
                }
                break;
            case TYPE_STRING:
                if(strcmp(((char**)arr->data)[i], *(char**)value) == 0){
                    indexs[found++] = i;
                }
                break;
        }
    }
    *count = found;
}

// This function searches for a value in the array and returns 1 if found, else 0
int search_value_exists(void *value, array *arr){
    for(int i = 0; i < arr->size; i++){
        switch(arr->type){
            case TYPE_INT:
                if(((int*)arr->data)[i] == *(int*)value){
                    return 1;
                }
                break;
            case TYPE_FLOAT:
                if(((float*)arr->data)[i] == *(float*)value){
                    return 1;
                }
                break;
            case TYPE_DOUBLE:
                if(((double*)arr->data)[i] == *(double*)value){
                    return 1;
                }
                break;
            case TYPE_CHAR:
                if(((char*)arr->data)[i] == *(char*)value){
                    return 1;
                }
                break;
            case TYPE_STRING:
                if(strcmp(((char**)arr->data)[i], *(char**)value) == 0){
                    return 1;
                }
                break;
        }
    }
    return 0;
}

// This function searches for a value in the array at a given index and returns 1 if found, else 0
int search_value_at_index(void *value, int index, array *arr){
    if(index < 0 || index >= arr->size){
        fprintf(stderr,"Index out of bounds\n");
        return 0;
    }
    switch(arr->type){
        case TYPE_INT:
            return ((int*)arr->data)[index] == *(int*)value;
        case TYPE_FLOAT:
            return ((float*)arr->data)[index] == *(float*)value;
        case TYPE_DOUBLE:
            return ((double*)arr->data)[index] == *(double*)value;
        case TYPE_CHAR:
            return ((char*)arr->data)[index] == *(char*)value;
        case TYPE_STRING:
            return strcmp(((char**)arr->data)[index], *(char**)value) == 0;
    }
    return 0;
}



/* Sorting Algorithms */
// This function sorts the array using Bubble Sort
int compare_elements(array *arr, int idx1, int idx2) {
    switch(arr->type) {
        case TYPE_INT:    return ((int*)arr->data)[idx1] - ((int*)arr->data)[idx2];
        case TYPE_FLOAT:  return (((float*)arr->data)[idx1] > ((float*)arr->data)[idx2]) - (((float*)arr->data)[idx1] < ((float*)arr->data)[idx2]);
        case TYPE_DOUBLE: return (((double*)arr->data)[idx1] > ((double*)arr->data)[idx2]) - (((double*)arr->data)[idx1] < ((double*)arr->data)[idx2]);
        case TYPE_CHAR:   return ((char*)arr->data)[idx1] - ((char*)arr->data)[idx2];
        case TYPE_STRING: return strcmp(((char**)arr->data)[idx1], ((char**)arr->data)[idx2]);
        default: return 0;
    }
}

void swap_elements(array *arr, int idx1, int idx2) {
    if (idx1 == idx2) return;
    switch(arr->type) {
        case TYPE_INT: {
            int temp = ((int*)arr->data)[idx1];
            ((int*)arr->data)[idx1] = ((int*)arr->data)[idx2];
            ((int*)arr->data)[idx2] = temp;
            break;
        }
        case TYPE_FLOAT: {
            float temp = ((float*)arr->data)[idx1];
            ((float*)arr->data)[idx1] = ((float*)arr->data)[idx2];
            ((float*)arr->data)[idx2] = temp;
            break;
        }
        case TYPE_DOUBLE: {
            double temp = ((double*)arr->data)[idx1];
            ((double*)arr->data)[idx1] = ((double*)arr->data)[idx2];
            ((double*)arr->data)[idx2] = temp;
            break;
        }
        case TYPE_CHAR: {
            char temp = ((char*)arr->data)[idx1];
            ((char*)arr->data)[idx1] = ((char*)arr->data)[idx2];
            ((char*)arr->data)[idx2] = temp;
            break;
        }
        case TYPE_STRING: {
            char *temp = ((char**)arr->data)[idx1];
            ((char**)arr->data)[idx1] = ((char**)arr->data)[idx2];
            ((char**)arr->data)[idx2] = temp;
            break;
        }
    }
}

// Partitioning logic (Lomuto partition scheme)

void quick_sort_recursive(array *arr, int low, int high) {
    if (low < high) {
        int pivot_idx = high; 
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (compare_elements(arr, j, pivot_idx) < 0) {
                i++;
                swap_elements(arr, i, j);
            }
        }
        swap_elements(arr, i + 1, high);
        int pi = i + 1;

        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

void sort_array(array *arr) {
    if (arr == NULL || arr->size < 2) return;
    quick_sort_recursive(arr, 0, arr->size - 1);
}

#endif