#include "cmd.h"

#include <string.h>
#include <stdio.h>

static int cmdc = 0;
static const struct Cmd* cmdv = 0;

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

void cmd_set_cmdv(int c, const struct Cmd* v) {
    cmdc = c;
    cmdv = v;
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

