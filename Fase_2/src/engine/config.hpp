#ifndef CONFIG
#define CONFIG
#include "../tinyXML/tinyxml.h"
#include "../utils/list.hpp"
#include "../utils/tree.hpp"
#include "../utils/figura.hpp"
#include <stdlib.h>

typedef struct config* Config;

typedef struct group* Group;

typedef struct transform* Transform;

Config newConfig();

Config xmlToConfig(const char*);

void setCamPosition(Config, float, float, float);

float getWindowWidth(Config conf);

float getWindowHeight(Config conf);

float getXPosCam(Config);

float getYPosCam(Config);

float getZPosCam(Config);

float getXLookAt(Config conf);

float getYLookAt(Config conf);

float getZLookAt(Config conf);

float getXUp(Config conf);

float getYUp(Config conf);

float getZUp(Config conf);

Tree getTreeGroups(Config conf);

List getGroupTransforms(Group group);

List getGroupModels(Group group);

char transformType(Transform transf);

float transformAngle(Transform transf);

float transformX(Transform transf);

float transformY(Transform transf);

float transformZ(Transform transf);

float getFov(Config conf);

float getNear(Config conf);

float getFar(Config conf);

void deleteConfig(Config);

/** WARNING: TEMPORARIA*/
void drawGroupsDEBUG(Tree groups, unsigned int indent);
/** WARNING: TEMPORARIA*/
void drawTreeDEBUG(Config c);
#endif // CONFIG