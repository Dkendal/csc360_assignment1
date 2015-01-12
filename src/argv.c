#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "argv.h"
// arg_str
//  the string to be parsed
// argv
//  an initialized array of pointers to each individual token, each tokens are
//  malloc'd strings and will need to be freed after use
void init_argv(char *arg_str, struct task *task_params) {
  char **argv, *tok;
  int count, size;

  memset(task_params, 0, sizeof(struct task));


  size = 1;
  argv = (char **) malloc(sizeof(char *) * size);

  // split the string into " " seperated tokens place each token in subsequent
  // indices of argv
  for(count = 0, tok = strtok(arg_str, " ");
      tok != NULL;
      tok = strtok(NULL, " "), count++){

    //resize if nessecary
    if(count >= size - 1) {
      size = size * 2;
      argv = (char **) realloc(argv, sizeof(char *) * size);
    }

    argv[count] = (char *) malloc(1 + strlen(tok));
    strcpy(argv[count], tok);
  }

  argv[count] = 0;

  task_params->argv = argv;
  task_params->cmd = argv[0];
  task_params->run_in_bg = 0;
}

void free_argv(struct task *task_params) {
  int i;
  char **curr_arg;
  for(curr_arg = task_params->argv, i = 0;
      *curr_arg != NULL && i < MAX_ARGS;
      curr_arg++, i++) {
    free(*curr_arg);
  }
  free(task_params->argv);
}
