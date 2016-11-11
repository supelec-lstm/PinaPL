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
    std::vector<std::vector<int> > importMNISTImages(std::string& path);
    std::vector<int> importMNISTLabels(std::string& path);
    
private:
    gzFile importGzFile(std::string& path);
};

#endif // DEF_IDXPARSER
