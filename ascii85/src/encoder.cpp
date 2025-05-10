#include "encoder.h"

uint32_t to_uint32_be(const char* bytes)
{
    return (static_cast<unsigned char>(bytes[0]) << 24) |
           (static_cast<unsigned char>(bytes[1]) << 16) |
           (static_cast<unsigned char>(bytes[2]) << 8) |
           static_cast<unsigned char>(bytes[3]);
}

void encode_block(const char* buffer, size_t padding, std::ostream& out)
{
    uint32_t number = to_uint32_be(buffer);
    char encoded[5];
    for (int i = 4; i >= 0; --i)
    {
        encoded[i] = static_cast<char>(number % 85 + 33);
        number /= 85;
    }
    size_t output_len = (padding > 0) ? 5 - padding : 5;
    out.write(encoded, output_len);
}
void encode(std::istream& in, std::ostream& out)
{
    std::vector<char> buffer;
    char ch;
    while (in.get(ch))
    {
        buffer.push_back(ch);
        if (buffer.size() == 4)
        {
            bool all_zero = true;
            for (size_t i = 0; i < 4; ++i)
            {
                if (buffer[i] != 0)
                {
                    all_zero = false;
                    break;
                }
            }
            if (all_zero)
            {
                std::cout << 'z';
            }
            else
            {
                encode_block(buffer.data(), 0, out);
                buffer.clear();
            }
        }
    }
    if (!buffer.empty())
    {
        size_t padding = 4 - buffer.size();
        if (padding > 0)
        {
            buffer.insert(buffer.end(), padding, 0);
        }
        encode_block(buffer.data(), padding, out);
    }
}
