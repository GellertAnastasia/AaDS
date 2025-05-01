#include "ascii85.h"

void encode()
{
    const size_t SIZE = 4;
    char buffer[SIZE];
    while (true)
    {
        std::memset(buffer, 0, SIZE);
        std::cin.read(buffer, SIZE);
        size_t read = std::cin.gcount();
        if (read == 0)
        {
            break;
        }
        size_t padding = 4 - read;
        if (padding != 0)
        {
            std::memset(buffer + read, 0, padding);
        }
        std::cout.write(buffer, SIZE);
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

