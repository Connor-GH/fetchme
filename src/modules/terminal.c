#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "./include/fetchme.h"
#include "./include/color.h"
#include "./include/config.h"

int terminal() {

    extern char **environ;
    char* terminal_emulator = NULL;

    for (size_t i = 0; environ[i] != NULL; i++) {
        char* eq = strchr(environ[i], '=');
        assert(eq != NULL);
        *eq = '\0';

        if (strcmp(environ[i], "TERM") == 0) {
            terminal_emulator = eq + 1;
        }
        *eq = '=';
    }
    if (terminal_emulator == NULL) {
        printf("wrong ENV var directory\n");
        exit(EXIT_FAILURE);
    }
    else {
        printf("%s", color_distro());
        printf("Terminal:\033[0m %s\n", terminal_emulator);
        return 0;
    }
}
