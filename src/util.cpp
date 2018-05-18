#include "util.hpp"
#include "color.hpp"

void writePPM(const char* filename, RGB* data, int w, int h)
{
    std::ofstream ofs;
    /*
    P3
    # filname
    w h
    max
    r g b
    r g b ....
    */
    if(data){
        ofs.open(filename, std::ios::out);
        ofs << "P6\n#"  << filename << "\n" 
                        << w << "\n" << h << "\n"
                        << RGB_DEPTH << "\n";
        int i =0;
        char pixel[3];
        RGB rgb;
        for(int y=0; y<h; y++) {
            for(int x=0; x<w; x++) {
                i= w*y+x;
                pixel[0]=data[i].r();
                pixel[1]=data[i].g();
                pixel[2]=data[i].b();
                ofs.write((char*)pixel, 3);
            }
        }
        ofs.close();
    }
}
