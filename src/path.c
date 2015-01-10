#include <string.h>
#include "path.h"
#include <unistd.h>

void rel_to_abs_path(char * path, const char * relative_path) {
  getcwd(path, PATH_MAX);
  strncat(path, "/", PATH_MAX);
  strncat(path, relative_path, PATH_MAX);
}

int change_dir(char * path) {
  char full_path[PATH_MAX] = {};
  rel_to_abs_path(full_path, path);
  return chdir(full_path);
}
