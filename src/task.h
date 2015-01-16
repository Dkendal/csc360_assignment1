#ifndef ARGV_H
#define ARGV_H
#define MAX_ARGS 256 // lazy, assume no more than 256 options
struct task {
  char *cmd;
  char **argv;
  int run_in_bg;
};

typedef int (TaskHandler(struct task));

int task_exec(struct task task_params);
int task_supervisor(struct task task_params);
pid_t task_spawn_handler(struct task task_params, TaskHandler handler);
void task_free(struct task *task_params);
void task_init(char *arg_str, struct task *task_params);
void task_run(struct task task_params);
#endif
