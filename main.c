#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./constants.h"
#include "./utils.h"
#include "./struct.h"

void free_param(cli_param* params){
    free(params->ProjectName);
    free(params->ProjectType);
    free(params->Language);
}

void bind_param(cli_param* params, int argc, char** argv){
    params->ProjectName = strdup(argv[1]);
    params->ProjectType = strdup(argv[2]);
    params->Language = strdup(argv[3]);
    if (argc > PARAM_COUNT){
        params->DestinationDir = strdup(argv[4]);
    }else{
        params->DestinationDir = strdup("./");
    }
}
void show_input_params(cli_param p){

    printf("Input parameters:\n");
    printf("\tProject name: %s\n", p.ProjectName);
    printf("\tProject type: %s\n", p.ProjectType);
    printf("\tLanguage: %s\n",  p.Language);
    printf("\tDestination dir: %s\n",  p.DestinationDir);
}

void show_usage(){
    printf("npt version 0.0.1\n");
    printf("\nnpt creates project structures based on custom file tamplates defined by the user.\n\n");
    printf("Usage:\n");
    printf("npt <ProjectName> <ProjectType> <Language> [<DestinationDir>]\n");
    printf("\nParameter\t\t\tDescription\n");
    printf("---------------------------------------------------------------\n");
    printf("  ProjectName:\t\t\tName of the project to be created.\n");
    printf("  ProjectType:\t\t\tType of the project to be created.\n");
    printf("  Language:\t\t\tLanguage of the project to be created.\n");
    printf("  DestinationDir:\t\t(Optional) Directory to create project files.\n\n");

}

int main(int argc, char** argv){

    if (argc < PARAM_COUNT){
        fprintf(stderr,ERROR_PARAM_COUNT, PARAM_COUNT-1, argc);
        show_usage();
        return -1;
    }

    cli_param p; 
    bind_param(&p,argc, argv);
    char* base_path;
    read_configuration(&base_path);
    printf("Creating project template...\n");
    show_input_params(p);
    int create_result;
    create_result = create_project_template(base_path, p);

    if (create_result != 0){
        fprintf(stderr,"Errors creating project template. See errors above.\n");
    }
    else{
        printf("Project template successfully created!\n");
    }
    return create_result;

    free_param(&p);
    free(base_path);
}

