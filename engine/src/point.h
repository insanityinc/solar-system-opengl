//
// Created by lucas on 3/7/19.
//

#ifndef ENGINE_POINT_H
#define ENGINE_POINT_H


#include <string>
#include <ostream>

class point {

private:
    float x;
    float y;
    float z;

public:
    point();
    point(std::string str);
    point(float xx, float yy, float zz);
    float getX();
    float getY();
    float getZ();
};


#endif //ENGINE_POINT_H
