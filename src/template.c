#include "template.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_css(char *buffer, const char *output_dir) {
  const char* css_path = "css";
  size_t total_path_len = strlen(output_dir) + strlen(css_path) + 2;
  char *total_path = malloc(total_path_len);
  snprintf(total_path, total_path_len, "%s/%s", output_dir, css_path);

  char *pos = strstr(buffer, "#(styles)");

  if (pos == NULL)
    return;

  char *styles_string;

  free(total_path);
}

void add_js(char *buffer, const char *output_dir) {
  const char* css_path = "js";
  size_t total_path_len = strlen(output_dir) + strlen(css_path) + 2;
  char *total_path = malloc(total_path_len);
  snprintf(total_path, total_path_len, "%s/%s", output_dir, css_path);



  free(total_path);
}

void template_file(const char *path, const char *output_dir) {
  FILE *file = fopen(path, "r+b");

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 1);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  buffer[bytesRead] = '\0';

  add_css(buffer, output_dir);
  add_js(buffer, output_dir);

  fwrite(buffer, sizeof(char), fileSize, file);
  fclose(file);
}
