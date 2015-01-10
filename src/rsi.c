#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "prompt.h"
#include "path.h"
#include "argv.h"

// execute the command denoted in cmd
void exec(char * cmd) {
  char *argv[MAX_ARGS] = {};
  int retval = 0, status;
  pid_t pid;

  init_argv(cmd, argv);

  if(!strcmp(argv[0], "cd")) {
    retval = change_dir(argv[1]);
  }
  else {
    pid = fork();
    waitpid(pid, &status, 0); // wait so output comes before prompt
    if(!pid) retval = execvp(argv[0], argv);
  }

  //check for errors
  if(retval) {
    perror(cmd);
  }

  free_argv(argv);
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
