#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#define CONFIG_BUFF_LENGTH 4096

int _config_writeLine(FILE *file, const char *line) {
  size_t lineLength = strlen(line);
  size_t wrote = fwrite(line, lineLength, 1, file);
  /*if (wrote != lineLength) {
    return -1;
  }*/
  return 0;
}

void config_createConfigFile() {
  FILE *configFile = fopen(CONFIG_FILE_PATH, "w");
  if (configFile == NULL) {
    fprintf(stderr, "Failed to create the config file\n");
    exit(EXIT_FAILURE);
  }
  if (_config_writeLine(configFile, CONFIG_DEFAULT_LINE_INTRO) == -1) {
    fprintf(stderr, "Failed to write into the config file\n");
    exit(EXIT_FAILURE);
  }
  if (_config_writeLine(configFile, CONFIG_DEFAULT_LINE_ANTIALIASING) == -1) {
    fprintf(stderr, "Failed to write into the config file\n");
    exit(EXIT_FAILURE);
  }
  if (_config_writeLine(configFile, CONFIG_DEFAULT_LINE_ANTIALIASING_SAMPLES) == -1) {
    fprintf(stderr, "Failed to write into the config file\n");
    exit(EXIT_FAILURE);
  }
  fclose(configFile);
}

/**
 * Search for the value of the config keyword.
 * Returns 1 if it was found, 0 if the keyword wasn't found.
 * The stream pointer may be positioned differently or even reach its end
 * at the exit of this function.
 */
int _config_getValue(char *buff, FILE *file, const char *keyword) {
  int stop = 0;
  char internBuff[CONFIG_BUFF_LENGTH];
  while (!stop) {
    fgets(internBuff, CONFIG_BUFF_LENGTH, file);
    if (!(internBuff[0] == '#')) {
      if (strstr(internBuff, keyword) != NULL) {
        buff = strtok(internBuff, "=");
        return 1;
      }
    }
    stop = feof(file);
  }
  return 0;
}

int config_isAntialiasingActive() {
  FILE *configFile = fopen(CONFIG_FILE_PATH, "r");
  if (configFile == NULL) {
    fprintf(stderr, "Error reading config file ; now trying to create it\n");
    config_createConfigFile();
    configFile = fopen(CONFIG_FILE_PATH, "a+");
    if (configFile == NULL) {
      fprintf(stderr, "Unable to read into the config file even after trying to create it. Aborting\n");
      exit(EXIT_FAILURE);
    }
  } else {
    fclose(configFile);
    configFile = fopen(CONFIG_FILE_PATH, "a+");
  }
  char buff[CONFIG_BUFF_LENGTH];
  if (_config_getValue(buff, configFile, "antialiasing")) {
    if (strcmp(buff, "true") == 0) {
      return 1;
    }
    return 0;
  } else {
    _config_writeLine(configFile, CONFIG_DEFAULT_LINE_ANTIALIASING);
    return 0;
  }
  
  fclose(configFile);
}

int config_getAntialiasingSamplesNb() {
  if (!config_isAntialiasingActive()) {
    return 0;
  }
  FILE *configFile = fopen(CONFIG_FILE_PATH, "a+");
  char buff[CONFIG_BUFF_LENGTH];
  if (_config_getValue(buff, configFile, "antialiasing-samples")) {
    return atoi(buff);
  } else {
    _config_writeLine(configFile, CONFIG_DEFAULT_LINE_ANTIALIASING_SAMPLES);
    return 0;
  }
  
  fclose(configFile);
}