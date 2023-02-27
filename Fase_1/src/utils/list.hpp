#ifndef LIST
#define LIST
#include <stdlib.h>

#define STDSIZE 100

typedef struct list* List;

List newEmptyList();

int listIsFull(List list);

void addValueList(List list, void* value);

void** getListValues(List list);

unsigned long getListLength(List list);

void* getListElemAt(List list, unsigned long index);

void deleteList(List list);

#endif // LIST