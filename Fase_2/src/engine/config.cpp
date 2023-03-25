#include "config.hpp"

struct config{
    float window[2];
    float poscam[3];
    float lookAt[3];
    float up[3];
    float projection[3]; // fov, near, far
    Tree groups;
};

struct group{
    List transforms; // cada elementO é um Transform
    List models; // cada elemento é uma Figura  
};

struct transform{
    char type; // 't': translate, 's': scale, 'r': rotate
    float x,y,z; // para todas
    float angle; // para rotações
};

Config newConfig(){
    Config newConf = (Config)malloc(sizeof(struct config));
    if(newConf){
        newConf->groups = NULL;
    }
    return newConf;
}

Group newGroup(){
    Group new_group = (Group)malloc(sizeof(struct group));
    if(new_group){
        new_group->models = newEmptyList();
        new_group->transforms = newEmptyList();
        if(!(new_group->transforms && new_group->models)){
            free(new_group->models);
            free(new_group->transforms);
            free(new_group);
            new_group = NULL;
        }
    }
    return new_group;
}

Transform newTransform(char type, float x, float y, float z, float angle = 0.0f){
    Transform transform = (Transform)malloc(sizeof(struct transform));
    if(transform){
        transform->type = type;
        transform->x = x;
        transform->y = y;
        transform->z = z;
        transform->angle = angle;
    }
    return transform;
}

/** WARNING: Função privada, não incluir no config.hpp */
void getWindowInfoFromXML(Config conf, TiXmlElement* root){
    TiXmlElement* window = root->FirstChildElement("window"); // parâmetros da janela
        conf->window[0] = atof(window->Attribute("width"));
        conf->window[1] = atof(window->Attribute("height"));
}

/** WARNING: Função privada, não incluir no config.hpp */
void getCameraInfoFromXML(Config conf, TiXmlElement* root){
    TiXmlElement* camera = root->FirstChildElement("camera"); // parâmetros da cầmara
        TiXmlElement* posCamera = camera->FirstChildElement("position"); // posição da câmara
        TiXmlElement* lookAtCamera = camera->FirstChildElement("lookAt"); // lookAt da câmara
        TiXmlElement* upCamera = camera->FirstChildElement("up"); // vetor "up" da câmara
        TiXmlElement* projectionCamera = camera->FirstChildElement("projection"); // projections
        conf->poscam[0] = atof(posCamera->Attribute("x")); // coordenada x da posição da câmara
        conf->poscam[1] = atof(posCamera->Attribute("y")); // coordenada y da posição da câmara
        conf->poscam[2] = atof(posCamera->Attribute("z")); // coordenada z da posição da câmara
        conf->lookAt[0] = atof(lookAtCamera->Attribute("x")); // coordenada x da posição lookAt da câmara
        conf->lookAt[1] = atof(lookAtCamera->Attribute("y")); // coordenada y da posição lookAt da câmara
        conf->lookAt[2] = atof(lookAtCamera->Attribute("z")); // coordenada z da posição lookAt da câmara
        conf->up[0] = atof(upCamera->Attribute("x")); // coordenada x do vetor "up" da câmara
        conf->up[1] = atof(upCamera->Attribute("y")); // coordenada y do vetor "up" da câmara
        conf->up[2] = atof(upCamera->Attribute("z")); // coordenada z do vetor "up" da câmara
        conf->projection[0] = atof(projectionCamera->Attribute("fov")); // parâmetro fov do xml de configuração
        conf->projection[1] = atof(projectionCamera->Attribute("near")); // parâmetro near do xml de configuração
        conf->projection[2] = atof(projectionCamera->Attribute("far")); // parâmetro far do xml de configuração
}

/** WARNING: Função privada, não incluir no config.hpp */
void addModel(Tree tree, const char* model){
    if(tree && model){
        Figura figura = fileToFigura(model);
        Group group = (Group)getRootValue(tree);
        addValueList(group->models, figura);
    }
}

/** WARNING: Função privada, não incluir no config.hpp */
void addTransform(Tree tree, Transform transform){
    if(tree && transform){// temos as condições para executar?
        Group group = (Group)getRootValue(tree);
        addValueList(group->transforms, transform);
    }
}

/** WARNING: Função privada, não incluir no config.hpp */
Tree parseGroups(TiXmlElement* group){
    if(group){
        Tree res = newTree(newGroup());

        // METER AS TRANSFORMS NA ARVORE
        Transform transform_obj = NULL;
        TiXmlElement* transform = group->FirstChildElement("transform");
        if(transform){
            for(TiXmlElement* t = transform->FirstChildElement(); t; t = t->NextSiblingElement()){
                const char* name_of_transform = t->Value();
                float angle = 0.0f;
                if (strcmp(name_of_transform, "rotate") == 0) {
                    angle = atof(t->Attribute("angle"));
                }
                float x = atof(t->Attribute("x"));
                float y = atof(t->Attribute("y"));
                float z = atof(t->Attribute("z"));
                transform_obj = newTransform(name_of_transform[0], x, y, z, angle);
                addTransform(res,transform_obj);
            }
        }

        // METER OS MODELS NA ARVORE
        TiXmlElement* models = group->FirstChildElement("models");
        if(models){
            for(TiXmlElement* m = models->FirstChildElement("model"); m; m = m->NextSiblingElement("model")){
                const char* file_name = m->Attribute("file");
                addModel(res,file_name);
            }
        }

        for(TiXmlElement* chGroup = group->FirstChildElement("group"); chGroup; chGroup = chGroup->NextSiblingElement("group")){
            Tree child = parseGroups(chGroup);
            // Tratar de appends do filho para a árvore
            addTreeChild(res, child);
        }
        return res;
    }
    return NULL;
}

Config xmlToConfig(const char* filePath){
    Config result = newConfig();
    if(result){
        TiXmlDocument doc;
        if(doc.LoadFile(filePath)){
            TiXmlElement* root = doc.FirstChildElement("world"); // todo o conteúdo do ficheiro
            getWindowInfoFromXML(result, root);
            getCameraInfoFromXML(result, root);
            result->groups = parseGroups(root);
        }
    }
    return result;
}

void setCamPosition(Config conf, float x, float y, float z){
    if(conf){
        conf->poscam[0] = x;
        conf->poscam[1] = y;
        conf->poscam[2] = z;
    }
}

float getWindowWidth(Config conf){
    return conf->window[0];
}

float getWindowHeight(Config conf){
    return conf->window[1];
}

float getXPosCam(Config conf){
    return conf->poscam[0];
}

float getYPosCam(Config conf){
    return conf->poscam[1];
}

float getZPosCam(Config conf){
    return conf->poscam[2];
}

float getXLookAt(Config conf){
    return conf->lookAt[0];
}

float getYLookAt(Config conf){
    return conf->lookAt[1];
}

float getZLookAt(Config conf){
    return conf->lookAt[2];
}

float getXUp(Config conf){
    return conf->up[0];
}

float getYUp(Config conf){
    return conf->up[1];
}

float getZUp(Config conf){
    return conf->up[2];
}

Tree getTreeGroups(Config conf){
    if(conf){
        return conf->groups;
    }
    return NULL;
}

List getGroupTransforms(Group group){
    if(group){
        return group->transforms;
    }
    return NULL;
}

List getGroupModels(Group group){
    if(group){
        return group->models;
    }
    return NULL;
}

char transformType(Transform transf){
    if(transf){
        return transf->type;
    }
    return -1;
}

float transformAngle(Transform transf){
    if(transf){
        return transf->angle;
    }
    return -1;
}

float transformX(Transform transf){
    if(transf){
        return transf->x;
    }
    return -666;
}

float transformY(Transform transf){
    if(transf){
        return transf->y;
    }
    return -666;
}

float transformZ(Transform transf){
    if(transf){
        return transf->z;
    }
    return -666;
}

float getFov(Config conf){
    if(conf){
        return conf->projection[0];
    }
    return -666;
}

float getNear(Config conf){
    if(conf){
        return conf->projection[1];
    }
    return -666;
}

float getFar(Config conf){
    if(conf){
        return conf->projection[2];
    }
    return -666;
}

/** WARNING: TEMPORARIA*/
void printSpaces(unsigned int how_many){
	for(unsigned int i = 0; i < how_many; i++){
		putchar(' ');
	}
}

/** WARNING: TEMPORARIA*/
void drawGroupsDEBUG(Tree groups, unsigned int indent = 0){
	if(groups){
		Group group = (Group)getRootValue(groups);
		List transforms = group->transforms, models = group->models;
		for(unsigned long i = 0; i < getListLength(transforms); i++){
			printSpaces(indent);
			Transform t = (Transform)getListElemAt(transforms,i);
			if(t->type == 'r'){
                printf("ROTATE(%f,%f,%f,%f)\n", t->angle,t->x,t->y,t->z);
            } else if(t->type == 't'){
                printf("TRANSLATE(%f,%f,%f)\n", t->x,t->y,t->z);
            } else if(t->type == 's'){
                printf("SCALE(%f,%f,%f)\n", t->x,t->y,t->z);
            } 
		}
        
        printSpaces(indent);
        printf("Nodo com %lu models\n", getListLength(models));
        List filhos = getChildren(groups);
        for(unsigned long i = 0; i < getListLength(filhos); i++){
            Tree next = (Tree)getListElemAt(filhos, i);
            drawGroupsDEBUG(next,indent+4);
        }
	}
}

/** WARNING: TEMPORARIA*/
void drawTreeDEBUG(Config c){
    if(c){
        drawGroupsDEBUG(c->groups);
    }
}

void deleteTransform(Transform transf){
    if(transf){
        free(transf);
    }
}

void deleteGroup(Group group){
    if(group){
        deepDeleteList(group->transforms,(void (*)(void *))deleteTransform);
        deepDeleteList(group->models,(void (*)(void *))deleteFigura);
        free(group);
    }
}

void deleteConfig(Config conf){
    if(conf){
        deepDeleteTree(conf->groups,(void (*)(void *))deleteGroup);
        free(conf);
    }
}
