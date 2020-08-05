#include "point.h"

point::point(){
    x = 0;
    y = 0;
    z = 0;
}

point::point(std::string str){
    size_t pos;
    x = std::stof(str,&pos);
    str.erase(0,pos+1);
    y = std::stof(str,&pos);
    str.erase(0,pos+1);
    z = std::stof(str,&pos);
}

point::point(float xx, float yy, float zz){
    x = xx;
    y = yy;
    z = zz;
}

float point::getX(){ return x; }
float point::getY(){ return y; }
float point::getZ(){ return z; }