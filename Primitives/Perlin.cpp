/*THE AFTER
Commencé le 22/10/2018

Youval Vanlaer
Martin Graive
Nicolas de Roux
Malo Le Magueresse

Projet de TDLog*/

#include <cmath>
#include <cstdlib>
#include "Perlin.h"

/**float*** computeGradient(float** source, int w, int h)
{
    float*** gradient = new float**[w];
    for (int i = 0 ; i < w ; i++) {
        gradient[i] = new float*[h];
        for (int j = 0 ; j < h ; j++) {
            gradient[i][j] = new float[2];
        }
    }

    for (int i = 0 ; i < w ; i++) {
        for (int j = 0 ; j < h ; j++) {
            if (i == 0 || i == w - 1) { gradient[i][j][0] = source[i][j]; }
            else { gradient[i][j][0] = source[i+1][j] - source[i-1][j]; }
            if (j == 0 || j == h - 1) { gradient[i][j][1] = source[i][j]; }
            else { gradient[i][j][1] = source[i][j+1] - source[i][j-1]; }
        }
    }

    return gradient;
}

//val in [0,1]
float lerp(float a, float b, float val) {
    return (1.0 - val) * a + val*b;
}

float dotGridGradient(int ix, int iy, float x, float y, float*** gradient)
{
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    return (dx*gradient[ix][iy][0] + dy*gradient[ix][iy][1]);
}

float perlin(float x, float y, float*** gradient)
{
    int x0 = (int)(floor((double)x));
    int x1 = x0 + 1;
    int y0 = (int)(floor((double)y));
    int y1 = y0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n0, n1, ix0, ix1, value;
    n0 = dotGridGradient(x0, y0, x, y, gradient);
    n1 = dotGridGradient(x1, y0, x, y, gradient);
    ix0 = lerp(n0, n1, sx);
    n0 = dotGridGradient(x0, y1, x, y, gradient);
    n1 = dotGridGradient(x1, y1, x, y, gradient);
    ix1 = lerp(n0, n1, sx);

    return lerp(ix0, ix1, sy);
}

float** heightMap(int w, int h, float scale)
{
    if (scale <= 0) { scale = 0.001f; }

    float** pureNoise = new float*[(int)(w/scale)];
    for (int i = 0 ; i < (int)(w/scale) ; i++) {
        pureNoise[i] = new float[(int)(h/scale)];
        for (int j = 0 ; j < (int)(h/scale) ; j++) {
            pureNoise[i][j] = (rand() % RAND_MAX) / (RAND_MAX - 1);
        }
    }

    float*** gradient = computeGradient(pureNoise, (int)(w/scale), (int)(h/scale));
}**/

float** heightMap(int w, int h, float nbOctaves, float biais)
{
    float scale = 1.f;

    float** pureNoise = new float*[(int)(w/scale) + 2];
    for (int i = 0 ; i < (int)(w/scale) + 2 ; i++) {
        pureNoise[i] = new float[(int)(h/scale) + 2];
        for (int j = 0 ; j < (int)(h/scale) + 2 ; j++) {
            pureNoise[i][j] = (float)(rand() % RAND_MAX) / float(RAND_MAX - 1);
        }
    }

    ///float*** gradient = computeGradient(pureNoise, (int)(w/scale) + 2, (int)(h/scale) + 2);

    float** map = new float*[w];
    for (int i = 0 ; i < w ; i++) {
        map[i] = new float[h];
        for (int j = 0 ; j < h ; j++) {
            //map[i][j] = perlin((float)(i) / scale, (float)(j) / scale, gradient);
            float noise = 0.f;
            scale = 1.f;
            float scale_sum = 0.f;
            for (int k = 0 ; k < nbOctaves ; k++) {
                int local_scale = w >> k;
                int x1 = (int)(i / local_scale) * local_scale;
                int y1 = (int)(j / local_scale) * local_scale;
                int x2 = (x1 + local_scale) % w;
                int y2 = (y1 + local_scale) % h;

                float blendx = (float)(i - x1) / (float)local_scale;
                float blendy = (float)(j - y1) / (float)local_scale;

                //std::cout<<"i="<<i<<" j="<<j<<" local="<<local_scale<<" o="<<k<<" x1="<<x1<<" y1="<<y1<<" x2="<<x2<<" y2="<<y2<<"\n";
                float sample1 = (1.0f - blendx) * pureNoise[x1][y1] + blendx * pureNoise[x2][y1];
                float sample2 = (1.0f - blendx) * pureNoise[x1][y2] + blendx * pureNoise[x2][y2];

                noise += (blendy * (sample2 - sample1) + sample1) * scale;
                scale_sum += scale;
                scale = scale / biais;
            }
            map[i][j] = noise / scale_sum;
            //std::cout<<"i="<<i<<" j="<<j<<": "<<map[i][j]<<"\n";
        }
    }

    scale = 1.f;
    for (int i = 0 ; i < (int)(w/scale) + 2 ; i++) { delete[] pureNoise[i]; }
    delete[] pureNoise;
    /**for (int i = 0 ; i < (int)(w/scale) + 2 ; i++) {
        for (int j = 0 ; j < (int)(h/scale) + 2 ; j++) {
            delete[] gradient[i][j];
        }
        delete[] gradient[i];
    }
    delete[] gradient;**/
    return map;
}


