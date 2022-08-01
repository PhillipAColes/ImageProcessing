#include "bmp.h"

BmpImage::BmpImage(std::string in_file_path): in_file_path(in_file_path)
{
    read_bmp_file();
}

void BmpImage::set_file_type(uint16_t file_type)
{
    _file_type = file_type;
}

void BmpImage::set_file_size(uint16_t file_size)
{
    _file_size = file_size;
}

void BmpImage::set_offset_data(uint32_t offset_data)
{
    _offset_data = offset_data;
}

void BmpImage::set_size(uint32_t size)
{
    _size = size;
}

void BmpImage::set_width(int32_t width)
{
    _width = width;
}

void BmpImage::set_height(int32_t height)
{
    _height = height;
}

void BmpImage::set_planes(uint16_t planes)
{
    if(planes != 1)
    {
        // TODO: throw exception
        std::cout << "error" << std::endl;
    }
    _planes = planes;
}

void BmpImage::set_bit_count(uint16_t bit_count)
{
    _bit_count = bit_count;
}

void BmpImage::set_compression(uint32_t compression)
{
    if(compression != 0)
    {
        // TODO: throw exception
        std::cout << "error" << std::endl;
    }
    _compression = compression;
}

void BmpImage::set_size_image(uint32_t size_image)
{
    _size_image = size_image;
}

void BmpImage::set_x_pixels_per_meter(uint32_t x_pixels_per_meter)
{
    _x_pixels_per_meter = x_pixels_per_meter;
}

void BmpImage::set_y_pixels_per_meter(uint32_t y_pixels_per_meter)
{
    _y_pixels_per_meter = y_pixels_per_meter;
}

void BmpImage::set_colors_used(uint32_t colors_used)
{
    // TODO: use 0 for 32-bit bitmap
    _colors_used = colors_used;
}

void BmpImage::set_colors_important(uint32_t colors_important)
{
    // TODO: use 0 for 32-bit bitmap
    _colors_important = colors_important;
}


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



void BmpImage::read_bmp_file_header(std::ifstream& in_stream)
{
    uint16_t file_type = read_uint16(in_stream); // File type always BM which is 0x4D42
    std::cout << "file type = " << std::hex << file_type << std::endl;
    set_file_type(file_type);

    uint32_t file_size = read_uint32(in_stream); // Size of the entire file (in bytes)
    std::cout << "file size = " << std::dec << file_size << std::endl;
    set_file_size(file_size);

    uint16_t reserved1 = read_uint16(in_stream); // Reserved, always 0
    std::cout << "reserved1 = " << std::dec << reserved1 << std::endl;
    uint16_t reserved2 = read_uint16(in_stream); // Reserved, always 0
    std::cout << "reserved2 = " << std::dec << reserved2 << std::endl;

    uint32_t offset_data = read_uint32(in_stream); // Start position of pixel data (bytes offset from start of file)
    std::cout << "offset_data = " << std::dec << offset_data << std::endl;
    set_offset_data(offset_data);
}

void BmpImage::read_bmp_info_header(std::ifstream& in_stream)
{
    uint32_t size = read_uint32(in_stream); // Size of BMPInfoHeader (in bytes)
    std::cout << "size = " << size << std::endl;
    set_size(size);

    int32_t width = read_int32(in_stream); // width of bitmap in pixels
    std::cout << "width = " << width << std::endl;
    set_width(width);

    int32_t height = read_int32(in_stream); // height of bitmap in pixels
    // (if positive, bottom-up, with origin in lower left corner)
    // (if negative, top-down, with origin in upper left corner)
    std::cout << "height = " << height << std::endl;
    set_height(height);

    uint16_t planes = read_uint16(in_stream); // No. of planes for the target device, this is always 1
    std::cout << "planes = " << planes << std::endl;
    set_planes(planes);

    uint16_t bit_count = read_uint16(in_stream); // No. of bits per pixel
    std::cout << "bit_count = " << bit_count << std::endl;
    set_bit_count(bit_count);

    uint32_t compression = read_uint32(in_stream); // 0 for uncompressed images. Only handle this case.
    std::cout << "compression = " << compression << std::endl;
    set_compression(compression);

    uint32_t size_image = read_uint32(in_stream); // Size of pixel data in bytes
    std::cout << "size_image = " << size_image << std::endl;
    set_size_image(size_image);

    int32_t x_pixels_per_meter = read_int32(in_stream); // Typically 2834
    std::cout << "x_pixels_per_meter = " << x_pixels_per_meter << std::endl;
    set_x_pixels_per_meter(x_pixels_per_meter);

    int32_t y_pixels_per_meter = read_int32(in_stream); // Typically 2834
    std::cout << "y_pixels_per_meter = " << y_pixels_per_meter << std::endl;
    set_y_pixels_per_meter(y_pixels_per_meter);

    uint32_t colors_used = read_uint32(in_stream); // No. color indexes used. Use 0 for 32-bit bitmaps
    std::cout << "colors_used = " << colors_used << std::endl;
    set_colors_used(colors_used);

    uint32_t colors_important = read_uint32(in_stream); // No. of colors used. Use 0 for 32-bit bitmaps
    std::cout << "colors_important = " << colors_important << std::endl;
    set_colors_important(colors_important);
}

void BmpImage::read_bmp_pixels(std::ifstream& in_stream)
{
    pixels.resize(_width, std::vector<Pixel>(_height, Pixel(0,0,0,0)));
    // TODO: point stream to part of file where image starts
    for(int i = 0; i < (unsigned)_width; i++)
    {
        for(int j = 0; j < (unsigned)_height; j++)
        {
            pixels[i][j].blue = in_stream.get();
            pixels[i][j].green = in_stream.get();
            pixels[i][j].red = in_stream.get();
            pixels[i][j].alpha = in_stream.get();
            //std::cout << i << "," << j << std::endl;
        }
    }
}

void BmpImage::read_bmp_file()
{
    // try
    std::ifstream in_stream(in_file_path, std::ios::in | std::ios::binary);
    if (!in_stream)
    {
        std::cout << "Error!" << std::endl;
    }
    read_bmp_file_header(in_stream);
    read_bmp_info_header(in_stream);
    read_bmp_pixels(in_stream);
    std::cout << "done" << std::endl;
    // catch
    in_stream.close();
}


void write_uint16(std::ofstream& out_stream, uint16_t ui16)
{
    std::cout << "uint16_t = " << ui16 << std::endl;
    uint8_t c0 = ui16 & 0xFF;
    uint8_t c1 = (ui16 >> 8) & 0xFF;
    out_stream.put(ui16 & 0xFF);
    out_stream.put((ui16 >> 8) & 0xFF);
    std::cout << "written uint16" << std::endl;
    /*
    char buff[2];
    buff[0] = ui16 && 0xFF; // mask ui32 with && 0000000011111111
    buff[1] = (ui16 >> 8) && 0xFF;
    out_stream.write(buff, 2);
    */
}

void write_uint32(std::ofstream& out_stream, uint32_t ui32)
{
    uint8_t c0 = ui32 & 0xFF; // mask ui32 with && 0000000011111111
    uint8_t c1 = (ui32 >> 8) & 0xFF;
    uint8_t c2 = (ui32 >> 16) & 0xFF;
    uint8_t c3 = (ui32 >> 24) & 0xFF;
    out_stream.put(ui32 & 0xFF);
    out_stream.put((ui32 >> 8) & 0xFF);
    out_stream.put((ui32 >> 16) & 0xFF);
    out_stream.put((ui32 >> 24) & 0xFF);
    std::cout << "written uint32, bad =  " << out_stream.bad() << std::endl;
    std::cout << "written uint32, good =  " << out_stream.good() << std::endl;
    /*
    char buff[4];
    buff[0] = ui32 && 0xFF; // mask ui32 with && 0000000011111111
    buff[1] = (ui32 >> 8) && 0xFF;
    buff[2] = (ui32 >> 16) && 0xFF;
    buff[3] = (ui32 >> 24) && 0xFF;
    out_stream.write(buff, 4);
    */
}

void write_int32(std::ofstream& out_stream, int32_t i32)
{
    uint8_t c0 = i32 && 0xFF;
    uint8_t c1 = (i32 >> 8) & 0xFF;
    uint8_t c2 = (i32 >> 16) & 0xFF;
    uint8_t c3 = (i32 >> 24) & 0xFF;
    out_stream.put(i32 & 0xFF);
    out_stream.put((i32 >> 8) & 0xFF);
    out_stream.put((i32 >> 16) & 0xFF);
    out_stream.put((i32 >> 24) & 0xFF);
    std::cout << "written int32" << std::endl;
    /*
    char buff[4];
    buff[0] = i32 && 0xFF; // mask ui32 with && 0000000011111111
    buff[1] = (i32 >> 8) && 0xFF;
    buff[2] = (i32 >> 16) && 0xFF;
    buff[3] = (i32 >> 24) && 0xFF;
    out_stream.write(buff, 4);
    */
}


void BmpImage::write_bmp_file_header(std::ofstream& out_stream) const
{
    std::cout << "_file_type = " << _file_type << std::endl;
    write_uint16(out_stream, _file_type);
    write_uint32(out_stream, _file_size);
    write_uint16(out_stream, 0);
    write_uint16(out_stream, 0);
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
    for(int i = 0; i < (unsigned)_width; i++)
    {
        for(int j = 0; j < (unsigned)_height; j++)
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
    std::cout << "writing to " << out_file_path << std::endl;
    std::ofstream out_stream(out_file_path, std::ios::out | std::ios::binary);
    if (!out_stream)
    {
        std::cout << "Error!" << std::endl;
    }
    write_bmp_file_header(out_stream);
    write_bmp_info_header(out_stream);
    write_bmp_pixels(out_stream);
}