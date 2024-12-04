#include <stdio.h>
#include <stdlib.h>

namespace IOUtil{
    char* ReadFile(char* path){
        FILE *file = fopen(path, "r");
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        char* fileData = (char*)malloc(size * sizeof(char) + 1);
        
        fseek(file, 0, SEEK_SET);
        fread(fileData, sizeof(char), size, file);
        fileData[size] = 0;
        fclose(file);

        return fileData;
    }
}