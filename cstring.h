#ifndef CSTRING_H

#define CSTRING_H

#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "carray.h"

char* str_lower(char *str) {
    if (!str) return NULL;
    for (int i = 0; str[i]; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
    return str;
}

char* str_upper(char *str) {
    if (!str) return NULL;
    for (int i = 0; str[i]; i++) {
        str[i] = (char)toupper((unsigned char)str[i]);
    }
    return str;
}

int str_starts_with(const char *str, const char *prefix) {
    if (!str || !prefix) return 0;
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

int str_ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) return 0;
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    if (suffix_len > str_len) return 0;
    return strcmp(str + str_len - suffix_len, suffix) == 0;
}

int str_is_numeric(const char *str) {
    if (!str || *str == '\0') return 0;
    while (*str) {
        if (!isdigit((unsigned char)*str)) return 0;
        str++;
    }
    return 1;
}

int str_is_alpha(const char *str) {
    if (!str || *str == '\0') return 0;
    while (*str) {
        if (!isalpha((unsigned char)*str)) return 0;
        str++;
    }
    return 1;
}


array* str_split(const char *str, const char token) {
    array *arr = create_array(0, TYPE_STRING);
    
    int len = strlen(str);
    char buffer[1024];
    int buffer_idx = 0;

    for (int i = 0; i <= len; i++) {
        if (str[i] == token || str[i] == '\0') {
        
            buffer[buffer_idx] = '\0';
            char *word = strdup(buffer);
            add_new_element(&word, arr);
            buffer_idx = 0;
        
        } else {
            if (buffer_idx < 1023) {
                buffer[buffer_idx++] = str[i];
            }
        }
    }

    return arr;
}

char* str_trim(const char *str) {
    if (str == NULL) return NULL;

    int start = 0;
    int end = strlen(str) - 1;

    while (str[start] != '\0' && isspace((unsigned char)str[start])) {
        start++;
    }

    while (end >= start && isspace((unsigned char)str[end])) {
        end--;
    }

    int len = (end - start) + 1;
    if (len <= 0) return strdup("");

    char *trimmed = (char*)malloc(len + 1);
    if (trimmed) {
        strncpy(trimmed, str + start, len);
        trimmed[len] = '\0';
    }

    return trimmed;
}

int str_contains(const char *haystack, const char *needle) {
    if (!haystack || !needle) return 0;
    return strstr(haystack, needle) != NULL;
}

int str_count(const char *str, const char *sub) {
    if (!str || !sub || *sub == '\0') return 0;
    int count = 0;
    const char *tmp = str;
    while ((tmp = strstr(tmp, sub))) {
        count++;
        tmp += strlen(sub);
    }
    return count;
}

void str_shuffle(char *str) {
    if (!str) return;
    int n = strlen(str);
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

char* str_replace(const char *str, const char *old_sub, const char *new_sub) {
    char *result;
    int i, count = 0;
    int new_len = strlen(new_sub);
    int old_len = strlen(old_sub);

    for (i = 0; str[i] != '\0'; i++) {
        if (strstr(&str[i], old_sub) == &str[i]) {
            count++;
            i += old_len - 1;
        }
    }

    result = (char*)malloc(i + count * (new_len - old_len) + 1);
    if (!result) return NULL;

    i = 0;
    while (*str) {
        if (strstr(str, old_sub) == str) {
            strcpy(&result[i], new_sub);
            i += new_len;
            str += old_len;
        } else {
            result[i++] = *str++;
        }
    }
    result[i] = '\0';
    return result;
}

void str_rev(char *str) {
    if (!str) return;
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

#endif