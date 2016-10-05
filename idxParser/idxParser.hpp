//
//  idxParser.hpp
//  PinaPL
//

#ifndef DEF_IDXPARSER
#define DEF_IDXPARSER

#include<vector>
#include <zlib.h>

class IdxParser {
public:
    IdxParser();
    gzFile importGzFile(std::string path);
    void testIdxParser();
};

#endif // DEF_IDXPARSER
