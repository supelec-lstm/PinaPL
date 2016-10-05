//
//  idxParser.cpp
//  PinaPL
//

#include <iostream>
#include <fstream>
#include <ios>
#include <sys/stat.h>
#include <sstream>

#include "idxParser.hpp"

using namespace std;

IdxParser::IdxParser() {
}


void importLabelFile(string path) {

    string filePath = path;

    // get file size
    struct stat results;

    const char* pathChared = path.c_str();

    if (stat(pathChared, &results) == 0) {
    } else {
        cout << "Error: cannot read file" << endl;
    }

    // results.st_size contains the file's byte size

    // open the file
    ifstream data;
    data.open(filePath, ios::in | ios::binary);

    // read the file
    // read magic number
    char magicNumber[3];
    data.read(magicNumber, 3);

    cout << magicNumber << endl;

    return;
}

void testIdxParser() {

    importLabelFile("idxParser/train-images-idx3-ubyte.gz");
    return;
}

