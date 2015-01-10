#include <string.h>
#include <stdlib.h>
#include "argv.h"
// arg_str
//  the string to be parsed
// argv
//  an initialized array of pointers to each individual token, each tokens are
//  malloc'd strings and will need to be freed after use
void init_argv(char *arg_str, char **argv) {
  char **curr_arg;
  char *tok;
  int i;

  // split the string into " " seperated tokens place each token in subsequent
  // indices of argv
  for(tok = strtok(arg_str, " "), curr_arg = argv, i = 0;
      tok != NULL && i < MAX_ARGS;
      tok = strtok(NULL, " "), curr_arg++, i++){
    *curr_arg = (char *) malloc(1 + strlen(tok));
    strcpy(*curr_arg, tok);
  }
}

void free_argv(char **argv) {
  int i;
  char **curr_arg;
  for(curr_arg = argv, i = 0;
      *curr_arg != NULL && i < MAX_ARGS;
      curr_arg++, i++) {
    free(*curr_arg);
  }
}
