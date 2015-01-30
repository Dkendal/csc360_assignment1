#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "task.h"

// arg_str
//  the string to be parsed
// argv
//  an initialized array of pointers to each individual token, each tokens are
//  malloc'd strings and will need to be freed after use
void task_init(char *arg_str, struct task *task_params) {
  char **argv, *tok;
  int count, size;

  memset(task_params, 0, sizeof(struct task));


  size = 1;
  argv = (char **) malloc(sizeof(char *) * size);

  // split the string into " " seperated tokens place each token in subsequent
  // indices of argv
  for(count = 0, tok = strtok(arg_str, " ");
      tok != NULL;
      tok = strtok(NULL, " "), count++){

    //resize if nessecary
    if(count >= size - 1) {
      size = size * 2;
      argv = (char **) realloc(argv, sizeof(char *) * size);
    }

    argv[count] = (char *) malloc(1 + strlen(tok));
    strcpy(argv[count], tok);
  }

  argv[count] = 0;

  if(!strcmp(argv[count - 1], "&")) {
    task_params->run_in_bg = 1;
    free(argv[count - 1]);
    argv[count - 1] = 0;
  }
  else {
    task_params->run_in_bg = 0;
  }

  task_params->argv = argv;
  task_params->cmd = argv[0];
}

void task_free(struct task *task_params) {
  int i;
  char **curr_arg;
  for(curr_arg = task_params->argv, i = 0;
      *curr_arg != NULL && i < MAX_ARGS;
      curr_arg++, i++) {
    free(*curr_arg);
  }
  free(task_params->argv);
}

pid_t task_spawn_handler(struct task task_params, TaskHandler handler) {
  pid_t pid;

  pid = fork();
  if (pid == 0) {
    if(handler(task_params) == -1) {
      fprintf(stderr, "RSI: ");
      perror(task_params.cmd);
    }
    exit(1);
  }
  return pid;
}

int task_exec(struct task task_params) {
  return execvp(task_params.cmd, task_params.argv);
}

int task_supervisor(struct task task_params) {
  pid_t pid;
  int status;
  pid = task_spawn_handler(task_params, task_exec);
  printf("\n[%d]\n", pid);
  waitpid(pid, &status, 0);
  printf("[%d] process finished\n", pid);
  return 1;
}

pid_t task_run(struct task task_params) {
  int status;
  if (task_params.run_in_bg) {
    return task_spawn_handler(task_params, task_supervisor);
  }
  else {
    waitpid(task_spawn_handler(task_params, task_exec), &status, 0);
  }
  return 0;
}
