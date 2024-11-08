#include "cli.h"

#include <stdio.h>
#include <string.h>

const char* cli_error_msg(int err) {
    switch (err) {
    case CLI_OK: return "OK.";
    case CLI_INPUT_READ_ERR: return "Couldn't read from stdin.";
    }
    return "Unknown error.";
}

int cli_init(int cmdc, struct Cmd* cmdv) {
    cmd_set_cmdv(cmdc, cmdv);
    return CLI_OK;
}

int cli_run() {
    const int buff_size = 1024;
    char buff[buff_size];
    char* argv[buff_size / 2];

    while (1) {
        buff[0] = '\0';

        printf(">");
        if (!fgets(buff, 1024, stdin))
            return CLI_INPUT_READ_ERR;

        // split the string into arguments
        int argc = 0;
        int first = 1;
        for (int i = 0; i < buff_size; ++i) {
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

        if (!strcmp(argv[0], "exit"))
            return CLI_OK;

        int err = cmd_dispatch(argv[0], argc - 1, (const char**)&argv[1]);
        if (err)
            printf("Error (%d): %s\n", err, cmd_error_msg(err));
    }

    return CLI_OK;
}
