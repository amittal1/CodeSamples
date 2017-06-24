#include <iostream>
#include <fstream>
#include <cstdint>
using namespace std;

class Bitmap {
private:
    uint32_t* bitmap;
    int w, h;
    const uint32_t defval = 0x0000000F; //Chose default value and other values
                                        //to make every function's implementation visible

public:
    Bitmap(const int w, const int h) : w(w), h(h) { // w as y and h as x
        bitmap = new uint32_t[this->w*this->h];
        for (int i=0; i<this->w; i++){
            for(int j=0; j<this->h; j++)
                bitmap[i*this->h + j]= defval;
        }
    }
    ~Bitmap() {
        delete [] bitmap;
    }
    void fillRect(int x, int y, int w, int h, int rgba) {
        if ((x < this->w) && (y < this->h) && ((x+w) < this->w) && ((y+h) < this->h)){
            for (int i=y; i<y+h; i++){
                for(int j=x-1; j<x+w; j++){
                    bitmap[(i*this->h) + (j)]= rgba;
                }
            }
        }
    }
    void horizLine(int x1, int x2, int y, int rgba) {
      if(x1>x2){
      x1 +=x2;
      x2 = x1-x2;
      x1 -=x2;
      }
        for (int i=x1; i<=x2; i++)
            bitmap[(y-1)*h + i]= rgba;
    }

    void vertLine(int y1, int y2, int x, int rgba) {
        if(y1>y2){
        y1 +=y2;
        y2 = y1-y2;
        y1 -=y2;
        }
          for (int i=y1-1; i<y2; i++)
              bitmap[i*h + x-1]= rgba;
    }
    void line(int x1, int y1, int x2, int y2, int rgba) {
        if(x1>x2){
        x1 +=x2;
        x2 = x1-x2;
        x1 -=x2;
        }
        if(y1>y2){
        y1 +=y2;
        y2 = y1-y2;
        y1 -=y2;
        }
        //double m1= (double)(x2-x1)/(y2-y1);
        int m=(x2-x1)/(y2-y1);
        int c= ((x1*y2) - (x2*y1))/(y2-y1);
        //cout << "m & c is" << m << c << "\n";
        //if(m1-m>0.5)
          //  m++;
        bitmap [(y1-1)*h + (x1-1)]= rgba;
        for (int i = y1; i<y2; i++){
        int j= ((int)m * i) + c;
        bitmap [i*h + j] = rgba;
        }
    }

    void point(int x, int y, int rgba) {
        bitmap[((y-1)*this->h) + (x-1)]= rgba;
        }

    void floodFill(int x, int y, int rgba) {

        for (int i=y; i<w; i++){
            for(int j=x; j<h; j++){
                if (bitmap[(i*h) + (j)]==0x00000000 || bitmap[(i*h) + (j)]==defval)
                bitmap[(i*h) + (j)]= rgba;
            }
        }
        for (int i=y-1; i>=0; i--){
            for(int j=x; j<h; j++){
                if (bitmap[(i*h) + (j)]==0x00000000  || bitmap[(i*h) + (j)]==defval)
                bitmap[(i*h) + (j)]= rgba;
            }
        }
        for (int i=y; i<w; i++){
            for(int j=x-1; j>=0; j--){
                if (bitmap[(i*h) + (j)]==0x00000000  || bitmap[(i*h) + (j)]==defval)
                bitmap[(i*h) + (j)]= rgba;
            }
        }
        for (int i=y-1; i>=0; i--){
            for(int j=x-1; j>=0; j--){
                if (bitmap[(i*h) + (j)]==0x00000000  || bitmap[(i*h) + (j)]==defval)
                bitmap[(i*h) + (j)]= rgba;
            }
        }
    }

    friend ostream& operator <<(ostream& s, const Bitmap& a) {
        for (int i=0; i<a.w; i++){
            for(int j=0; j<a.h; j++)
                s << a.bitmap[i*a.h + j] << ' ';
            s<< "\n";
        }
        return s;
    }
};

int main() {
    Bitmap b(10, 14); // w, h, default color
    cout << b << '\n';
    b.fillRect(3, 4, 4, 4, 0xFFFFFFFF);
    cout << b << '\n';
    b.point(9,3, 0xFFFFFFFF); // bottom right point
    cout << b << '\n';
    b.horizLine(7,9,6,0xFFFFFFFF);
    cout << b << '\n';
    b.vertLine(3,5,7,0xFFFFFFFF);
    cout << b << '\n';
    b.line(2,3,8,9,0xFFFFFFFF);
    cout << b << '\n';
    b.floodFill(7,8, 0x000000F0); //fill in place of no colour or default colour
    cout << b << '\n';
}
