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

    BmpImage bmp_image(input.in_file_path);

    //bmp_image.print_pixels();
    //bmp_image.flip_x();
    //bmp_image.flip_y();
    //bmp_image.greyscale();
    //bmp_image.brightness(-0.4);
    bmp_image.contrast(-0.001);

    bmp_image.write_bmp_file(input.out_file_path);
}