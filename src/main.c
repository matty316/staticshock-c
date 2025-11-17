#include "staticshock.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
  if (argc == 3) {
    generate(argv[1], argv[2]);
  } else {
    fprintf(stderr, "Usage: static [input_dir] [output_dir]\n");
    exit(EXIT_FAILURE);
  }
  return 0;
}
