#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

char * prompt() {
  char *prompt_str;
  prompt_str = (char *)malloc(6);
  strncpy(prompt_str, "RSI > ", 6);
  return prompt_str;
}

int start() {
  char *buf, *prompt_str;
  prompt_str = prompt();

  buf = readline(prompt_str);

  free(prompt_str);
  free(buf);
  return 0;
}

int main() {
  start();
  return 0;
}
