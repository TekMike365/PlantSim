#include <stdio.h>

#include "cli.h"

const int aliasc_test = 1;
const char* aliasv_test[] = {"test"};
int exec_test(int argc, const char** argv) {
    printf("test:");
    for (int i = 0; i < argc; ++i)
        printf(" %s", argv[i]);
    printf("\n");
    return 0;
}

const int cmdc = 1;
const struct Cmd cmdv[] = {
    {aliasc_test, aliasv_test, exec_test}
};

int main() {
    printf("Running PlantSim!\n");

    int err = cli_init(cmdc, cmdv);
    if (err) {
        printf("Error (%d): %s\n", err, cli_error_msg(err));
        return 1;
    }

    err = cli_run();
    if (err)
        printf("Error (%d): %s\n", err, cli_error_msg(err));
    return err;
}
