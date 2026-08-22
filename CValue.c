#include "CValue.h"
#include <string.h>

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 0;
    int c = *str++;
    
    while (c)
    {
      hash = c + (hash << 6) + (hash << 16) - hash;
        c = *str++;
    }

    return hash;
}

void CValueInit(CValue* cValue, void* ref, size_t refSize, char* encoding)
{
    cValue->ref = ref;
    cValue->refSize = refSize;
    cValue->valueIsSet = true;
    cValue->encoding = encoding;
    cValue->hashValue = 0; // You might want to compute a hash based on the content of ref

   int el =  strlen(encoding);
    for (int i = 0; i < el; el++)
    {

    }
   
    uuid_generate(cValue->uuid); // Generate a new UUID for this value
     cValue->UUIDHashValue = hash((unsigned char*)cValue->uuid);
}


void CValueDestroy(CValue* cValue)
{
    free(cValue->ref); // this may crash
    cValue->ref = NULL;
    cValue->refSize = 0;
    cValue->valueIsSet = false;
    cValue->encoding = "";
    cValue->hashValue = 0;
    cValue->UUIDHashValue = 0;
    uuid_clear(cValue->uuid);
}