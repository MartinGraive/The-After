/*Random Game
Started on 27/01/2018

Grade (programming / Concept)*/

#ifndef DEF_PERLIN
#define DEF_PERLIN

/*float*** computeGradient(float** source, int w, int h);
float lerp(float a, float b, float val);
float dotGridGradient(int ix, int iy, float x, float y, float*** gradient);
float perlin(float x, float y, float*** gradient);*/

float** heightMap(int w, int h, float nbOctaves, float biais);

#endif
