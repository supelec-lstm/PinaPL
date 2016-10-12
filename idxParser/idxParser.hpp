//
//  idxParser.hpp
//  PinaPL
//

#ifndef DEF_IDXPARSER
#define DEF_IDXPARSER

#include<vector>
#include<zlib.h>

class IdxParser {

private:
    gzFile importGzFile(std::string& path);

public:
    IdxParser();
    std::vector<std::vector<double> > importMNISTImages(std::string& path);
    std::vector<double> importMNISTLabels(std::string& path);
};

#endif // DEF_IDXPARSER
