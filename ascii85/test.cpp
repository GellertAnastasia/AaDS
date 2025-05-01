#include "ascii85.h"

int main(int argc, char* argv[]) {
    if (argc == 1)
    {
        encode();
    }
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-d") {
            decode();
        } else if (arg == "-e") {
            encode();
        } else {
            return 1;
        }
    }
       
            
            
    return 0;       
}
