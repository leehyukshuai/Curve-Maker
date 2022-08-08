#include "curve.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

int main(int argc, char const *argv[])
{
    // usage example:
    // curve -i "myScript.txt" -t 2.3 -r 100 -o "myCurve.bmp"
    std::string inputFile = "script.txt";
    std::string outputFile = "untitled.bmp";
    Color penColor("black");
    double seconds = 5;
    int rate = 100;
    for (int i = 1; i < argc; i += 2)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
            case 'i':
                inputFile = argv[i + 1];
                if (!std::ifstream(inputFile)) {
                    std::cerr << inputFile << ": Invalid InputFile." << std::endl;
                    return 1;
                }
                break;
            case 't':
                seconds = atof(argv[i + 1]);
                break;
            case 'r':
                rate = atoi(argv[i + 1]);
                break;
            case 'o':
                outputFile = argv[i + 1];
                break;
            case 'c':
                if (!penColor.setColor(argv[i + 1])) {
                    std::cerr << inputFile << ": Invalid Color Name." << std::endl;
                    return 1;
                }
                break;
            default:
                std::cerr << argv[i] << ": Unknown Parameter." << std::endl;
                return 1;
            }
        }
    }

    Machine machine;
    machine.initialize(inputFile);
    Painter painter;
    painter.setPenColor(penColor);
    painter.run(&machine, seconds, rate);
    painter.saveAs(outputFile);
    return 0;

}