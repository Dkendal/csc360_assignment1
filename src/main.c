#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "prompt.h"

// execut the command denoted in cmd
void exec(char * cmd) {
  char *argv[1] = { "" };
  int retval;
  retval = execvp(cmd, argv);
  if(retval == -1) {
    perror(cmd);
  }
}

int start() {
  int status;
  pid_t pid;
  char *buf, *prompt_str;

  for(pid = 1; pid != 0; free(buf)) {
    prompt_str = get_prompt();
    buf = readline(prompt_str);
    free(prompt_str);

    // if  is received exit
    if(buf == NULL) {
      printf("\nGoodbye!");
      exit(0);
    }
    // empty string don't do anything
    else if(strcmp(buf, "") == 0) {
      continue;
    }

    pid = fork();

    if(pid == 0) {
      exec(buf);
    }
    else {
      waitpid(pid, &status, 0); // wait so output comes before prompt
    }
  }
  return 0;
}

int main() {
  start();
  return 0;
}
