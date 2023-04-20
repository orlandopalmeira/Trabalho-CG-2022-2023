#include "tree.hpp"

struct tree{
    void* valor; // valor do nodo
    List filhos; // nodos filhos (os filhos são do tipo Tree)
};

/** Funções de utilização geral */

Tree newEmptyTree(){
    Tree result = (Tree)malloc(sizeof(struct tree));
    if(result){
        result->valor = NULL;
        result->filhos = NULL;
    }
    return result;
}

Tree newTree(void* valor){
    Tree result = (Tree)malloc(sizeof(struct tree));
    if(result){
        result->valor = valor;
        result->filhos = NULL;
    }
    return result;
}

void setRootValue(Tree tree, void* valor){
    if(tree){
        tree->valor = valor;
    }
}

void* getRootValue(Tree tree){
    if(tree){
        return tree->valor;
    }
    return NULL;
}

List getChildren(Tree tree){
    if(tree){
        return tree->filhos;
    }
    return NULL;
}

void addChild(Tree tree, void* valor){
    if(tree && valor){ // tem as condições para executar?
        Tree newChild = newTree(valor); // novo filho da tree
        if(newChild){ // conseguiu criar o nodo para o filho?
            if(!tree->filhos){ // A tree ainda não tem filhos?
                tree->filhos = newEmptyList(); // cria uma lista para colocar os filhos da tree
                if(!tree->filhos){ // não foi possível criar a lista dos filhos da tree -> termina
                    deleteTree(newChild); // apaga o filho criado uma vez que ele não pode ser inserido
                    return; // termina a função
                }
            }
            // aqui a tree já pode colocar filhos
            addValueList(tree->filhos, newChild); // filho adicionado
        }
    }
}

void addTreeChild(Tree tree, Tree child){
    if(tree && child){
        if(!tree->filhos){
            tree->filhos = newEmptyList();
            if(!tree->filhos){ // não foi possível criar a lista dos filhos da tree -> termina
                return; // termina a função
            }
        }
        addValueList(tree->filhos, child);
    }
}

void deleteTree(Tree tree){
    if(tree){
        if(tree->filhos){
            deepDeleteList(tree->filhos,(void (*)(void *))deleteTree);   
        }
        free(tree);
    }
}

void deepDeleteTree(Tree tree, void (*free_function)(void *)){
    if(tree){
        if(tree->filhos){
            for(unsigned long i = 0; i < getListLength(tree->filhos); i++){
                deepDeleteTree((Tree)getListElemAt(tree->filhos,i), free_function);
            }
        }
        deleteList(tree->filhos);
        free_function(tree->valor);
        free(tree);
    }
}
