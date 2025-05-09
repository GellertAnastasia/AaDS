#include "decoder.h"

void decode_block(const char* buffer, size_t padding, std::ostream& out)
{
    uint32_t number = 0;
    for (int i = 0; i < 5; ++i)
    {
        number = number * 85 + (static_cast<unsigned char>(buffer[i]) - 33);
    }

    char decoded[4];
    decoded[0] = (number >> 24) & 0xFF;
    decoded[1] = (number >> 16) & 0xFF;
    decoded[2] = (number >> 8) & 0xFF;
    decoded[3] = number & 0xFF;

    size_t output_len = (padding > 0) ? 4 - padding : 4;
    out.write(decoded, output_len);
}

void decode(std::istream& in, std::ostream& out)
{
    std::vector<char> buffer;
    char ch;
    while (in.get(ch))
    {
        if (std::isspace(ch) && ch != ' ') {
            continue;
        }

        if (ch == 'z')
        {
            if (!buffer.empty())
            {
                throw std::runtime_error("'z' in the middle of block");
            }
            char zero[4] = { 0, 0, 0, 0 };
            out.write(zero, 4);
            continue;
        }
        if (ch < 33 || ch > 117) {
            throw std::runtime_error("Invalid ASCII85 character");
        }
        buffer.push_back(ch);
        if (buffer.size() == 5)
        {
            decode_block(buffer.data(), 0, out);
            buffer.clear();
        }
    }

    if (!buffer.empty())
    {
        if (buffer.size() < 2)
        {
            throw std::runtime_error("Last block less than 2 characters");
        }
        size_t padding = 5 - buffer.size();
        if (padding > 0)
        {
            buffer.insert(buffer.end(), padding, 'u');
        }
        decode_block(buffer.data(), padding, out);
    }
}

