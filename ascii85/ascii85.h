#ifndef ASCII85_H
#define ASCII85_H
#include <iostream>
#include <cstring>
#include <sstream>


uint32_t to_uint32_be(const char* bytes);
void encode(std::istream& in, std::ostream& out);
void decode();

#endif
