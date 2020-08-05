#include "model.h"

void model::pushPoint(point* p) {
    points.push_back(p);
}

point* model::getPoint(int i) {
    return points[i];
}

int model::getSize() {
    return points.size();
}
