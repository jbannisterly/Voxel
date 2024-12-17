#include <stdlib.h>
#include <vector>

class OBJ{
    enum LineType{
        OTHER, VERTEX, FACE  
    };
    std::vector<float> vertex = {};
    std::vector<int> index = {};
    char* data = nullptr;
    void LoadData();
    public:
    OBJ(char* data);
    float* GetVertex(int* nVertices);
    int* GetIndex(int* nIndices);
    ~OBJ(){
        free(data);
    }
};