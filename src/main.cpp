#include "math.hpp"
#include "util.hpp"
#include <cmath>
int main(){

	const int W = 255;
	const int H = 255;
	HDR img[H*W];
	int cx =W/2; int cy = H/2;
	int radius = (W+H)/4;
	float d = 0;
	for(int y =0; y < H; ++y){
		for(int x =0; x < W; ++x){
			d = sqrt((x-cx)*(x-cx)+(y-cy)*(y-cy));
			if(d < radius){
				img[y*W+x].r = (double)x/W;
				img[y*W+x].g = (double)y/H;

			}
		}
	}
	writePPM("Out.ppm", img, W, H);

}
