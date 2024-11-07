#ifndef CONSOLE_H
#define CONSOLE_H

#define CLI_OK 0
#define CLI_INPUT_READ_ERR 1

const char* cli_error_msg(int err);
int cli_run();

#endif
