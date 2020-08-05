#ifndef _GENERATE_H
#define _GENERATE_H

#include <vector>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

class generate {

public:
    void generatePlane(float size, string filename);

    void generateBox(float x, float y, float z, int divs, string filename);

    void generateSphere(float radius, int slices, int stacks, string filename);

    void generateCone(float radius, float height, int slices, int stacks, string filename);

    void xySide(float x, float y, float z, int divs, string filename);

    void yzSide(float x, float y, float z, int divs, string filename);

    void zxSide(float x, float y, float z, int divs, string filename);
};


#endif