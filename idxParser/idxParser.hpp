//
//  idxParser.hpp
//  PinaPL
//

#ifndef DEF_IDXPARSER
#define DEF_IDXPARSER

#include<vector>

class IdxParser {
private:
public:
    IdxParser();
    void importLabelFile(std::string path);
    void testIdxParser();
};

#endif // DEF_IDXPARSER
