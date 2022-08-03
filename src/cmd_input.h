#include <string>
#include <iostream>
#include <vector>
#include <set>

class CmdInput
{
private:
    struct OptionalArg
    {
        std::string name;
        double factor;
        bool has_factor;
        OptionalArg(std::string name_, double factor_, bool has_factor_):
            name(name_), factor(factor_), has_factor(has_factor_)
            {} 
    };
    std::set<std::string> allowed_parameterised_options = 
        {"brightness", "contrast"};
    std::set<std::string> allowed_non_parameterised_options = 
        {"flipX", "flipY", "greyscale"};

    OptionalArg parse_optional_arg(char* arg);
public:
    std::string in_file_path;
    std::string out_file_path;
    std::vector<OptionalArg> optional_args;

    CmdInput(int argc, char* argv[]);
};