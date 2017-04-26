#include "ooc.h"

void* New(void* type)
{
    void* object = malloc(sizeof(type));
    return object;
}

void Delete(void* object)
{
    free(object);
}
