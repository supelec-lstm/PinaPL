//
//  idxParser.cpp
//  PinaPL
//

#include <iostream>
#include <fstream>
#include <ios>
#include <sstream>
#include <zlib.h>

#include "idxParser.hpp"

using namespace std;

IdxParser::IdxParser() {
}

typedef struct gzFile_s *gzFile;

gzFile IdxParser::importGzFile(string path) {
    const char * pathChared = path.c_str();
    gzFile file = gzopen(pathChared, "rb");
    return file;
}

void IdxParser::testIdxParser() {
    // import an image file
    gzFile file = importGzFile("idxParser/train-images-idx3-ubyte.gz");
    // magic number
    uint8_t magicNumber[4];
    gzread(file, &magicNumber, sizeof(magicNumber));
    cout << "magicNumber: " << int32_t(magicNumber[0] << 24 | magicNumber[1] << 16 | magicNumber[2] << 8 | magicNumber[3]) << endl;
    // number of images
    uint8_t imageCount[4];
    gzread(file, &imageCount, sizeof(imageCount));
    cout << "imageCount: " << int32_t(imageCount[0] << 24 | imageCount[1] << 16 | imageCount[2] << 8 | imageCount[3]) << endl;

    return;
}

