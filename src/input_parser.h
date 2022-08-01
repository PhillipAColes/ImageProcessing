#include <string>
#include <iostream>
#include <vector>

class InputParser
{
private:
    const std::string in_file_path;
    const std::string out_file_path;
    struct OptionalArg
    {
        std::string name;
        int value;
    };
    std::vector<OptionalArg> optional_args;
    void parse_optional_arg(char* arg);
public:
    InputParser(int argc, char* argv[]);
    std::string get_in_file_path();
    std::string get_out_file_path();
};