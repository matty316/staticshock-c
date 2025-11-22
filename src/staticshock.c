#include "staticshock.h"

#include "file_utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

struct Generator {
  const char *input_path;
  const char *output_path;
  char *js_path;
  char *js_output_path;
  char *css_path;
  char *css_output_path;
  char *posts_path;
  char *img_path;
  char *img_output_path;
  char *header_path;
  char *footer_path;
} gen;

char *get_path(const char *dir_path, const char *path) {
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
  free(gen.img_path);
  free(gen.img_output_path);
}

void create_paths(const char *input_path, const char *output_path) {
  gen.input_path = input_path;
  gen.output_path = output_path;
  gen.js_path = get_path(gen.input_path, "js");
  gen.js_output_path = get_path(gen.output_path, "js");
  gen.css_path = get_path(gen.input_path, "css");
  gen.css_output_path = get_path(gen.output_path, "css");
  gen.posts_path = get_path(gen.input_path, "posts");
  gen.img_path = get_path(gen.input_path, "img");
  gen.img_output_path = get_path(gen.output_path, "img");
  gen.header_path = get_path(gen.input_path, "header.html");
  gen.footer_path = get_path(gen.input_path, "footer.html");
}

void create_output_dir() {
  remove_dir(gen.output_path);
  create_dir(gen.output_path);
  create_dir(gen.js_output_path);
  create_dir(gen.css_output_path);
  create_dir(gen.img_output_path);
}

void build_html_pages() {
    DIR *dir = opendir(gen.input_path);
    if (dir == NULL) {
      printf("cannot open directory: %s", gen.input_path);
      exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
      const char* name = entry->d_name;
      if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0 || strcmp(name, "footer.html") == 0 || strcmp(name, "header.html") == 0 || !has_extension(name, ".html"))
        continue;

      size_t src_len = strlen(gen.input_path) + strlen(name) + 2;
      size_t dest_len = strlen(gen.output_path) + strlen(name) + 2;

      char src_file_path[src_len];
      char dest_file_path[dest_len];

      snprintf(src_file_path, src_len, "%s/%s", gen.input_path, name);
      snprintf(dest_file_path, dest_len, "%s/%s", gen.output_path, name);

      copy_file(gen.header_path, dest_file_path);
      copy_file(src_file_path, dest_file_path);
      copy_file(gen.footer_path, dest_file_path);
    }

    closedir(dir);
}

void generate(const char *input_path, const char *output_path) {
  create_paths(input_path, output_path);
  create_output_dir();

  copy_files_from_dir(gen.css_path, gen.css_output_path, ".css");
  copy_files_from_dir(gen.js_path, gen.js_output_path, ".js");
  copy_files_from_dir(gen.img_path, gen.img_output_path, NULL);

  build_html_pages();

  free_gen();
}
