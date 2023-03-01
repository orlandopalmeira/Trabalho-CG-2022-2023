#ifndef CONFIG
#define CONFIG
#include "../tinyXML/tinyxml.h"
#include <stdlib.h>

typedef struct config* Config;

Config newConfig();

Config xmlToConfig(const char*);

void deleteConfig(Config);

#endif // CONFIG