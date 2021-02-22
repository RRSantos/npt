#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "./struct.h"

extern char* CONFIG_PARAM_BASE_PATH;
extern char* CONFIG_FILE;
extern char* DEFAULT_BASE_PATH;
extern char* MESSAGE_COPYING_FILES;
extern char* MESSAGE_ERROR_OPENING_SOURCE ;
extern char* MESSAGE_ERROR_CREATING_DESTINATION;
extern char* MESSAGE_ERROR_READING_DIR;
extern char* MESSAGE_ERROR_CREATING_DIR;

void remove_line_ending(char *input_string){
    int size_s = strlen(input_string);
    for(int i = 0; i< size_s; i++){ 
        
        if (input_string[i] == '\r' || input_string[i] == '\n'){
            input_string[i] = '\0';
        }
    }

}
void get_value_from_string(const char string[], const char* prefix, char ** result){
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
        char buf[1024] = {0} ;
        fread(buf, 1, sizeof(buf), f);
        remove_line_ending(buf);
        get_value_from_string(buf,CONFIG_PARAM_BASE_PATH, base_path); 
        fclose(f);
    }
}

int copy_file(char source[], char destination[]){
    FILE* f_source = fopen(source, "r");
    FILE* f_destination = fopen(destination, "w");
    if (f_source == NULL){
        return -1;
    }

    if (f_destination == NULL){
        fclose(f_source);
        return -2;
    }

    char buffer[4096];
    while(!feof(f_source)){
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), f_source);
        if (bytes_read){
            fwrite(buffer,1, bytes_read, f_destination);
        }
    }

    fclose(f_source);
    fclose(f_destination);


    return 0;

}
int set_complete_filename (char **destination, const char *path, const char *filename ){
    int path_size = strlen(path);
    int filename_size = strlen(filename);
    if (path_size == 0 || filename_size == 0){
        return -1;
    }
    *destination = malloc((path_size + filename_size+1)*sizeof(char*));
    strcpy(*destination, path);

    if ( path[path_size-1] != '/'){
        strcat(*destination, "/");
    }

    strcat(*destination, filename);

    return 0;
}
int create_dir_if_not_exists(const char dirName[]){
    printf("Creating directory %s...", dirName);
    int error = mkdir(dirName, S_IRWXU | S_IRWXG);
    if (!error){
        printf("OK!\n");
        return 0;
    }
    else{
        fprintf(stderr, MESSAGE_ERROR_CREATING_DIR, dirName);
        return -1;
    }

}
int create_project_template(const char* base_path, cli_param p){
    DIR *d;
    int copy_out = 0;
    struct dirent *dir;
    char *full_base_path;
    set_complete_filename(&full_base_path, base_path, p.Language);
    set_complete_filename(&full_base_path, full_base_path, p.ProjectType);

    int create_dir_result = create_dir_if_not_exists(p.DestinationDir);
    if (create_dir_result != 0)
    {
        return -4;
    }

    
    d = opendir(full_base_path);
    if (d){

        while ( (dir = readdir(d)) != NULL){
            if(dir->d_type == DT_REG){
                char *source_final_path;
                set_complete_filename(&source_final_path, full_base_path, dir->d_name);

                char *destination_final_path;
                set_complete_filename(&destination_final_path, p.DestinationDir, dir->d_name);
                
                printf(MESSAGE_COPYING_FILES, source_final_path, destination_final_path);
                copy_out = copy_file(source_final_path, destination_final_path);
                if (copy_out == -1){
                    fprintf(stderr, MESSAGE_ERROR_OPENING_SOURCE , source_final_path);
                    break;
                }
                else if (copy_out == -2){
                    fprintf(stderr, MESSAGE_ERROR_CREATING_DESTINATION , destination_final_path);
                    break;
                }
                else{
                    printf("OK!\n");
                }

            }
        }
        closedir(d);
        return copy_out;
    }
    else{
        fprintf(stderr, MESSAGE_ERROR_READING_DIR ,full_base_path);
        return -3;
    }
}
