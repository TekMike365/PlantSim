#include <stdio.h>

#include "cli.h"

int main() {
    printf("Running PlantSim!\n");

    int err = cli_run();
    if (err)
        printf("Error (%d): %s\n", err, cli_error_msg(err));
    return err;
}
