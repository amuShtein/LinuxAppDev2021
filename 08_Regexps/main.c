#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <regex.h>

enum {
    ERR_BUF = 1024,

    PM_MAX = 10
};

char* build_subst(char* fmt, regmatch_t pm[PM_MAX], char* str) {
    int max_matches = 0;
    for(; pm[max_matches].rm_eo != -1 && pm[max_matches].rm_so != -1; max_matches++);

    max_matches--;

    int buf = strlen(fmt);
    char* subst = malloc(buf);
    int i = 0, j = 0;
    char c;
    while ( (c = fmt[i]) != '\0') {
        if(j + 2 >= buf) {
            buf *= 2;
            subst = realloc(subst, buf);
        }

        if(c == '\\' && isdigit(fmt[i+1])) {
            int n = fmt[i+1] - '0';
            // printf("subst %d\n", n);
            if(n <= max_matches) {
                int match_len = pm[n].rm_eo - pm[n].rm_so;

                if(j + match_len + 1 >= buf) {
                    buf = buf + match_len + 1;
                    subst = realloc(subst, buf);
                }

                for(int k = pm[n].rm_so; k < pm[n].rm_eo; k++) {
                    subst[j++] = str[k];
                    // printf("[%c]", subst[j-1]);
                }
            } else {
                free(subst);
                return NULL;
            }
            
            i++;
        } else {
            subst[j++] = c;
            // printf("[%c]", subst[j-1]);
            if(c == '\\' && fmt[i+1] == '\\') {
                i++;
            }
        }
        
        i++;
    }
    // putchar('\n');
    subst[j] = '\0';
    subst = realloc(subst, j+1);
    return subst;
}

int main(int argc, char** argv) {
    if(argc != 4) {
        printf("required exactly 3 arguments\n");

        return 0;
    }

    regex_t r;
    int err = regcomp(&r, argv[1], REG_EXTENDED);

    if(err != 0) {
        char errbuf[ERR_BUF];
        regerror(err, &r, errbuf, ERR_BUF);

        perror(errbuf);
        return 1;
    }

    regmatch_t pm[PM_MAX];

    err = regexec(&r, argv[2], PM_MAX, pm, 0);
    if(err == 0) {
        // for(int i = 0; i < PM_MAX; i++) {
        //     int start = pm[i].rm_so;
        //     int end = pm[i].rm_eo;

        //     if(start != -1 && end != -1) {
        //         printf("%d: %d[%c] - %d[%c]\n", i, pm[i].rm_so, argv[2][pm[i].rm_so], pm[i].rm_eo, argv[2][pm[i].rm_eo]);
        //     }
        // }

        char* subst = build_subst(argv[3], pm, argv[2]);
        // printf("subst = '%s'\n", subst);

        char* res = malloc(strlen(argv[2]) + strlen(subst) + 1);
        
        int j;
        int start = pm[0].rm_so;
        for(; j < start; j++) {
            res[j] = argv[2][j];
        }

        int subst_len = strlen(subst);
        for(j = 0; j < subst_len; j++) {
            res[start + j] = subst[j];
        }

        j += start;
        int str_len = strlen(argv[2]);
        for(int i = pm[0].rm_eo; i < str_len; i++) {
            res[j++] = argv[2][i];
        }

        printf("%s\n", res);
    } else {
        if(err != 0) {
        char errbuf[ERR_BUF];
        regerror(err, &r, errbuf, ERR_BUF);

        perror(errbuf);
        return 2;
        }
    }

    return 0;
}