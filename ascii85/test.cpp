#include "ascii85.h"


int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::string input;
        std::getline(std::cin, input);

        std::istringstream in(input);
        encode(in, std::cout);
        std::cout << std::endl;
    }
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-d")
        {
            std::string input;
            std::getline(std::cin, input); 
            std::istringstream in(input);
            decode(in, std::cout);
            std::cout << std::endl;
        }
        else if (arg == "-e")
        {
            std::string input;
            std::getline(std::cin, input);

            std::istringstream in(input);
            encode(in, std::cout);
            std::cout << std::endl;
        }
        else
        {
            return 1;
        }
    }



    return 0;
}
