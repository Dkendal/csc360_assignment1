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

  // split the string into " " seperated tokens place each token in subsequent
  // indices of argv
  for(tok = strtok(arg_str, " "), curr_arg = argv;
      tok != NULL;
      tok = strtok(NULL, " "), curr_arg++){
    *curr_arg = (char *) malloc(1 + strlen(tok));
    strcpy(*curr_arg, tok);
  }
}

void free_argv(char **argv) {
  char **curr_arg;
  for(curr_arg = argv; curr_arg != NULL; curr_arg++) {
    free(curr_arg);
  }
}
