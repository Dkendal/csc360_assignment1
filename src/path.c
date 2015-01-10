#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "path.h"

void rel_to_abs_path(char * path, const char * relative_path) {
  getcwd(path, PATH_MAX);
  strncat(path, "/", PATH_MAX);
  strncat(path, relative_path, PATH_MAX);
}

int change_dir(const char * path) {
  char full_path[PATH_MAX] = {};
  const char * path_str = path;

  if(!path) {
    path_str = getenv("HOME");
  }
  else switch(path[0]) {
    case '~':
      path_str = getenv("HOME");
      break;
    case '/':
      break;
    default:
      rel_to_abs_path(full_path, path);
      path_str = full_path;
  }

  return chdir(path_str);
}
