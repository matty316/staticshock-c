#include "staticshock.h"

#include "file_utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Generator {
  const char *input_path;
  const char *output_path;
  char *js_path;
  char *js_output_path;
  char *css_path;
  char *css_output_path;
  char *posts_path;
} gen;

char *get_subdirectory_path(const char *dir_path, const char *path) {
  size_t input_len = strlen(dir_path);
  size_t path_len = strlen(path);
  size_t total_len = input_len + path_len + 2;
  char *string = (char *)malloc(sizeof(char) * total_len);
  snprintf(string, total_len, "%s/%s", dir_path, path);
  return string;
}

void free_gen() {
  free(gen.js_path);
  free(gen.js_output_path);
  free(gen.css_path);
  free(gen.css_output_path);
  free(gen.posts_path);
}

void create_paths(const char *input_path, const char *output_path) {
  gen.input_path = input_path;
  gen.output_path = output_path;
  gen.js_path = get_subdirectory_path(gen.input_path, "js");
  gen.js_output_path = get_subdirectory_path(gen.output_path, "js");
  gen.css_path = get_subdirectory_path(gen.input_path, "css");
  gen.css_output_path = get_subdirectory_path(gen.output_path, "css");
  gen.posts_path = get_subdirectory_path(gen.input_path, "posts");
}

void create_output_dir() {
  remove_dir(gen.output_path);
  create_dir(gen.output_path);
  create_dir(gen.js_output_path);
  create_dir(gen.css_output_path);
}

void generate(const char *input_path, const char *output_path) {
  create_paths(input_path, output_path);
  create_output_dir();
  
  free_gen();
}
