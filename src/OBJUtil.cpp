#include "OBJUtil.hpp"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

OBJ::OBJ(char* data){
    this->data = data;
    LoadData();
}

float* OBJ::GetVertex(int* nVertices){
    if (this->vertex.size() != 0){
        OBJ::LoadData();
    } 
    *nVertices = this->vertex.size();
    return this->vertex.data();
}

int* OBJ::GetIndex(int* nIndices){
    if (this->index.size() != 0){
        OBJ::LoadData();
    }
    *nIndices = this->index.size();
    return this->index.data();
}

void OBJ::LoadData(){
    int dataOffset = 0;
    int startPos = 0;
    int wordIndex = -1;
    int nextWordIndex = -1;
    char dataChar = data[dataOffset];
    std::vector<int> faceVertices;
    LineType lineType = OTHER;
    while(dataChar){
        switch(dataChar){
            case '\n':
                nextWordIndex = -1;
            case ' ':
                nextWordIndex++;
                data[dataOffset] = 0;
                if (wordIndex == 0){
                    if (!strcmp(data + startPos, "v")){
                        lineType = VERTEX;
                    }else if(!strcmp(data + startPos, "f")){
                        lineType = FACE;
                    }else{
                        lineType = OTHER;
                    }
                }else{
                    switch(lineType){
                        case VERTEX:
                            vertex.push_back(std::stof(data + startPos));
                            break;
                        case FACE:
                            faceVertices.push_back(std::stoi(data + startPos) - 1);
                            break;
                        default:
                        break;
                    }
                }
                startPos = dataOffset + 1;
                if (nextWordIndex == 0){
                    switch (lineType){
                        case FACE:
                            for (int i = 0; i < faceVertices.size() - 2; i++){
                                for (int j = 0; j < 3; j++){
                                    index.push_back(faceVertices[i + j]);
                                }
                            }
                            faceVertices.clear();
                            break;
                        default:
                            break;
                    }
                }
                break;
            case '/':
                data[dataOffset] = 0;
            default:
            break;
        }
        wordIndex = nextWordIndex;
        dataOffset++;
        dataChar = data[dataOffset];
    }
}