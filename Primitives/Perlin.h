/*THE AFTER
Commenc� le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse
Arnaud Lafargue

Projet de TDLog*/

#ifndef DEF_PERLIN
#define DEF_PERLIN

/*float*** computeGradient(float** source, int w, int h);
float lerp(float a, float b, float val);
float dotGridGradient(int ix, int iy, float x, float y, float*** gradient);
float perlin(float x, float y, float*** gradient);*/

float** heightMap(int w, int h, float nbOctaves, float biais);

#endif
