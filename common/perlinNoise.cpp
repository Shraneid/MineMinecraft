#include "perlinNoise.hpp"

perlinNoise::perlinNoise() {
	perlinSource = new Perlin();

	octaves = 8;
	lacunarity = 2.0f;
	persistence = 0.5f;
	baseFrequency = 1.0f;
	baseAmplitude = 1.0f;
}

perlinNoise::~perlinNoise() {
	delete perlinSource;
}

float perlinNoise::noise(float x, float y, float z) {
	float sum = 0;
	float freq = baseFrequency;
	float amp = baseAmplitude;

	for (int i = 0; i < octaves; ++i) {
		sum += perlinSource->noise(x * freq, y * freq, z * freq) * amp;

		freq *= lacunarity;
		amp *= persistence;
	}

	return (sum+1.0f)/2.0f;
}

void perlinNoise::setOctaves(int o) {
	if (o > 0) {
		this->octaves = o;
	}
}

void perlinNoise::setPersistence(float p) {
	this->persistence = p;
}

void perlinNoise::setLacunarity(float l) {
	this->lacunarity = l;
}

void perlinNoise::setBaseAmplitude(float ba) {
	this->baseAmplitude = ba;
}

void perlinNoise::setBaseFrequency(float bf) {
	this->baseFrequency = bf;
}
