#include "file_utils.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void remove_dir(const char *path) {
  DIR *dir;
  struct dirent *entry;
  struct stat path_stat;

  if (stat(path, &path_stat) != 0) {
    printf("dir does not exist: %s\n", path);
    return;
  }

  dir = opendir(path);
  if (dir == NULL) {
    printf("unable to delete dir: %s\n", path);
    exit(EXIT_FAILURE);
  }

  while ((entry = readdir(dir)) != NULL) {
    size_t len = strlen(path) + strlen(entry->d_name) + 2;
    char full_path[len];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    if (stat(full_path, &path_stat) != 0) {
      continue;
    }

    if (S_ISDIR(path_stat.st_mode)) {
      remove_dir(full_path);
    } else {
      if (unlink(full_path) != 0) {
        printf("unable to delete file %s\n", full_path);
        exit(EXIT_FAILURE);
      }
    }
  }

  closedir(dir);

  if (rmdir(path) != 0) {
    printf("unable to rm dir %s\n", path);
  }

  printf("successfully deleted dir: %s\n", path);
}

void create_dir(const char *path) {
  if (mkdir(path, 0750) != 0) {
    printf("unable to create dir: %s\n", path);
    exit(EXIT_FAILURE);
  }
  printf("successfully created dir: %s\n", path);
}

void copy_file(const char *src_path, const char *dest_path) {
  printf("copying file: %s\n", src_path);

  FILE* src = fopen(src_path, "rb");

  if (src == NULL) {
    printf("cannot open file: %s", src_path);
    exit(EXIT_FAILURE);
  }

  fseek(src, 0L, SEEK_END);
  size_t fileSize = ftell(src);
  rewind(src);

  char* buffer = (char*)malloc(fileSize + 1);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, src);
  buffer[bytesRead] = '\0';

  FILE *dest = fopen(dest_path, "ab");

  if (dest == NULL) {
    printf("cannot open file: %s", dest_path);
    exit(EXIT_FAILURE);
  }

  fwrite(buffer, sizeof(char), fileSize, dest);

  fclose(src);
  fclose(dest);
  free(buffer);
}

void append_to_file(const char *string, const char *dest_path) {
  FILE *dest = fopen(dest_path, "ab");
  size_t str_len = strlen(string);

  if (dest == NULL) {
    printf("cannot open file: %s", dest_path);
    exit(EXIT_FAILURE);
  }

  fwrite(string, sizeof(char), str_len, dest);

  fclose(dest);
}

bool has_extension(const char *path, const char *ext) {
  if (ext == NULL) return true;

  size_t path_len = strlen(path);
  size_t ext_len = strlen(ext);

  return strncmp(&path[path_len - ext_len], ext, ext_len) == 0;
}

void copy_files_from_dir(const char *src_path, const char *dest_path, const char *ext) {
  DIR *src_dir = opendir(src_path);
  if (src_dir == NULL) {
    printf("cannot open directory: %s", src_path);
    exit(EXIT_FAILURE);
  }

  struct dirent *entry;
  while ((entry = readdir(src_dir)) != NULL) {
    const char* name = entry->d_name;
    if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0 || !has_extension(name, ext))
      continue;

    size_t src_len = strlen(src_path) + strlen(name) + 2;
    size_t dest_len = strlen(dest_path) + strlen(name) + 2;

    char src_file_path[src_len];
    char dest_file_path[dest_len];

    snprintf(src_file_path, src_len, "%s/%s", src_path, name);
    snprintf(dest_file_path, dest_len, "%s/%s", dest_path, name);

    copy_file(src_file_path, dest_file_path);
  }

  closedir(src_dir);
}
