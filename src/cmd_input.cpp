#include "cmd_input.h"


CmdInput::CmdInput(int argc, char* argv[]): 
    in_file_path(argv[1]),
    out_file_path(argv[2])
{
    if(in_file_path.compare(out_file_path) == 0)
    {
        std::cout << "Error: input file and output file are the same!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> found_optionals;
    for(int i = 3; i < argc; i++)
    {
        auto optional_arg = parse_optional_arg(argv[i]);
        for(auto found_optional : found_optionals)
        {
            if(optional_arg.name == found_optional)
            {
                std::cout << "Error: argument '" << optional_arg.name << 
                "' cannot appear more than once in argument list" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        found_optionals.push_back(optional_arg.name);
        optional_args.push_back(optional_arg);
    }
};

CmdInput::OptionalArg CmdInput::parse_optional_arg(char* arg)
{
    if(arg[0] != '-' || arg[1] != '-')
    {
        std::cout << "Error: invalid optional argument, expect '--'" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string name("");
    std::string s_factor("");
    bool has_factor = false;
    int i = 2;
    while(arg[i])
    {
        if(arg[i] == '=')
        {
            i++;
            has_factor = true;
            break;
        }
        else
        {
            name = name + arg[i];
        }
        i++;
    }

    if(allowed_parameterised_options.find(name) == allowed_parameterised_options.end() && 
       allowed_non_parameterised_options.find(name) == allowed_non_parameterised_options.end())
    {
        std::cout << "Error: " << name << " option not recognised" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(allowed_parameterised_options.find(name) != allowed_parameterised_options.end() && !has_factor)
    {
        std::cout << "Error: please provide a value for " << name << " option " << std::endl;
        exit(EXIT_FAILURE);
    }
    if(allowed_non_parameterised_options.find(name) != allowed_non_parameterised_options.end() && has_factor)
    {
        std::cout << "Error: unexpected parameter for " << name << " option " << std::endl;
        exit(EXIT_FAILURE);
    }  

    if(has_factor)
    {
        bool decimal = false;
        if(arg[i] == '-')
        {
            s_factor = s_factor + arg[i];
            i++;
        }
        while(arg[i])
        {
            if(isdigit(arg[i]) || (arg[i] == '.' && !decimal))
            {
                s_factor = s_factor + arg[i];
            }
            else if(arg[i] == '.' && !decimal)
            {
                decimal = true;
            }
            else
            {
                std::cout << "Error: Invalid character " << arg[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            i++;
        }

        if(s_factor == "" || s_factor == "-")
        {
            std::cout << "Error: please provide a value for " << name << " option" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        double factor = std::stod(s_factor);
        if(factor >= 1.0 || factor <= -1.0)
        {
            std::cout << "Error: factor shoule be between -1.0 and 1.0, value found factor = " << factor << std::endl;
            exit(EXIT_FAILURE);   
        }
        return OptionalArg(name, factor, has_factor);
    }
    
    return OptionalArg(name, 0, has_factor);
} 