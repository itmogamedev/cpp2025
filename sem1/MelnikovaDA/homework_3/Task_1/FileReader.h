#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <memory>
#include "Shop.h"

class FileReader {
public:
    static std::vector<Shop> readShopsFromFile(const std::string& filename);
};

#endif