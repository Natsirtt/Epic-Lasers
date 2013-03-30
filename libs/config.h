#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

  #define CONFIG_FILE_PATH "conf/config"
  
  /**
   * Creates a new config file, erasing the old one if it exists.
   * Keywords are set to defaults values.
   * 
   * @return 0 if the file was created, -1 if its creation failed.
   */
  int config_createConfigFile();
  
  /**
   * Parses the config file in order to know if antialiasing is
   * active (true) or not (false). If it is, the number of samples
   * can be known with config_getAntialiasingSamplesNb().
   * If no config file was found, a new one is created using
   * config_createConfigFile() and antialiasing is set to false.
   * 
   * @return 0 if no config file was found or if its "antialiasing" is
   * set to "false" value.
   * 1 if the config file was found and its
   * "antialiasing" value is set to "true".
   * -1 if no config file was found AND the creation of a config
   * file failed.
   */
  int config_isAntialiasingActive();
  
  /**
   * Parses the config file searching for the "antialiasing-samples" keyword and
   * its value.
   * 
   * @return 2, 4 or 6 as the number of samples the config files asks to be used.
   * 0 if the "antialiasing" keyword is set to "false" or if the number of samples
   * the config file asks for is irrelevant. In this last case (irrelevant number
   * of samples), the config file is corrected to the default value of samples
   * number : 0.
   */
  int config_getAntialiasingSamplesNb();

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

