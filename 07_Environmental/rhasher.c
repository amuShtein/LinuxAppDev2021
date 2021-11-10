#include "config.h"
#include <stdlib.h>
#include <string.h>
#include "rhash.h"

#ifndef GETLINE_ENABLE

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#endif

enum { STRSIZE = 1024, OUTPUT_SIZE = 256 };

int main(int argc, char** argv) {
    size_t buf = STRSIZE;
#ifdef GETLINE_ENABLE
    printf("using geline\n");
    char* str = malloc(buf);
#else
    printf("using readline\n");
    char* str = NULL;
#endif
    char digest[OUTPUT_SIZE];
    char output[OUTPUT_SIZE];

    rhash_library_init(); /* initialize static data */
#ifdef GETLINE_ENABLE
    while (getline(&str, &buf, stdin) > 0) {
#else
    while ((str = readline(NULL)) != NULL) {
#endif
        // printf("scanned string: '%s'\n", str);

        char* cmd = (char*)strtok(str, " \n");

        // printf("scanned cmd = '%s':\n", cmd);
    
        int method;
        if(strcasecmp(cmd, "MD5") == 0) {
            method = RHASH_MD5;
        } else if(strcasecmp(cmd, "SHA1") == 0) {
            method = RHASH_SHA1;
        } else if(strcasecmp(cmd, "TTH") == 0) {
            method = RHASH_TTH;
        } else {
            perror("undefined command: '");
            perror(str);
            perror("'\n");
            continue;
        }

        // printf("method: %s\n", rhash_get_name(method));
        int appearance = islower(cmd[0]) ? RHPR_BASE64 : RHPR_HEX;

        char* arg = (char*)strtok(NULL, " \n");
        // printf("scanned arg = '%s':\n", arg+1);

        int res;
        if(arg[0] != '\"') {
            res = rhash_file(method, arg, digest);
        } else {
            res = rhash_msg(method, arg+1, strlen(arg+1), digest);
        }

        if(res < 0) {
            perror("rhash error\n");
            continue;
        }

        rhash_print_bytes(output, digest, rhash_get_digest_size(method),
            (appearance));
 
        printf("%s\n", output);

#ifndef GETLINE_ENABLE
    free(str);
#endif
    }
    
#ifdef GETLINE_ENABLE
    free(str);
#endif
}