#ifndef ARGV_H
#define ARGV_H
#define MAX_ARGS 256 // lazy, assume no more than 256 options
void init_argv(char *arg_str, char **argv);
void free_argv(char **argv);
#endif
