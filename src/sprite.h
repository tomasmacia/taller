#ifndef SPRITE_H
#define SPRITE_H
#include <string>

class Sprite{ //ES UN OBJETO/STRUCT QUE CONTIENE EL PATH DEL SPRITE A CARGAR Y EL COLOR AL QUE HACER TRANSPARENTE

private:

   const std::string _image_path;
    int _r_transparent;
    int _g_transparent;
    int _b_transparent;
    
public:    
    Sprite(std::string image_path,int r_transparent,int g_transparent,int b_transparent);
    std::string getImagePath();
    int getRTransparent();
    int getGTransparent();
    int getBTransparent();
};
#endif