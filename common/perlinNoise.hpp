#ifndef PERLINNOISE_HPP
#define PERLINNOISE_HPP

#include "Perlin.hpp"

class perlinNoise {
public:
	perlinNoise();
	~perlinNoise();

	float noise(float x, float y, float z);

	void setOctaves(int o);

	void setPersistence(float p);

	void setLacunarity(float l);

	void setBaseFrequency(float f);
	void setBaseAmplitude(float f);

private:
	Perlin* perlinSource;

	int octaves;
	float persistence;
	float lacunarity;
	float baseFrequency;
	float baseAmplitude;
};

#endif