#include "curve.h"
#include "fraction.h"
#include <fstream>
#include <cmath>

#define bWrite(stream, data) stream.write((char *)&data, sizeof(data))

Point::Point() : x(INF), y(INF) {}

Point::Point(int _x, int _y) : x(_x), y(_y) {}

Color::Color() { setColor("black"); }

Color::Color(std::string colorName) { setColor(colorName); }

int Color::setColor(std::string colorName)
{
    reserved = 0x00;
    if (colorName == "white") {
        red = 0xff;
        green = 0xff;
        blue = 0xff;
    } else if (colorName == "black") {
        red = 0x00;
        green = 0x00;
        blue = 0x00;
    } else if (colorName == "red") {
        red = 0xff;
        green = 0x00;
        blue = 0x00;
    } else if (colorName == "green") {
        red = 0x00;
        green = 0xff;
        blue = 0x00;
    } else if (colorName == "blue") {
        red = 0x00;
        green = 0x00;
        blue = 0xff;
    } else if (colorName == "grey") {
        red = 0x10;
        green = 0x10;
        blue = 0x10;
    } else {
        return false;
    }
    return true;
}

Node::Node() : length(INF), angular_velocity(INF) {}

Node::Node(int len, double anv) : length(len), angular_velocity(anv) {}

Machine::Machine() {}

Machine::Machine(std::string scriptPath) { initialize(scriptPath); }

void Machine::initialize(std::string scriptPath)
{
    std::ifstream stream;
    stream.open(scriptPath);

    int len; // Pixels
    Fraction rps; // Revolutions Per Second

    while (!stream.eof())
    {
        stream >> len >> rps;
        double anv = M_PI * 2 * rps.value();
        nodes.push_back(Node(len, anv));
    }

    stream.close();
}

Point Machine::get_position(double t)
{
    double x = 0, y = 0;
    double rotation = 0;
    for (Node n : nodes)
    {
        rotation += n.angular_velocity * t;
        x += n.length * std::cos(rotation);
        y += n.length * std::sin(rotation);
    }
    return Point(x, y);
}

Painter::Painter()
{
    prev = Point(INF, INF);
    penColor = Color("black");
    bgColor = Color("white");
}

void Painter::setPenColor(Color color)
{
    penColor = color;
}

void Painter::setBgColor(Color color)
{
    bgColor = color;
}

void Painter::run(Machine * machine, double seconds, int rate)
{
    double unit = 1.0 / rate;
    for (double t = 0; t < seconds + 0.0001; t += unit)
        mark(machine->get_position(t));
}

void Painter::dot(Point p)
{
    int x = p.x + SIZE / 2;
    int y = SIZE / 2 - p.y;
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE)
        canvas[y][x] = 1;
}

void Painter::mark(Point p)
{
    if (prev.x == INF)
        dot(p);
    else
    {
        // link dots to form a line
        int dx = p.x - prev.x;
        int dy = p.y - prev.y;
        int step = std::max(std::abs(dx), std::abs(dy));
        double ux = (double)dx / step;
        double uy = (double)dy / step;
        for (int i = 1; i <= step; ++i)
        {
            int x = prev.x + ux * i;
            int y = prev.y + uy * i;
            dot(Point(x, y));
        }
    }
    prev = p;
}

void Painter::saveAs(std::string fileName)
{
    std::ofstream stream(fileName, std::ios::binary);

    // file header
    const char *bfType = "BM";
    uint32_t bfSize;
    uint32_t bfReserved = 0x00;
    uint32_t bfOffBits = 0x3E;

    // information header
    uint32_t biSize = 0x28;
    uint32_t biWidth = SIZE;
    uint32_t biHeight = SIZE;
    uint16_t biPlanes = 0x01;
    uint16_t biBitCount = 0x01;
    uint32_t biCompression = 0x00;
    int widthBytes = (biWidth * biBitCount + 31) / 32 * 4;
    uint32_t biSizeImage = biHeight * widthBytes;
    bfSize = biSizeImage + bfOffBits;
    uint32_t biXPelsPerMeter = 0x00;
    uint32_t biYPelsPerMeter = 0x00;
    uint32_t biClrUsed = 0x00;
    uint32_t biClrImportant = 0x00;

    stream << bfType;
    bWrite(stream, bfSize);
    bWrite(stream, bfReserved);
    bWrite(stream, bfOffBits);
    bWrite(stream, biSize);
    bWrite(stream, biWidth);
    bWrite(stream, biHeight);
    bWrite(stream, biPlanes);
    bWrite(stream, biBitCount);
    bWrite(stream, biCompression);
    bWrite(stream, biSizeImage);
    bWrite(stream, biXPelsPerMeter);
    bWrite(stream, biYPelsPerMeter);
    bWrite(stream, biClrUsed);
    bWrite(stream, biClrImportant);

    // color table
    bWrite(stream, bgColor.blue);
    bWrite(stream, bgColor.green);
    bWrite(stream, bgColor.red);
    bWrite(stream, bgColor.reserved);
    bWrite(stream, penColor.blue);
    bWrite(stream, penColor.green);
    bWrite(stream, penColor.red);
    bWrite(stream, penColor.reserved);
    
    // bits data
    for (int i = 0; i < biHeight; ++i)
    {
        for (int j = 0; j < widthBytes; ++j)
        {
            uint8_t byte = 0x00;
            for (int k = 0; k < 8; ++k)
                if (8 * j + k < biWidth && canvas[i][8 * j + k])
                    byte |= (1 << (7 - k));
            bWrite(stream, byte);
        }
    }

    stream.close();
}