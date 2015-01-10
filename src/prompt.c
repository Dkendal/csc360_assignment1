#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "prompt.h"

struct prompt{
  const char *start;
  const int  start_len;
  const char *end;
  const int  end_len;
  char dir[PATH_MAX];
  int  dir_len;
};

int prompt_len(struct prompt p) {
  return p.start_len + p.end_len + p.dir_len + 1; // plus \0
}

//  "RSI: $pwd > "
char * get_prompt() {
  struct prompt new_prompt = { "RSI: ", 5, " > ", 3, {} };
  char *prompt_str;

  getcwd(new_prompt.dir, PATH_MAX);

  new_prompt.dir_len = strlen(new_prompt.dir);

  prompt_str = (char*) malloc(prompt_len(new_prompt));

  strcpy(prompt_str, new_prompt.start);
  strncat(prompt_str, new_prompt.dir, new_prompt.dir_len);
  strncat(prompt_str, new_prompt.end, new_prompt.end_len);

  return prompt_str;
}
