#include "Point3f3i.h"

Point3f3i::Point3f3i()
{

}

//03.10.2022 comm
/*
Point3f3i::Point3f3i(float worldX, float worldY, float worldZ, int pixelX, int pixelY, int pixelZ) {
    this->worldX = worldX;
    this->worldY = worldY;
    this->worldZ = worldZ;
    this->pixelX = pixelX;
    this->pixelY = pixelY;
    this->pixelZ = pixelZ;
}

Point3f3i::Point3f3i(float worldX, float worldY, float worldZ) {
    this->worldX = worldX;
    this->worldY = worldY;
    this->worldZ = worldZ;
}
*/

Point3f3i::Point3f3i(int pixelX, int pixelY, int pixelZ) {
    this->pixelX = pixelX;
    this->pixelY = pixelY;
    this->pixelZ = pixelZ;
}
