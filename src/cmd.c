#include "cmd.h"

#include <string.h>
#include <stdio.h>

#define CREATE_ALIASES(x, c, ...)\
const char* aliasv_ ## x[] = {__VA_ARGS__};\
const int aliasc_ ## x = c;

struct Cmd {
    int aliasc;
    const char** aliasv;
    int (*exec)(int argc, const char** argv);
};

CREATE_ALIASES(test, 1, "test")
int exec_test(int argc, const char** argv) {
    printf("test command\n");
    printf("args: %d\n", argc);
    for (int i = 0; i < argc; ++i)
        printf("%d: %s\n", i + 1, argv[i]);
    return CMD_TEST_ERROR;
}

const int cmdc = 1;
const struct Cmd cmdv[] = {
    { aliasc_test, aliasv_test, exec_test }
};

const char* cmd_error_msg(int err) {
    switch(err)
    {
    case CMD_OK: return "OK.";
    case CMD_UNKNOWN_COMMAND: return "Unknown command.";
    case CMD_TEST_ERROR: return "Nice.";
    }
    return "Unknown error.";
}

int cmd_compare(const char* alias, struct Cmd cmd) {
    for (int i = 0; i < cmd.aliasc; ++i) {
        if (!strcmp(alias, cmd.aliasv[i]))
            return 1;
    }

    return 0;
}

int cmd_dispatch(const char* alias, int argc, const char** argv) {
    int idx = -1;

    for (int i = 0; i < cmdc; ++i) {
        if (cmd_compare(alias, cmdv[i])) {
            idx = i;
            break;
        }
    }

    if (idx < 0)
        return CMD_UNKNOWN_COMMAND;

    return cmdv[idx].exec(argc, argv);
}

