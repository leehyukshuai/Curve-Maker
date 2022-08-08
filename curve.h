#ifndef _CURVE_H_
#define _CURVE_H_

#include <string>
#include <bitset>
#include <cmath>
#include <list>

#define INF INT_MIN
#define SIZE 1080

class Point
{
public:
    Point();
    Point(int _x, int _y);
    int x;
    int y;
};

class Color
{
public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t reserved;
    Color();
    Color(std::string colorName);
    int setColor(std::string colorName);
};

class Node
{
public:
    Node();
    Node(int len, double anv);
    int length;
    double angular_velocity;
};

class Machine
{
private:
    std::list<Node> nodes;
public:
    Machine();
    Machine(std::string scriptPath);
    void initialize(std::string scriptPath);
    Point get_position(double t);
};

class Painter
{
private:
    std::bitset<SIZE> canvas[SIZE];
    Point prev;
    Color penColor;
    Color bgColor;
public:
    Painter();
    void setPenColor(Color color);
    void setBgColor(Color color);
    void run(Machine *machine, double seconds, int rate);
    void dot(Point p);
    void mark(Point p);
    void saveAs(std::string fileName);
};

#endif