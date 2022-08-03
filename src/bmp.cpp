#include "bmp.h"

uint8_t read_uint8(std::ifstream& in_stream)
{
    return in_stream.get();
}

uint16_t read_uint16(std::ifstream& in_stream)
{
    char buff[2]; //char is always 1 byte
    in_stream.read(buff, 2); // read two bytes into char array
    uint8_t c0 = buff[0]; // little endian so least significant
    uint8_t c1 = buff[1]; // little endian so most significant
    return (c1 << 8) | c0; // leftshift most significant by one byte and combine into big endian
}

uint32_t read_uint32(std::ifstream& in_stream)
{
    char buff[4]; //char is always 1 byte
    in_stream.read(buff, 4); // read four bytes into char array
    uint8_t c0 = buff[0]; // little endian so least significant
    uint8_t c1 = buff[1];
    uint8_t c2 = buff[2];
    uint8_t c3 = buff[3]; // little endian so most significant
    return (c3 << 24) | (c2 << 16) | (c1 << 8) | c0; // back to big endian
}

int32_t read_int32(std::ifstream& in_stream)
{
    char buff[4]; //char is always 1 byte
    in_stream.read(buff, 4); // read four bytes into char array
    uint8_t c0 = buff[0]; // little endian so least significant
    uint8_t c1 = buff[1];
    uint8_t c2 = buff[2];
    uint8_t c3 = buff[3]; // little endian so most significant
    return (c3 << 24) | (c2 << 16) | (c1 << 8) | c0; // back to big endian
}

BmpImage::BmpImage(std::string in_file_path_): in_file_path(in_file_path_)
{
    read_bmp_file();
}

void BmpImage::read_bmp_file_header(std::ifstream& in_stream)
{
    _file_type = read_uint16(in_stream);
    if(_file_type != 0x4D42)
    {
        std::cout << "Error: incorrect file type read from file! Expected 0x4D42, found "
            << std::hex << _file_type << std::dec << std::endl;
        in_stream.close();
        exit(EXIT_FAILURE);
    }
    _file_size = read_uint32(in_stream);
    _reserved1 = read_uint16(in_stream);
    _reserved2 = read_uint16(in_stream);
    _offset_data = read_uint32(in_stream);
}

void BmpImage::read_bmp_info_header(std::ifstream& in_stream)
{
    _size = read_uint32(in_stream);
    _width = read_int32(in_stream);
    _height = read_int32(in_stream);
    _planes = read_uint16(in_stream);
    _bit_count = read_uint16(in_stream);
    if(_bit_count != 32)
    {
        std::cout << "Error: incorrect bit count read from file! Expected 32-bit pixels, found "
            << (unsigned)_bit_count << std::endl;
        in_stream.close();
        exit(EXIT_FAILURE);
    }
    _compression = read_uint32(in_stream);
    if(_compression != 0)
    {
        std::cout << "Error: incorrect compression read from file! Expected uncompressed file, found" 
            << (unsigned)_compression << std::endl;
        in_stream.close();
        exit(EXIT_FAILURE);
    }
    _size_image = read_uint32(in_stream);
    _x_pixels_per_meter = read_int32(in_stream);
    _y_pixels_per_meter = read_int32(in_stream);
    _colors_used = read_uint32(in_stream);
    _colors_important = read_uint32(in_stream);
}

void BmpImage::read_bmp_pixels(std::ifstream& in_stream)
{
    pixels.resize(_height, std::vector<Pixel>(_width, Pixel(0,0,0,0)));
    // TODO: point stream to _offset_data where image starts
    for(unsigned i = 0; i < (unsigned)_height; i++)
    {
        for(unsigned j = 0; j < (unsigned)_width; j++)
        {
            pixels[i][j].blue = in_stream.get();
            pixels[i][j].green = in_stream.get();
            pixels[i][j].red = in_stream.get();
            pixels[i][j].alpha = in_stream.get();
        }
    }
}

void BmpImage::read_bmp_file()
{
    std::cout << "Reading bmp file... " << in_file_path << std::endl;
    std::ifstream in_stream(in_file_path, std::ios::in | std::ios::binary);
    if (!in_stream)
    {
        std::cout << "Error reading bmp file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Reading file header..." << std::endl;
    read_bmp_file_header(in_stream);

    std::cout << "Reading info header..." << std::endl;
    read_bmp_info_header(in_stream);

    std::cout << "Reading pixels..." << std::endl;
    read_bmp_pixels(in_stream);

    std::cout << "... done!" << std::endl;
}


void write_uint16(std::ofstream& out_stream, uint16_t ui16)
{
    out_stream.put(ui16 & 0xFF);
    out_stream.put((ui16 >> 8) & 0xFF);
}

void write_uint32(std::ofstream& out_stream, uint32_t ui32)
{
    out_stream.put(ui32 & 0xFF); // mask ui32 with & 0000000011111111
    out_stream.put((ui32 >> 8) & 0xFF);
    out_stream.put((ui32 >> 16) & 0xFF);
    out_stream.put((ui32 >> 24) & 0xFF);
}

void write_int32(std::ofstream& out_stream, int32_t i32)
{
    out_stream.put(i32 & 0xFF);
    out_stream.put((i32 >> 8) & 0xFF);
    out_stream.put((i32 >> 16) & 0xFF);
    out_stream.put((i32 >> 24) & 0xFF);
}


void BmpImage::write_bmp_file_header(std::ofstream& out_stream) const
{
    // TODO: adjust file size and offset for written file
    write_uint16(out_stream, _file_type);
    write_uint32(out_stream, _file_size);
    write_uint16(out_stream, _reserved1);
    write_uint16(out_stream, _reserved2);
    write_uint32(out_stream, _offset_data);
}

void BmpImage::write_bmp_info_header(std::ofstream& out_stream) const
{
    write_uint32(out_stream, _size);
    write_int32(out_stream, _width);
    write_int32(out_stream, _height);
    write_uint16(out_stream, _planes);
    write_uint16(out_stream, _bit_count);
    write_uint32(out_stream, _compression);
    write_uint32(out_stream, _size_image);
    write_int32(out_stream, _x_pixels_per_meter);
    write_int32(out_stream, _y_pixels_per_meter);
    write_uint32(out_stream, _colors_used);
    write_uint32(out_stream, _colors_important);
}

void BmpImage::write_bmp_pixels(std::ofstream& out_stream) const
{
    for(unsigned i = 0; i < std::abs(_height); i++)
    {
        for(unsigned j = 0; j < std::abs(_width); j++)
        {
            out_stream.put(pixels[i][j].blue);
            out_stream.put(pixels[i][j].green);
            out_stream.put(pixels[i][j].red);
            out_stream.put(pixels[i][j].alpha);
        }
    }
}

void BmpImage::write_bmp_file(std::string out_file_path)
{
    std::cout << "Writing output to bmp file " << out_file_path << std::endl;
    std::ofstream out_stream(out_file_path, std::ios::out | std::ios::binary);
    if (!out_stream)
    {
        std::cout << "Error: unable to open file " << out_file_path << " to write!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Writing file header..." << std::endl;
    write_bmp_file_header(out_stream);

    std::cout << "Writing file info..." << std::endl;
    write_bmp_info_header(out_stream);

    std::cout << "Writing pixels" << std::endl;
    write_bmp_pixels(out_stream);

    std::cout << "... done!" << std::endl;
}

void BmpImage::print_pixels()
{
    for(unsigned i = 0; i < std::abs(_height); i++)
    {
        for(unsigned j = 0; j < std::abs(_width); j++)
        {
            std::cout << "(i,j) = (" << i << "," << j << "),    (b,g,r) = " << std::hex
            << (unsigned)pixels[i][j].blue << "," << (unsigned)pixels[i][j].green 
            << "," << (unsigned)pixels[i][j].red << std::endl;
        }
    }
}

void BmpImage::print_file_header()
{
    std::cout << "file type = " << std::hex << _file_type << std::endl;
    std::cout << "file size = " << _file_size << std::endl;
    std::cout << "reserved1 = " << _reserved1 << std::endl;
    std::cout << "reserved2 = " << _reserved1 << std::endl;
    std::cout << "offset_data = " << _offset_data << std::endl;
}

void BmpImage::print_info_header()
{
    std::cout << "size = " << std::hex << _size << std::endl;
    std::cout << "width = " << _width << std::endl;
    std::cout << "height = " << _height << std::endl;
    std::cout << "planes = " << _planes << std::endl;
    std::cout << "bit_count = " << _bit_count << std::endl;
    std::cout << "compression = " << _compression << std::endl;
    std::cout << "size_image = " << _size_image << std::endl;
    std::cout << "x_pixels_per_meter = " << _x_pixels_per_meter << std::endl;
    std::cout << "y_pixels_per_meter = " << _y_pixels_per_meter << std::endl;
    std::cout << "colors_used = " << _colors_used << std::endl;
    std::cout << "colors_important = " << _colors_important << std::endl;
}



void BmpImage::flip_y()
{
    /* Flip image vertically */
    std::cout << "Flipping image vertically" << std::endl;
    std::reverse(pixels.begin(), pixels.end());
}

void BmpImage::flip_x()
{
    /* Flip image horizontally */
    std::cout << "Flipping image horizontally" << std::endl;
    for(auto& row : pixels)
    {
        std::reverse(row.begin(), row.end());
    }
}

void BmpImage::greyscale()
{
    std::cout << "Converting to greyscale" << std::endl;
    for(int i = 0; i <  std::abs(_height); i++)
    {
        for(int j = 0; j <  std::abs(_width); j++)
        {
            uint8_t grey = (pixels[i][j].blue + pixels[i][j].green + pixels[i][j].red) / 3;
            pixels[i][j].blue = grey;
            pixels[i][j].green = grey;
            pixels[i][j].red = grey;
        }
    }
}

void BmpImage::brightness(double factor)
{
    std::cout << "Adjusting brightness using factor = " << factor << std::endl;
    for(int i = 0; i <  std::abs(_height); i++)
    {
        for(int j = 0; j <  std::abs(_width); j++)
        {
            pixels[i][j].blue = std::min(255.0, std::max(0.0, pixels[i][j].blue + (factor * 255)));
            pixels[i][j].green = std::min(255.0, std::max(0.0, pixels[i][j].green + (factor * 255)));
            pixels[i][j].red = std::min(255.0, std::max(0.0, pixels[i][j].red + (factor * 255)));
        }
    }
}

void BmpImage::contrast(double factor)
{
    std::cout << "Adjusting contrast using factor = " << factor << std::endl;
    double contrast_factor = 1.01 * (1.0 - factor) / (1.01 - factor);
    for(int i = 0; i <  std::abs(_height); i++)
    {
        for(int j = 0; j <  std::abs(_width); j++)
        {
            pixels[i][j].blue = std::min(255.0, std::max(0.0, (contrast_factor * (pixels[i][j].blue - 128)) + 128));
            pixels[i][j].green = std::min(255.0, std::max(0.0, (contrast_factor * (pixels[i][j].green - 128)) + 128));
            pixels[i][j].red = std::min(255.0, std::max(0.0, (contrast_factor * (pixels[i][j].red - 128)) + 128));
        }
    }
}

void BmpImage::do_operation(const std::string name)
{
    if(name.compare("flipX") == 0)
    {
        flip_x();
    }
    else if(name.compare("flipY") == 0)
    {
        flip_y();
    }
    else if(name.compare("greyscale") == 0)
    {
        greyscale();
    }
    else
    {
        std::cout << "Error, unrecognised argument" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void BmpImage::do_operation(const std::string name, const double factor)
{
    if(name.compare("brightness") == 0)
    {
        brightness(factor);
    }
    else if(name.compare("contrast") == 0)
    {
        contrast(factor);
    }
    else
    {
        std::cout << "Error, unrecognised argument" << std::endl;
        exit(EXIT_FAILURE);
    }
}