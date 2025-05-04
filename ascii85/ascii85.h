#ifndef ASCII85_H
#define ASCII85_H
#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdint>
#include <vector>

uint32_t to_uint32_be(const char* bytes);
void encode(std::istream& in, std::ostream& out);
void decode_block(const char* input, size_t padding, std::ostream& out);
void decode(std::istream& in, std::ostream& out);

#endif
