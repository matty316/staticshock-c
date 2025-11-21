#include "file_utils.h"

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
