#ifndef NPT_CONSTANTS_H
#define NPT_CONSTANTS_H

const char* ERROR_PARAM_COUNT = "Invalid number of arguments. (Expected: %d; Actual: %d)\n";
const int PARAM_COUNT = 4;

char* CONFIG_FILE = "npt.config";
char* DEFAULT_BASE_PATH = "~/.config/npt/templates/";
char* CONFIG_PARAM_BASE_PATH = "base_path=";

char* MESSAGE_COPYING_FILES = "Copying %s to %s...";
char* MESSAGE_ERROR_OPENING_SOURCE = "Error: Could not open source file '%s' for reading.\n";
char* MESSAGE_ERROR_CREATING_DESTINATION = "Error: Could not open destination file '%s' for writting.\n";
char* MESSAGE_ERROR_READING_DIR = "Error: Could not open directory '%s' for listing files.\n";
char* MESSAGE_ERROR_CREATING_DIR = "Error: Could not create directory %s\n";
#endif

