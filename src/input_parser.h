#include <string>
#include <iostream>
#include <vector>

class InputParser
{
private:
    struct OptionalArg
    {
        std::string name;
        int value;
        bool has_value;
    };
    std::vector<OptionalArg> optional_args;
    void parse_optional_arg(char* arg);
public:
    const std::string in_file_path;
    const std::string out_file_path;
    InputParser(int argc, char* argv[]);
};