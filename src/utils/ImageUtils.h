//
// Created by Tomás Macía on 05/11/2019.
//

#ifndef GAME_IMAGEUTILS_H
#define GAME_IMAGEUTILS_H

#include <string>

struct ImageSize {
    int width;
    int height;
};

class ImageUtils {
public:
    static ImageSize getImageSize(std::string);
};


#endif //GAME_IMAGEUTILS_H
