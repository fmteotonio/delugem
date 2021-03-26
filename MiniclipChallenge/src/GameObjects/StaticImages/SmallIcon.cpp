#include "SmallIcon.h"

const int SmallIcon::cW = 8;
const int SmallIcon::cH = 8;

SmallIcon::SmallIcon(float x, float y, std::string filename) : StaticImage(x,y,cW,cH,filename){
}