#ifndef TREE
#define TREE
#include "list.hpp"
#include <stdlib.h>
#include <string.h>

typedef struct tree* Tree;

Tree newEmptyTree();

Tree newTree(void*);

void setRootValue(Tree, void*);

void* getRootValue(Tree);

List getChildren(Tree tree);

void addChild(Tree, void*);

void addTreeChild(Tree tree, Tree child);

void deleteTree(Tree);

void deepDeleteTree(Tree, void (*)(void *));

#endif // TREE