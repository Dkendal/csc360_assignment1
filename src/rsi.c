#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "prompt.h"
#include "path.h"
#include "argv.h"


typedef int (TaskHandler(struct task));

pid_t spawn_task_handler(struct task task_params, TaskHandler handler, int async) {
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    if(handler(task_params) == -1) {
      perror(task_params.cmd);
    }
    exit(1);
  }
  if (!async) {
    waitpid(pid, &status, 0);
  }
  return pid;
}

int exec_cmd(struct task task_params) {
  return execvp(task_params.cmd, task_params.argv);
}

int task_supervisor(struct task task_params) {
  pid_t pid;
  pid = spawn_task_handler(task_params, exec_cmd, 0);
  printf("[%d] process finished\n", pid);
  return 1;
}

// execute the command denoted in cmd
void exec(char * cmd) {
  struct task task_params;

  init_argv(cmd, &task_params);

  if(!strcmp(task_params.cmd, "cd")) {
    if(!change_dir(task_params.argv[1])) {
      perror(task_params.cmd);
    }
  }
  else {
    if(task_params.run_in_bg) {
      spawn_task_handler(task_params, task_supervisor, 1);
    }
    else {
      spawn_task_handler(task_params, exec_cmd, 0);
    }
  }

  free_argv(&task_params);
}

int start() {
  char *buf, *prompt_str;

  for(;; free(buf)) {
    prompt_str = get_prompt();
    buf = readline(prompt_str);
    free(prompt_str);

    // if  is received exit
    if(buf == NULL) {
      printf("\nGoodbye!");
      exit(0);
    }
    // empty string don't do anything
    else if(strcmp(buf, "") != 0) {
      exec(buf);
    }
  }
  return 0;
}

int main() {
  start();
  return 0;
}
