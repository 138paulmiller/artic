#include <math.h>
#include "image.hpp"

int main(){
	const char * OUT_FILE = "OUT.ppm";
	const int W = 255;
	const int H = 255;
	Image<HDR> img(W,H);
	int cx =W/2; int cy = H/2;
	int radius = (W+H)/4;
	double d = 0;
	for(int y =0; y < H; ++y){
		for(int x =0; x < W; ++x){
			d = sqrt((x-cx)*(x-cx)+(y-cy)*(y-cy));
			if(d < radius)
				0;
				img.pixel(x,y).set((double)x/W ,0, 0);
		}
	}

	remove(OUT_FILE);
	Image<HDR>::exportPPM(OUT_FILE, img);
}