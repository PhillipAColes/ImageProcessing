#include <iostream>
#include <fstream>
#include <ostream>
#include <array>
#include <vector>
#include <algorithm>
#include <math.h>

class BmpImage
{
//private:
public:
    std::string in_file_path;

    /* BMPFileHeader */
    uint16_t _file_type; // File type always BM which is 0x4D42
    uint32_t _file_size; // Size of the entire file (in bytes)
    uint16_t _reserved1; // Reserved, always 0
    uint16_t _reserved2; // Reserved, always 0
    uint32_t _offset_data; // Start position of pixel data (bytes offset from start of file)

    /* BMPInfoHeader */
    uint32_t _size; // Size of BMPInfoHeader (in bytes)
    int32_t _width; // width of bitmap in pixels
    int32_t _height; // height of bitmap in pixels
    // (if positive, bottom-up, with origin in lower left corner)
    // (if negative, top-down, with origin in upper left corner)
    uint16_t _planes; // No. of planes for the target device, this is always 1
    uint16_t _bit_count; // No. of bits per pixel
    uint32_t _compression; // 0 for uncompressed images. Only handle this case.
    uint32_t _size_image; // Size of pixel data in bytes
    int32_t _x_pixels_per_meter; // Typically 2834
    int32_t _y_pixels_per_meter; // Typically 2834
    uint32_t _colors_used; // No. color indexes used. Use 0 for 32-bit bitmaps
    uint32_t _colors_important; // No. of colors used. Use 0 for 32-bit bitmaps

    struct Pixel
    {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t alpha;
        Pixel(uint8_t b, uint8_t g, uint8_t r, uint8_t a):
            blue(b), green(g), red(r), alpha(a)
        {};
    };
    //std::array<Pixel>* pixels = NULL; // Array to hold pixels 
    std::vector<std::vector<Pixel>> pixels;

public:
    BmpImage(std::string bmp_file_path);

    void set_file_type(uint16_t file_type);
    void set_file_size(uint32_t file_size);
    void set_offset_data(uint32_t offset_data);

    void set_size(uint32_t size);
    void set_width(int32_t width);
    void set_height(int32_t height);
    void set_planes(uint16_t planes);
    void set_bit_count(uint16_t bit_count);
    void set_compression(uint32_t compression);
    void set_size_image(uint32_t size_image);
    void set_x_pixels_per_meter(int32_t x_pixels_per_meter);
    void set_y_pixels_per_meter(int32_t y_pixels_per_meter);
    void set_colors_used(uint32_t colors_used);
    void set_colors_important(uint32_t colors_important);

    void read_bmp_file_header(std::ifstream& in_stream);
    void read_bmp_info_header(std::ifstream& in_stream);
    void read_bmp_pixels(std::ifstream& in_stream);
    void read_bmp_file();

    void write_bmp_file_header(std::ofstream& out_stream)const;
    void write_bmp_info_header(std::ofstream& out_stream)const;
    void write_bmp_pixels(std::ofstream& out_stream)const;
    void write_bmp_file(std::string out_file_path);

    void write_small_bmp_file(std::string out_file_path);
    void write_small_bmp_pixels(std::ofstream& out_stream)const;

    void print_pixels();

    void flip_x();
    void flip_y();
    void greyscale();
    void brightness(double factor);
    void contrast(double factor);
};

uint8_t read_uint8(std::ifstream& in_stream);
uint16_t read_uint16(std::ifstream& in_stream);
uint32_t read_uint32(std::ifstream& in_stream);