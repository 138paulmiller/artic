#include <stdio.h>
void writePPM(const char* filename, int w, int h, Color* data)
{
	FILE * f = fopen(filename, "w");
    fprintf(f,"P6\n%d\n%d\n%d",w,h,255);
	int i =0,y,x;
    for(y=0; y<h; y++) {
        for(x=0; x<w; x++) {
			i= w*y+x;
            char c[3] = { data[i].r, data[i].g, data[i].b };
            fwrite(c, sizeof(char), 3, f);
        }
    }
    fclose(f);
}
