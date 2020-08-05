#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H

#include "point.h"

#include <vector>

using namespace std;

class model {

private:
    vector<point*> points;

public:
    void pushPoint(point* p);
    point* getPoint(int i);
    int getSize();
};


#endif //ENGINE_MODEL_H
