#include "encoder.h"
#include "decoder.h"

int main(int argc, char* argv[])
{
    bool decode_mode = false;
    bool use_stdin = true;
    std::string data;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            decode_mode = true;
        }
        else if (strcmp(argv[i], "-e") == 0)
        {
            decode_mode = false;
        }
        else if (argv[i][0] != '-')
        {
            use_stdin = false;
            data = argv[i];
        }
    }

    try
    {
        if (use_stdin)
        {
            if (decode_mode)
            {
                decode(std::cin, std::cout);
            }
            else
            {
                encode(std::cin, std::cout);
            }
        }
        else
        {
            std::istringstream input(data, std::ios::binary);
            if (decode_mode)
            {
                decode(input, std::cout);
            }
            else
            {
                encode(input, std::cout);
            }
        }
    }
    
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
