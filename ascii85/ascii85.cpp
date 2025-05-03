#include "ascii85.h"
#include <iostream>
#include <cstring>
#include <string>

uint32_t to_uint32_be(const char* bytes) {
    return (static_cast<unsigned char>(bytes[0]) << 24) |
           (static_cast<unsigned char>(bytes[1]) << 16) |
           (static_cast<unsigned char>(bytes[2]) << 8) |
           static_cast<unsigned char>(bytes[3]);
}

void encode(std::istream& in, std::ostream& out) {
    const size_t SIZE = 4;
    char buffer[SIZE];

    while (true) {
        in.read(buffer, SIZE);
        size_t read = in.gcount();
        if (read == 0) break;

        bool all_zero = true;
        for (size_t i = 0; i < SIZE; ++i) {
            if (buffer[i] != 0) {
                all_zero = false;
                break;
            }
        }
        size_t padding = SIZE - read;
        if (padding > 0) {
            std::memset(buffer + read, 0, padding);
        }
        
        if (read == 4 && all_zero) {
            std::cout << 'z';
        } else {
            uint32_t number = to_uint32_be(buffer);
            char encoded[5];
            for (int i = 4; i >= 0; --i) {
                encoded[i] = static_cast<char>(number % 85 + 33);
                number /= 85;
            }
            size_t output_len = (read < 4) ? read + 1 : 5;
            out.write(encoded, output_len);
        }

    }
}

void decode()
{
    const size_t SIZE = 5;
    char buffer[SIZE];

    while (true)
    {
        std::cin.read(buffer, SIZE);
        size_t read = std::cin.gcount();

        if (read == 0)
        {
            break;
        }

        if (read < SIZE)
        {
            throw std::runtime_error("decoding error");
        }

        std::cout.write(buffer, SIZE);
    }
}

