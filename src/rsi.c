#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "path.h"
#include "prompt.h"
#include "task.h"

// execute the command denoted in cmd
void exec(char * cmd) {
  struct task task_params;

  task_init(cmd, &task_params);

  if(!strcmp(task_params.cmd, "cd")) {
    if(!change_dir(task_params.argv[1])) {
      perror(task_params.cmd);
    }
  }
  else {
    task_run(task_params);
  }

  task_free(&task_params);
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
