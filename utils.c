#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "./struct.h"

extern char* CONFIG_PARAM_BASE_PATH;
extern char* CONFIG_FILE;
extern char* DEFAULT_BASE_PATH;

void get_value_from_string(const char* string, const char* prefix, char ** result){
    char * found_ptr = strstr(string,prefix);
    if (found_ptr != NULL){
        int pos = found_ptr[0] - string[0] + strlen(prefix);
        *result = strndup(&string[pos], strlen(string) - pos - 1);
    }
}

void read_configuration(char **base_path){
    FILE* f = fopen(CONFIG_FILE, "r");
    if (f == NULL){
        *base_path = strdup(DEFAULT_BASE_PATH); 
    }
    else{
        char buf[1024] = {0};
        fread(&buf, sizeof(char), 1024, f);
        get_value_from_string(buf,CONFIG_PARAM_BASE_PATH, base_path); 
        fclose(f);
    }
}


void create_project_template(const char* base_path, cli_param p){
    DIR *d;
    struct dirent *dir;
    d = opendir(base_path);
    if (d){
        while ( (dir = readdir(d)) != NULL){
            if(dir->d_type == DT_REG)
                //TODO: Open file; replace tokens; save in current directory
                printf("---%s\n", dir->d_name);
        }
        closedir(d);
    }
}
