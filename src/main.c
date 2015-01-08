#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "prompt.h"


int start() {
  char *buf, *prompt_str;
  prompt_str = get_prompt();

  buf = readline(prompt_str);

  free(prompt_str);
  free(buf);
  return 0;
}

int main() {
  start();
  return 0;
}
