#include "input_parser.h"


InputParser::InputParser(int argc, char* argv[]): 
    in_file_path(argv[1]),
    out_file_path(argv[2])
{
    if(in_file_path.compare(out_file_path) == 0)
    {
        std::cout << "in file and out file are the same!" << std::endl;
    }

    for(int i = 3; i < argc; i++)
    {
        parse_optional_arg(argv[i]);
    }
};

void InputParser::parse_optional_arg(char* arg)
{
    std::cout << arg << std::endl;
} 