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
    List transforms; // cada elemento é um Transform
    List models; // cada elemento é uma Figura  
};

struct transform{
    char type; // 't': translate, 's': scale, 'r': rotate
    float x,y,z; // para todas
    float angle; // para rotações, == 0 significa que não é usado
    float time; // para rotações e translações, == 0 significa que não é usado
    bool align; // para translações
    vector<vector<float>>* points; // para translações, vazio significa que não é usado
    float yAxis[3];
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

Transform newTransform(char type, float x, float y, float z, float angle = 0.0f, float time = 0.0f, vector<vector<float>> points = {}, bool align = false){
    Transform transform = (Transform)malloc(sizeof(struct transform));
    transform->points = new vector<vector<float>>();
    if(transform){
        transform->type = type;
        transform->x = x;
        transform->y = y;
        transform->z = z;
        transform->angle = angle;
        transform->time = time;
        for(vector<float> point : points){
            vector<float> ptn;
            ptn.push_back(point[0]);
            ptn.push_back(point[1]);
            ptn.push_back(point[2]); 
            transform->points->push_back(ptn);
        }
        transform->align = align;
        transform->yAxis[0] = 0.0f;
        transform->yAxis[1] = 1.0f;
        transform->yAxis[2] = 0.0f;
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
void parseTransform(Tree tree, TiXmlElement* transforms){
    if(transforms && tree){
        for(TiXmlElement* t = transforms->FirstChildElement(); t; t = t->NextSiblingElement()){
            vector<vector<float>> points;
            const char* name_of_transform = t->Value();
            float angle = 0.0f, time = 0.0f;
            bool align = false;
            if(strcmp(name_of_transform,"rotate") == 0){
                angle = t->Attribute("angle") ? atof(t->Attribute("angle")) : 0.0f;
                time = t->Attribute("time") ? atof(t->Attribute("time")) : 0.0f;
            }else if(strcmp(name_of_transform,"translate") == 0){
                if(t->Attribute("time") || t->Attribute("align")){
                    time = t->Attribute("time") ? atof(t->Attribute("time")) : 0.0f;
                    align = t->Attribute("align") ? (strcasecmp(t->Attribute("align"),"true") == 0 ? true : false) : false;
                    for(TiXmlElement* p = t->FirstChildElement("point"); p; p = p->NextSiblingElement()){
                        vector<float> ptn;
                        ptn.push_back(atof(p->Attribute("x")));
                        ptn.push_back(atof(p->Attribute("y")));
                        ptn.push_back(atof(p->Attribute("z")));
                        points.push_back(ptn);
                    }
                }
            }
            float x = t->Attribute("x") ? atof(t->Attribute("x")) : 0.0f;
            float y = t->Attribute("y") ? atof(t->Attribute("y")) : 0.0f;
            float z = t->Attribute("z") ? atof(t->Attribute("z")) : 0.0f;
            addTransform(tree,newTransform(name_of_transform[0],x,y,z,angle,time,points,align));
        }
    }
}

/** WARNING: Função privada, não incluir no config.hpp */
Tree parseGroups(TiXmlElement* group){
    if(group){
        Tree res = newTree(newGroup());

        // METER AS TRANSFORMS NA ARVORE
        Transform transform_obj = NULL;
        TiXmlElement* transform = group->FirstChildElement("transform");
        parseTransform(res,transform);

        // METER OS MODELS NA ARVORE
        TiXmlElement* models = group->FirstChildElement("models");
        if(models){
            for(TiXmlElement* m = models->FirstChildElement("model"); m; m = m->NextSiblingElement("model")){
                const char* file_name = m->Attribute("file");
                addModel(res,file_name);
            }
        }

        // Continuar recursivamente
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
    return 0.0f;
}

float transformTime(Transform transf){
    if(transf){
        return transf->time;
    }
    return 0.0f;
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

void setTransformXYZ(Transform transf, float x, float y, float z){
    if(transf){
        transf->x = x;
        transf->y = y;
        transf->z = z;
    }
}

vector<vector<float>> translatePoints(Transform transf){
    vector<vector<float>> result; 
    if(transf){
        for(vector<float> point : *(transf->points)){
            result.push_back(point);
        }
    }
    return result;
}

vector<float> transformYAxis(Transform transf){
    vector<float> result;
    if(transf){
        result.push_back(transf->yAxis[0]);
        result.push_back(transf->yAxis[1]);
        result.push_back(transf->yAxis[2]);
        return result;
    }
    return result;
}

bool transformAlign(Transform transf){
    if(transf){
        return transf->align;
    }
    return false;
}

void setTransformYAxis(Transform transf, float* newYAxis){
    if(transf && newYAxis){
        transf->yAxis[0] = newYAxis[0];
        transf->yAxis[1] = newYAxis[1];
        transf->yAxis[2] = newYAxis[2];
    }
}

void addPointToTranslate(Transform transf, float x, float y, float z){
    if(transf){
        vector<float> ptn;
        ptn.push_back(x);
        ptn.push_back(y);
        ptn.push_back(z);
        transf->points->push_back(ptn);
    }
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

/** WARNING: Funcção privada, não incluir no hpp*/
unsigned long figureCountAux(Tree groups){
    unsigned long result = 0;
    if(groups){
        Group group = (Group)getRootValue(groups);
        result = getListLength(group->models);
        List children = getChildren(groups);
        for(unsigned long i = 0; i < getListLength(children); i++){
            result += figureCountAux((Tree)getListElemAt(children,i));
        }
    }
    return result;
}

unsigned long figureCount(Config config){
    return figureCountAux(config->groups);
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
        delete transf->points;
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
