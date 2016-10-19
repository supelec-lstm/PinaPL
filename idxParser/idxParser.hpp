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
    std::vector<std::vector<double>> importMNISTImages(std::string& path, bool log = false);
    std::vector<double> importMNISTLabels(std::string& path, bool log = false);
    
private:
    gzFile importGzFile(std::string& path);
};

#endif // DEF_IDXPARSER
