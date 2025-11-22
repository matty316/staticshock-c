#ifndef file_utils_h
#define file_utils_h

#include <stdbool.h>

void remove_dir(const char *path);
void create_dir(const char *path);
void copy_file(const char *src_path, const char *dest_path);
void append_to_file(const char *string, const char *dest_path);
bool has_extension(const char *path, const char *ext);
void copy_files_from_dir(const char* src_path, const char* dest_path, const char *ext);

#endif
