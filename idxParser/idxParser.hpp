//
//  idxParser.hpp
//  PinaPL
//

#ifndef DEF_IDXPARSER
#define DEF_IDXPARSER

#include<vector>
#include<zlib.h>

class IdxParser {
public:
    IdxParser();
    gzFile importGzFile(std::string path);
    std::vector<std::vector<int32_t>> importMNISTImages(std::string path);
    std::vector<int> importMNISTLabels(std::string path);
};

#endif // DEF_IDXPARSER
