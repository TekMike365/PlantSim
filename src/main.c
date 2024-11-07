#include <stdio.h>

#include "cmd.h"

int main() {
    printf("Hello, World!\n");
    printf(">");

    char buff[1024];
    buff[0] = '\0';
    if (!fgets(buff, 1024, stdin))
        return 1;

    // split the string
    int argc = 0;
    char* argv[1024];
    int first = 1;
    for (int i = 0; i < 1024; ++i) {
        if ('\0' == buff[i])
            break;

        if (first) {
            argv[argc++] = &buff[i];
            first = 0;
        }

        if (' ' == buff[i] || '\n' == buff[i]) {
            buff[i] = '\0';
            first = 1;
        }
    }

    // printf("argc: %d\n", argc);
    // printf("alias: %s, argc: %d, argv: %u\n", argv[0], argc - 1, &argv[1]);
    int err = cmd_dispatch(argv[0], argc - 1, &argv[1]);
    if (err) {
        printf("ERROR (%d): %s\n", err, cmd_error_msg(err));
        return 1;
    }
}
