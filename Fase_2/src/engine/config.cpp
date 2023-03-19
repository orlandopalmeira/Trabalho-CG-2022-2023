#include "config.hpp"
/*
struct config{
    // TODO: Acrescentar a window
    // Câmara
    float poscam[3];
    float lookAt[3];
    float up[3];
    float projection[3]; // fov, near, far
    List models; // TODO: Apagar isto -> substituir por Tree groups;
};*/
struct config{
    float window[2];
    float poscam[3];
    float lookAt[3];
    float up[3];
    float projection[3]; // fov, near, far
    Tree groups;
};

struct group{
    List transforms;
    List models;
};

struct transform{
    char type; // 't': translate, 's': scale, 'r': rotate
    float angle; // para rotações
    float x,y,z; // para todas
};

Config newConfig(){
    Config newConf = (Config)malloc(sizeof(struct config));
    if(newConf){
        newConf->groups = newEmptyTree();
        if(!newConf->groups){ // não foi possível criar a lista
            free(newConf);
            newConf = NULL;
        }
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
/*
Config xmlToConfig(const char* filePath){
    Config result = newConfig();
    if(result){
        TiXmlDocument doc;
        if(doc.LoadFile(filePath)){
            TiXmlElement* root = doc.FirstChildElement("world"); // todo o conteúdo do ficheiro
            // Obtenção dos dados da câmara
            TiXmlElement* camera = root->FirstChildElement("camera"); // parâmetros da cầmara
                TiXmlElement* posCamera = camera->FirstChildElement("position"); // posição da câmara
                TiXmlElement* lookAtCamera = camera->FirstChildElement("lookAt"); // lookAt da câmara
                TiXmlElement* upCamera = camera->FirstChildElement("up"); // vetor "up" da câmara
                TiXmlElement* projectionCamera = camera->FirstChildElement("projection"); // projections
                result->poscam[0] = atof(posCamera->Attribute("x")); // coordenada x da posição da câmara
                result->poscam[1] = atof(posCamera->Attribute("y")); // coordenada y da posição da câmara
                result->poscam[2] = atof(posCamera->Attribute("z")); // coordenada z da posição da câmara
                result->lookAt[0] = atof(lookAtCamera->Attribute("x")); // coordenada x da posição lookAt da câmara
                result->lookAt[1] = atof(lookAtCamera->Attribute("y")); // coordenada y da posição lookAt da câmara
                result->lookAt[2] = atof(lookAtCamera->Attribute("z")); // coordenada z da posição lookAt da câmara
                result->up[0] = atof(upCamera->Attribute("x")); // coordenada x do vetor "up" da câmara
                result->up[1] = atof(upCamera->Attribute("y")); // coordenada y do vetor "up" da câmara
                result->up[2] = atof(upCamera->Attribute("z")); // coordenada z do vetor "up" da câmara
                result->projection[0] = atof(projectionCamera->Attribute("fov")); // parâmetro fov do xml de configuração
                result->projection[1] = atof(projectionCamera->Attribute("near")); // parâmetro near do xml de configuração
                result->projection[2] = atof(projectionCamera->Attribute("far")); // parâmetro far do xml de configuração
                
            TiXmlElement* group = root->FirstChildElement("group"); // obtenção do group do ficheiro de configuração
                TiXmlElement* models = group->FirstChildElement("models"); // obtenção dos ficheiros dos modelos
                    for(TiXmlElement* model = models->FirstChildElement("model"); model; model = model->NextSiblingElement("model")){
                        addValueList(result->models, strdup(model->Attribute("file")));
                    }
        }
    }
    return result;
}*/

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
    if(tree && model){// temos as condições para executar
        Group group = (Group)getRootValue(tree);
        if(!group){// a árvore ainda não tem o group?
            group = newGroup(); // novo group para inserir na árvore
            if(!group){ // o novo grupo não foi criado?
                return; // termina
            }
            setRootValue(tree,group); // a árvore já tem group
        }
        addValueList(group->models, strdup(model)); // !!!!STRDUP ALOCA MEMÓRIA!!!!
    }
}

/** WARNING: Função privada, não incluir no config.hpp */
void addTransform(Tree tree, Transform transform){
    if(tree && transform){// temos as condições para executar?
        Group group = (Group)getRootValue(tree);
        if(!group){
            group = newGroup(); // novo group para inserir na árvore
            if(!group){ // o novo grupo não foi criado?
                return; // termina
            }
            setRootValue(tree,group); // a árvore já tem group
        }
        addValueList(group->transforms,transform);
    }
}

/** WARNING: Função privada, não incluir no config.hpp */
// TEST FUNCTION
Tree checkGroups(TiXmlElement* group){
    Tree res = newEmptyTree();

    // METER AS TRANSFORMS NA ARVORE
    Transform transform_obj = NULL;
    TiXmlElement* transform = group->FirstChildElement("transform");
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

    // METER OS MODELS NA ARVORE
    TiXmlElement* models = group->FirstChildElement("models");
    for(TiXmlElement* m = models->FirstChildElement("model"); m; m = m->NextSiblingElement("model")){
        const char* file_name = m->Attribute("file");
        addModel(res,file_name);
    }

    for(TiXmlElement* chGroup = group->FirstChildElement("group"); chGroup; chGroup = chGroup->NextSiblingElement("group")){
        Tree child = checkGroups(chGroup);
        // Tratar de appends do filho para a árvore
        addChild(res, child);
    }
    return res;
}
// TEST END

Config xmlToConfig(const char* filePath){
    Config result = newConfig();
    if(result){
        TiXmlDocument doc;
        if(doc.LoadFile(filePath)){
            TiXmlElement* root = doc.FirstChildElement("world"); // todo o conteúdo do ficheiro
            getWindowInfoFromXML(result, root);
            getCameraInfoFromXML(result, root);
            TiXmlElement* group = root->FirstChildElement("group");
            result->groups = checkGroups(group);
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

/*
void deleteConfig(Config conf){
    if(conf){
        deepDeleteList(conf->models, free);
        free(conf);
    }
}*/