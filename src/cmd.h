#ifndef CMD_H
#define CMD_H

#define CMD_OK 0
#define CMD_UNKNOWN_COMMAND 1
#define CMD_TEST_ERROR 69

const char* cmd_error_msg(int err);
int cmd_dispatch(const char* alias,  int argc, const char** argv);

#endif
