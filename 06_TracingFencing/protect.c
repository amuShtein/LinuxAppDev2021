#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

typedef int (*unlink_t) (const char *pathname);

int contains(const char *str, const char *substr) {
    int len = strlen(str);
    int sub_len = strlen(substr);

    if(len < sub_len) {
        return 0;
    }  

    int match;

    for(int i = 0; i <= len - sub_len; i++) {
        match = 1;

        for(int j = 0; j < sub_len; j++) {
            if (str[i + j] != substr[j]) {
                match = 0;
                break;
            }
        }

        if(match) {
            return 1;
        }
    }

    return 0;
}

int unlink(const char *pathname) {
    if (!contains(pathname, "PROTECT")) {
        unlink_t orig_unlink;

        orig_unlink = (unlink_t) dlsym(RTLD_NEXT, "unlink");
        return orig_unlink(pathname);
    }
}