#ifndef PERLIN_HPP
#define PERLIN_HPP

#include <ctime>
#include <cmath>

class Perlin {
public:
    Perlin();
    ~Perlin();

    //int noise(float chunk_x, float chunk_y, float chunk_z, float cube_x, float cube_y, float cube_z);
    float noise(float x, float y, float z);

private:
    int* p;
    float* Gx;
    float* Gy;
    float* Gz;

    float lerp(float a0, float a1, float w);
};

#endif