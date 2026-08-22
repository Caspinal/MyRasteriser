#include <stdlib.h>
#include <stdbool.h>
#include <uuid/uuid.h>

typedef struct 
{
    void* ref;
    size_t refSize;
    
    bool valueIsSet;
    char* encoding;
    long hashValue;
    long UUIDHashValue;
    uuid_t uuid;
} CValue;