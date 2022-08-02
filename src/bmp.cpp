#include "bmp.h"

BmpImage::BmpImage(std::string in_file_path): in_file_path(in_file_path)
{
    read_bmp_file();
}

void BmpImage::set_file_type(uint16_t file_type)
{
    _file_type = file_type;
}

void BmpImage::set_file_size(uint32_t file_size)
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

void BmpImage::set_x_pixels_per_meter(int32_t x_pixels_per_meter)
{
    _x_pixels_per_meter = x_pixels_per_meter;
}

void BmpImage::set_y_pixels_per_meter(int32_t y_pixels_per_meter)
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
    std::cout << "file size = " << std::hex << file_size << std::endl;
    set_file_size(file_size);

    uint16_t reserved1 = read_uint16(in_stream); // Reserved, always 0
    std::cout << "reserved1 = " << std::hex << reserved1 << std::endl;
    uint16_t reserved2 = read_uint16(in_stream); // Reserved, always 0
    std::cout << "reserved2 = " << std::hex << reserved2 << std::endl;

    uint32_t offset_data = read_uint32(in_stream); // Start position of pixel data (bytes offset from start of file)
    std::cout << "offset_data = " << std::hex << offset_data << std::endl;
    set_offset_data(offset_data);
}

void BmpImage::read_bmp_info_header(std::ifstream& in_stream)
{
    uint32_t size = read_uint32(in_stream); // Size of BMPInfoHeader (in bytes)
    std::cout << "size = " << std::hex << size << std::endl;
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

/*
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
        }
        //char temp;
        //in_stream.get(temp);
    }
}
*/

void BmpImage::read_bmp_pixels(std::ifstream& in_stream)
{
    pixels.resize(_height, std::vector<Pixel>(_width, Pixel(0,0,0,0)));
    // TODO: point stream to part of file where image starts
    for(int i = 0; i < (unsigned)_height; i++)
    {
        for(int j = 0; j < (unsigned)_width; j++)
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
    // try
    std::ifstream in_stream(in_file_path, std::ios::in | std::ios::binary);
    if (!in_stream)
    {
        std::cout << "Error!" << std::endl;
    }
    read_bmp_file_header(in_stream);
    read_bmp_info_header(in_stream);
    read_bmp_pixels(in_stream);
    std::cout << "read bmp file." << std::endl;
    std::cout << "sizeof(pixels) = " << pixels.size() << ", sizeof(pixels[i]) = " << pixels[0].size() << std::endl;
    // catch
    _offset_data = sizeof(_file_type) + sizeof(_file_size) + sizeof(_reserved1) + sizeof(_reserved2) +
        sizeof(_offset_data) + sizeof(_size) + sizeof(_width) + sizeof(_height) + sizeof(_planes) +
        sizeof(_bit_count) + sizeof(_compression) + sizeof(_size_image) + sizeof(_x_pixels_per_meter) +
        sizeof(_y_pixels_per_meter) + sizeof(_colors_used) + sizeof(_colors_important);
    std::cout << "new _offset_data = " << _offset_data << std::endl;

    in_stream.close();
}


void write_uint16(std::ofstream& out_stream, uint16_t ui16)
{
    uint8_t c0 = ui16 & 0xFF;
    uint8_t c1 = (ui16 >> 8) & 0xFF;
    out_stream.put(ui16 & 0xFF);
    out_stream.put((ui16 >> 8) & 0xFF);
}

void write_uint32(std::ofstream& out_stream, uint32_t ui32)
{
    uint8_t c0 = ui32 & 0xFF; // mask ui32 with & 0000000011111111
    uint8_t c1 = (ui32 >> 8) & 0xFF;
    uint8_t c2 = (ui32 >> 16) & 0xFF;
    uint8_t c3 = (ui32 >> 24) & 0xFF;
    out_stream.put(ui32 & 0xFF);
    out_stream.put((ui32 >> 8) & 0xFF);
    out_stream.put((ui32 >> 16) & 0xFF);
    out_stream.put((ui32 >> 24) & 0xFF);
}

void write_int32(std::ofstream& out_stream, int32_t i32)
{
    // TODO: diff between writing uint and int
    uint8_t c0 = i32 & 0xFF;
    uint8_t c1 = (i32 >> 8) & 0xFF;
    uint8_t c2 = (i32 >> 16) & 0xFF;
    uint8_t c3 = (i32 >> 24) & 0xFF;
    out_stream.put(i32 & 0xFF);
    out_stream.put((i32 >> 8) & 0xFF);
    out_stream.put((i32 >> 16) & 0xFF);
    out_stream.put((i32 >> 24) & 0xFF);
}


void BmpImage::write_bmp_file_header(std::ofstream& out_stream) const
{
    std::cout << "_file_type = " << std::hex << _file_type << std::endl;
    write_uint16(out_stream, _file_type);
    std::cout << "_file_size = " << std::hex << _file_size << std::endl;
    write_uint32(out_stream, _file_size);
    write_uint16(out_stream, 0);
    write_uint16(out_stream, 0);
    write_uint32(out_stream, _offset_data);
}

void BmpImage::write_bmp_info_header(std::ofstream& out_stream) const
{
    write_uint32(out_stream, _size);
    std::cout << "_width = " << _width << std::endl;
    write_int32(out_stream, _width);
    std::cout << "_height = " << _height << std::endl;
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

/*
void BmpImage::write_bmp_pixels(std::ofstream& out_stream) const
{
    std::cout << "writing bmp_pixels" << std::endl;
    //for(int i = 0; i < (unsigned)_width; i++)
    for(int i = 0; i < std::abs(_width); i++)
    {
        //for(int j = 0; j < (unsigned)_height; j++)
        for(int j = 0; j < std::abs(_height); j++)
        {
            out_stream.put(pixels[i][j].blue);
            out_stream.put(pixels[i][j].green);
            out_stream.put(pixels[i][j].red);
            out_stream.put(pixels[i][j].alpha);
        }
    }
    std::cout << "... done writing bmp_pixels" << std::endl;
}
*/

void BmpImage::write_bmp_pixels(std::ofstream& out_stream) const
{
    std::cout << "writing bmp_pixels" << std::endl;
    //for(int i = 0; i < (unsigned)_width; i++)
    for(int i = 0; i < std::abs(_height); i++)
    {
        //for(int j = 0; j < (unsigned)_height; j++)
        for(int j = 0; j < std::abs(_width); j++)
        {
            out_stream.put(pixels[i][j].blue);
            out_stream.put(pixels[i][j].green);
            out_stream.put(pixels[i][j].red);
            out_stream.put(pixels[i][j].alpha);
        }
    }
    std::cout << "... done writing bmp_pixels" << std::endl;
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

/*
void BmpImage::write_small_bmp_pixels(std::ofstream& out_stream) const
{
    std::cout << "writing bmp_pixels" << std::endl;
    //for(int i = 0; i < (unsigned)_width; i++)
    for(int i = 0; i < std::abs(_width); i++)
    {
        //for(int j = 0; j < (unsigned)_height; j++)
        for(int j = 0; j < std::abs(_height); j++)
        {
            out_stream.put(pixels[i][j].blue);
            out_stream.put(pixels[i][j].green);
            out_stream.put(pixels[i][j].red);
            out_stream.put(pixels[i][j].alpha);
        }
    }
    std::cout << "... done writing bmp_pixels" << std::endl;
}
*/

void BmpImage::write_small_bmp_pixels(std::ofstream& out_stream) const
{
    std::cout << "writing bmp_pixels" << std::endl;
    //for(int i = 0; i < (unsigned)_width; i++)
    for(int i = 0; i < std::abs(_height); i++)
    {
        //for(int j = 0; j < (unsigned)_height; j++)
        for(int j = 0; j < std::abs(_width); j++)
        {
            out_stream.put(pixels[i][j].blue);
            out_stream.put(pixels[i][j].green);
            out_stream.put(pixels[i][j].red);
            out_stream.put(pixels[i][j].alpha);
        }
    }
    std::cout << "... done writing bmp_pixels" << std::endl;
}

void BmpImage::write_small_bmp_file(std::string out_file_path)
{
    std::cout << "writing to " << out_file_path << std::endl;
    std::ofstream out_stream(out_file_path, std::ios::out | std::ios::binary);
    if (!out_stream)
    {
        std::cout << "Error!" << std::endl;
    }

    _width = 4; // width of bitmap in pixels
    _height = 3; // height of bitmap in pixels

    //_file_type; // File type always BM which is 0x4D42
    _file_size = 54 + (_width * _height * 4); // Size of the entire file (in bytes)
    //_reserved1; // Reserved, always 0
    //_reserved2; // Reserved, always 0
    write_bmp_file_header(out_stream);

    //uint32_t _size; // Size of BMPInfoHeader (in bytes)
    //_width = 4; // width of bitmap in pixels
    //_height = 3; // height of bitmap in pixels
    // (if positive, bottom-up, with origin in lower left corner)
    // (if negative, top-down, with origin in upper left corner)
    //uint16_t _planes; // No. of planes for the target device, this is always 1
    //uint16_t _bit_count; // No. of bits per pixel
    //uint32_t _compression; // 0 for uncompressed images. Only handle this case.
    _size_image = (_width * _height * 4); // Size of pixel data in bytes
    //int32_t _x_pixels_per_meter; // Typically 2834
    //int32_t _y_pixels_per_meter; // Typically 2834
    //uint32_t _colors_used; // No. color indexes used. Use 0 for 32-bit bitmaps
    //uint32_t _colors_important; // No. of colors used. Use 0 for 32-bit bitmaps
    write_bmp_info_header(out_stream);
    write_small_bmp_pixels(out_stream);
}

void BmpImage::print_pixels()
{
    for(int i = 0; i < std::abs(_height); i++)
    {
        //for(int j = 0; j < (unsigned)_height; j++)
        for(int j = 0; j < std::abs(_width); j++)
        {
            std::cout << "(i,j) = (" << i << "," << j << "),    (b,g,r) = " << std::hex
            << (unsigned)pixels[i][j].blue << "," << (unsigned)pixels[i][j].green 
            << "," << (unsigned)pixels[i][j].red << std::endl;
        }
    }
}

void BmpImage::flip_y()
{
    /* Flip image horizontally */
    std::reverse(pixels.begin(), pixels.end());
    
    /*
    for(int i = 0; i < (unsigned)_width / 2; i++)
    {
        for(int j = 0; j < (unsigned)_height; j++)
        {
            //std::cout << "width = " << _width << ", height = " << _height << ", i,j = " << i << "," << j << std::endl;
            //std::cout << "sizeof(pixels) = " << pixels.size() << ", sizeof(pixels[i]) = " << pixels[0].size() << std::endl; 
            uint8_t red_tmp = pixels[i][j].red;
            //std::cout << "1" << std::endl;
            uint8_t blue_tmp = pixels[i][j].blue;
            //std::cout << "2" << std::endl;
            uint8_t green_tmp = pixels[i][j].green;
            //std::cout << "3" << std::endl;
            uint8_t alpha_tmp = pixels[i][j].alpha;
            //std::cout << "4" << std::endl;
            //std::cout << "_width - i - 1 = " << _width - i - 1 << ", height = " << _height << ", i,j = " << i << "," << j << std::endl;
            pixels[i][j].red = pixels[_width - i - 1][j].red;
            //std::cout << "5" << std::endl;
            pixels[i][j].blue = pixels[_width - i - 1][j].blue;
            //std::cout << "6" << std::endl;
            pixels[i][j].green = pixels[_width - i - 1][j].green;
            //std::cout << "7" << std::endl;
            pixels[i][j].alpha = pixels[_width - i - 1][j].alpha;
            pixels[_width - i - 1][j].red = red_tmp;
            pixels[_width - i - 1][j].blue = blue_tmp;
            pixels[_width - i - 1][j].green = green_tmp;
            pixels[_width - i - 1][j].alpha = alpha_tmp;
            //std::cout << "width = " << _width << ", height = " << _height << ", i,j = " << i << "," << j << std::endl;
            //out_stream.put(pixels[i][j].blue);
            //out_stream.put(pixels[i][j].green);
            //out_stream.put(pixels[i][j].red);
            //out_stream.put(pixels[i][j].alpha);
        }
    }
    */
    
}

/*
void BmpImage::print_pixels()
{
    for(int i = 0; i < std::abs(_width); i++)
    {
        //for(int j = 0; j < (unsigned)_height; j++)
        for(int j = 0; j < std::abs(_height); j++)
        {
            std::cout <<  unsigned(pixels[i][j].blue) << "," << unsigned(pixels[i][j].green) << "," << unsigned(pixels[i][j].red) << "  " << std::endl;        
        }
        std::cout << std::endl;
    }
}
*/

void BmpImage::flip_x()
{
    /* Flip image vertically */
    std::cout << "before flip pixel[0][0] = " << unsigned(pixels[0][0].blue) << "," << unsigned(pixels[0][0].green) << "," << unsigned(pixels[0][0].red) << std::endl;
    std::cout << "before flip pixel[0][_height - 1] = " << unsigned(pixels[0][_height - 1].blue) << "," << unsigned(pixels[0][_height - 1].green) << "," << unsigned(pixels[0][_height - 1].red) << std::endl;
    for(auto& row : pixels)
    {
        std::reverse(row.begin(), row.end());
        //std::cout << "reversed " << x++ << " cols" << std::endl;
    }
    std::cout << "after flip pixel[0][0] = " << unsigned(pixels[0][0].blue) << "," << unsigned(pixels[0][0].green) << "," << unsigned(pixels[0][0].red) << std::endl;
    std::cout << "after flip pixel[0][_height - 1] = " << unsigned(pixels[0][_height - 1].blue) << "," << unsigned(pixels[0][_height - 1].green) << "," << unsigned(pixels[0][_height - 1].red) << std::endl;
}


void BmpImage::greyscale()
{
    for(int i = 0; i < _width; i++)
    {
        for(int j = 0; j < _height; j++)
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
    for(int i = 0; i < _width; i++)
    {
        for(int j = 0; j < _height; j++)
        {
            pixels[i][j].blue = std::min(255.0, std::max(0.0, pixels[i][j].blue + (factor * 255)));
            pixels[i][j].green = std::min(255.0, std::max(0.0, pixels[i][j].green + (factor * 255)));
            pixels[i][j].red = std::min(255.0, std::max(0.0, pixels[i][j].red + (factor * 255)));
        }
    }
}

void BmpImage::contrast(double factor)
{
    double contrast_factor = 1.01 * (1.0 - factor) / (1.01 - factor);
    std::cout << "contrast_factor = " << contrast_factor << std::endl;
    for(int i = 0; i < _width; i++)
    {
        for(int j = 0; j < _height; j++)
        {
            pixels[i][j].blue = std::min(255.0, std::max(0.0, (contrast_factor * (pixels[i][j].blue - 128)) + 128));
            pixels[i][j].green = std::min(255.0, std::max(0.0, (contrast_factor * (pixels[i][j].green - 128)) + 128));
            pixels[i][j].red = std::min(255.0, std::max(0.0, (contrast_factor * (pixels[i][j].red - 128)) + 128));
        }
    }
}