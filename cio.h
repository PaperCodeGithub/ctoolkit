#ifndef CIO_H
#define CIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <stdbool.h>


char *cio_input(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    
    char *buffer = (char*) malloc(1024);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    if (fgets(buffer, 1024, stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        return buffer;
    }

    free(buffer);
    return NULL;
}

int to_int(const char *str) {
    return atoi(str);
}

float to_float(const char *str) {
    return atof(str);
}

bool file_exists(const char* path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

char* read_file(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buffer = malloc(length + 1);
    if (buffer) {
        fread(buffer, 1, length, f);
        buffer[length] = '\0';
    }
    fclose(f);
    return buffer;
}

void write_file(const char* filename, const char* format, ...) {
    FILE* f = fopen(filename, "wb");
    if (f) {
        va_list args;
        va_start(args, format);
        
        vfprintf(f, format, args);
        
        va_end(args);
        fclose(f);
        fclose(f);
    }
}

void append_file(const char* filename, const char* format, ...) {
    FILE* f = fopen(filename, "a");
    if (f) {
        va_list args;
        va_start(args, format);
        
        vfprintf(f, format, args);
        
        va_end(args);
        fclose(f);
        fclose(f);
    }
}

void delete_file(const char* filename) {
    remove(filename);
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[H\033[J");
    #endif
}

void print_progress(int current, int total) {
    int percentage = (current * 100) / total;
    int width = 20;
    int progress = (current * width) / total;

    printf("\r[");
    for (int i = 0; i < width; i++) {
        if (i < progress) printf("=");
        else printf(" ");
    }
    printf("] %d%%", percentage);
    fflush(stdout);
}

#endif