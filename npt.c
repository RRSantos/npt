#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./constants.h"

typedef struct params{
    char* ProjectName;
    char* ProjectType;
    char* Language;
} cli_param;

void free_param(cli_param* params){
    free(params->ProjectName);
    free(params->ProjectType);
    free(params->Language);
}
void bind_param(cli_param* params, char** argv){
    params->ProjectName = strdup(argv[1]);
    params->ProjectType = strdup(argv[2]);
    params->Language = strdup(argv[3]);
}

void read_configuration(char **base_path){
    FILE* f = fopen(CONFIG_FILE, "r");
    if (f == NULL){
        *base_path = strdup(DEFAULT_BASE_PATH); 
    }
    else{
        *base_path = strdup(DEFAULT_BASE_PATH); 
        fclose(f);
    }
}

int main(int argc, char** argv){

    if (argc != 4){
        fprintf(stderr,ERROR_PARAM_COUNT, PARAM_COUNT, argc);
        return -1;
    }

    cli_param p; 
    bind_param(&p,argv);
    char* my_dir;
    read_configuration(&my_dir);
    printf("Name: %s\nType: %s\nLanguage: %s\nBase path: %s\n", p.ProjectName, p.ProjectType, p.Language, my_dir);
    free_param(&p);
    return 0;
}

