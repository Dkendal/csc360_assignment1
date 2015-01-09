#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "prompt.h"

int start() {
  int status;
  pid_t pid;
  char *buf, *prompt_str;

  for(pid = 1; pid != 0;) {
    prompt_str = get_prompt();
    buf = readline(prompt_str);
    free(prompt_str);

    pid = fork();

    if(pid == 0) {
      char *argv[1] = { "" };
      execvp(buf, argv);
      // TODO spit error
    }
    else {
      waitpid(pid, &status, 0);
    }

    free(buf);
  }
  return 0;
}

int main() {
  start();
  return 0;
}
