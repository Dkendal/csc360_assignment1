#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../src/prompt.c"

void test_get_prompt() {
  char *actual;
  int val;
  actual = get_prompt();

  val = strcmp("RSI: /home/dkendal/src/csc360/assignment1 > ", actual);

  assert(val == 0);

  free(actual);
}

int main(int argc, char *argv[]) {
  test_get_prompt();
  return 0;
}
