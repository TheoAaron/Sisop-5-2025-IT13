#ifndef __SHELL_H__
#define __SHELL_H__

#include "std_type.h"

void shell();
void parseCommand(char *buf, char *cmd, char arg[2][64]);
void running(char *cmd, char *buf, char arg[2][64]);
void userName(char *word);
void generateResponse();

// Tambahkan fungsi bila perlu

#endif // __SHELL_H__
