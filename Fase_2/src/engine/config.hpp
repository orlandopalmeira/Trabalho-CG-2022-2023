#ifndef CONFIG
#define CONFIG
#include "../tinyXML/tinyxml.h"
#include "../utils/list.hpp"
#include "../utils/tree.hpp"
#include <stdlib.h>

typedef struct config* Config;

typedef struct group* Group;

typedef struct transform* Transform;

Config newConfig();

Config xmlToConfig(const char*);

void setCamPosition(Config, float, float, float);

float getXPosCam(Config);

float getYPosCam(Config);

float getZPosCam(Config);

float getXLookAt(Config conf);

float getYLookAt(Config conf);

float getZLookAt(Config conf);

float getXUp(Config conf);

float getYUp(Config conf);

float getZUp(Config conf);

List getGroupTransforms(Group group);

List getGroupModels(Group group);

char transformType(Transform transf);

float transformAngle(Transform transf);

float transformX(Transform transf);

float transformY(Transform transf);

float transformZ(Transform transf);

void deleteConfig(Config);

/** WARNING: TEMPORARIA*/
void drawGroups(Tree groups, unsigned int indent);
/** WARNING: TEMPORARIA*/
void drawTree(Config c);
#endif // CONFIG