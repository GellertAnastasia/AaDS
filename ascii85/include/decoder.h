#ifndef DECODER_H
#define DECODER_H
#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdint>
#include <vector>

void decode_block(const char* input, size_t padding, std::ostream& out);
void decode(std::istream& in, std::ostream& out);

#endif
