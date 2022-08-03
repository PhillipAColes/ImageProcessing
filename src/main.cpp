#include "bmp.h"
#include "cmd_input.h"
#

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        std::cout << "Error: please specify an input and output file." << std::endl;
        return EXIT_FAILURE;
    }

    CmdInput cmd_input(argc, argv);
    BmpImage bmp_image(cmd_input.in_file_path);

    for(auto arg : cmd_input.optional_args)
    {
        if(arg.has_factor)
        {
            bmp_image.do_operation(arg.name, arg.factor);
        }
        else
        {
           bmp_image.do_operation(arg.name);
        }
    }

    bmp_image.write_bmp_file(cmd_input.out_file_path);
}