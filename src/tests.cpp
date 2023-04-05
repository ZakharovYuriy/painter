#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

#include "html_generator.h"
#include "graphics.h"
#include "tests.h"

using namespace graphics;

namespace tests {

    void GeneralGraphicsTest (std::ostream& out){
        Objects rects;
        auto r1 = Rectangle(Point(1,1),Point(5,5));
        auto r2 = Rectangle(Point(6,6),Point(10,10));

        r1.SetColor(Color(5,10,55));
        r2.SetColor(Color(255,0,22));

        rects.push_back(std::make_shared<Rectangle>(r1));
        rects.push_back(std::make_shared<Rectangle>(r2));

        //создаем лист для рисования HTMLCanvas
        HTMLCanvas list(out);
        //list.ReSize(Point(10,10));
        SimplePrinter table_printer(list); 
        DrawPicture(rects,table_printer);
        table_printer.Print();
    }

    void ParsingRectanglesFromFile(std::ostream& out){
        auto path = std::filesystem::canonical("./../tests/multyple");//two_squares
        out <<" path is->"<< path;
        std::ifstream input_file(path);

        if(input_file){
            //создаем лист для рисования HTMLCanvas
            graphics::HTMLCanvas list(out);
            //list.ReSize(graphics::Point(10,10));
            graphics::SimplePrinter table_printer(list);

            DrawPicture (generator::ReadRectangles(input_file),table_printer);

            table_printer.Print();
        }else{
            throw std::runtime_error("Error opening file");
        }
    }

}  // namespace graph