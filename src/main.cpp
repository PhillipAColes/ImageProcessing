#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

#include "bmp.h"
#include "input_parser.h"

/*
typedef void (*processing_function)(void); // function pointer type

void flip_x(){std::cout << "flip_x" << std::endl;};
void flip_y(){std::cout << "flip_y" << std::endl;};

//std::map<std::string, std::string (*)()> m;
// ( {{"apple","red"},{"lemon","yellow"}} );

const static std::unordered_map<std::string, processing_function> processing_functions
({
    {"flipX", flip_x},
    {"flipY", flip_y}
});
*/


int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        std::cout << "Error: please specify an input and output file." << std::endl;
        return 1;
    }

    InputParser input(argc, argv);

    // here open the file
    //std::ifstream in_stream(input.get_in_file_path(), std::ios::in | std::ios::binary);
    //if (!in_stream)
    //{
    //    std::cout << "Error!" << std::endl;
    //}
    std::cout << "here......" << std::endl;
    BmpImage bmp_image(input.get_in_file_path());

    std::cout << "here......" << std::endl;
    bmp_image.write_bmp_file(input.get_out_file_path());

    //read_bmp_file(in_stream, bmp_image);

}