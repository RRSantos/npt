#ifndef NPT_UTILS_H
#define NPT_UTILS_H

#include "./struct.h"

void get_value_from_string(const char* string, const char* prefix, char ** result);
void read_configuration(char **base_path);
int create_project_template(const char* base_path, cli_param p);

#endif

