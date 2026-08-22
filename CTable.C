



int CTableBucketIndex(unsigned long hash, bool isPopulated);
{
    unsigned long hMod = hash % length;
    
    bool insert = true;
    if((hashs[hMod] != 0 && !isPopulated) || (hashs[hMod] != hash && isPopulated))
    {
        insert = false;
        int i = hMod+1 % length;
     
        printf("Searching: ");
        while(i != hMod)
        {
            printf("%i ",i);
            
            if((hashs[i] == 0 && !isPopulated) || (hashs[i] == hash && isPopulated))
            {
                hMod = i;
                insert = true;
                break;
            }
            i = ((i+1) % length);
        }
    }
    
    return insert ? hMod : -1;
}