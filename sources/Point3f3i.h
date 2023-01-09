#ifndef POINT3F3I_H
#define POINT3F3I_H


class Point3f3i
{
public:
    Point3f3i();
    //03.10.2022 comm
    //Point3f3i(float worldX, float worldY, float worldZ, int pixelX, int pixelY, int pixelZ);
    //Point3f3i(float worldX, float worldY, float worldZ);
    Point3f3i(int pixelX, int pixelY, int pixelZ);
    //03.10.2022 comm
    //float worldX = 0.0f;
    //float worldY = 0.0f;
    //float worldZ = 0.0f;
    int pixelX = 0;
    int pixelY = 0;
    int pixelZ = 0;
};

#endif // POINT3F3I_H
