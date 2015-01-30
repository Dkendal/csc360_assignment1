#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../list/src/list.h"

#include "path.h"
#include "prompt.h"
#include "task.h"

// execute the command denoted in cmd
pid_t exec(char * cmd) {
  struct task task_params;
  pid_t supervisor_pid = 0;

  task_init(cmd, &task_params);

  if(!strcmp(task_params.cmd, "cd")) {
    if(!change_dir(task_params.argv[1])) {
      fprintf(stderr, "RSI: ");
      perror(task_params.cmd);
    }
  }
  else {
    supervisor_pid = task_run(task_params);
  }

  task_free(&task_params);
  return supervisor_pid;
}

int start() {
  char *buf, *prompt_str;
  pid_t supervisor_pid = 0;
  list_node_t *node;
  list_iterator_t *it;
  list_t *list = list_new();

  for(;; free(buf)) {
    // reap the zombies
    for(it = list_iterator_new(list, LIST_HEAD); (node = list_iterator_next(it));) {
      int status;
      waitpid(* (pid_t *) node->val, &status, WNOHANG);

      if (WIFEXITED(status) || WIFSIGNALED(status)) {
        list_remove(list, node);
      }
    }

    list_iterator_destroy(it);

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
      supervisor_pid = exec(buf);
    }

    if( supervisor_pid ) {
      list_rpush(list, list_node_new(&supervisor_pid));
    }
  }
  // need to destroy on exit as well
  list_destroy(list);
  return 0;
}

int main() {
  start();
  return 0;
}
