#ifndef ANDROID_H
#define ANDROID_H

char* read_rules_file(const char *filename);

char** read_directory(const char *dir_path, int *num_files);

#endif