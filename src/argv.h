#ifndef ARGV_H
#define ARGV_H
#define MAX_ARGS 256 // lazy, assume no more than 256 options
struct task {
  char *cmd;
  char **argv;
  int run_in_bg;
};

void init_argv(char *arg_str, struct task *task_params);
void free_argv(struct task *task_params);
#endif
