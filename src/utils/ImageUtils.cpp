//
// Created by Tomás Macía on 05/11/2019.
//

#include "ImageUtils.h"
#include <fstream>
#include <arpa/inet.h> // for ntohl


ImageSize ImageUtils::getImageSize(std::string path) {
    std::ifstream in(path);
    unsigned int width, height;
    ImageSize imageSize{0, 0};

    in.seekg(16);
    in.read((char *)&width, 4);
    in.read((char *)&height, 4);


    width = ntohl(width);
    height = ntohl(height);

    imageSize.width = (int) width;
    imageSize.height = (int) height;

    return imageSize;
}