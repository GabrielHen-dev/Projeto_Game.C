
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avatar_loader.h"

char** load_avatar_from_file(const char* path, int* lines)
{
    if (!path) {
        if (lines) *lines = 0;
        return NULL;
    }

    FILE* f = fopen(path, "r");
    if (!f) {
        if (lines) *lines = 0;
        return NULL;
    }

    size_t cap = 8;
    size_t count = 0;
    char** arr = (char**)malloc(cap * sizeof(char*));
    if (!arr) {
        fclose(f);
        if (lines) *lines = 0;
        return NULL;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), f)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }

        char* line = (char*)malloc(len + 1);
        if (!line) {
            for (size_t i = 0; i < count; ++i) free(arr[i]);
            free(arr);
            fclose(f);
            if (lines) *lines = 0;
            return NULL;
        }
        memcpy(line, buffer, len + 1);

        if (count >= cap) {
            cap *= 2;
            char** tmp = (char**)realloc(arr, cap * sizeof(char*));
            if (!tmp) {
                free(line);
                for (size_t i = 0; i < count; ++i) free(arr[i]);
                free(arr);
                fclose(f);
                if (lines) *lines = 0;
                return NULL;
            }
            arr = tmp;
        }

        arr[count++] = line;
    }

    fclose(f);

    if (count == 0) {
        free(arr);
        if (lines) *lines = 0;
        return NULL;
    }

    char** res = (char**)realloc(arr, count * sizeof(char*));
    if (res) arr = res;
    if (lines) *lines = (int)count;
    return arr;
}
