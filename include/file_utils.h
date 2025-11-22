#ifndef file_utils_h
#define file_utils_h

void remove_dir(const char *path);
void create_dir(const char *path);
void copy_file(const char *src_path, const char *dest_path);
void copy_files_from_dir(const char* src_path, const char* dest_path);

#endif
