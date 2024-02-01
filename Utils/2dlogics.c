#include "2dlogics.h"

position addPos(position p1, position p2) {
    p1.point.x += p2.point.x;
    p1.point.y += p2.point.y;
    return p1;
}
