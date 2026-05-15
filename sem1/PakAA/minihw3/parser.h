#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "shop.h"

class Parser {
public:
	static std::vector<Shop> parseFile(const std::string& filename);
};

#endif  // PARSER_H