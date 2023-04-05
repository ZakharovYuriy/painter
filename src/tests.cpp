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
        HTMLCanvas list;
        list.ReSize(Point(10,10));
        HTMLPrinterTable table(list); 
        DrawPicture(rects,table);

        table.Print(out);
    }

    void ParsingRectangles(std::ostream& out){

        auto path = std::filesystem::canonical("/home/yuriy/Документы/собеседование/тестовые/painter/tests/two_squares");
        std::ifstream input_file(path);

        if(input_file){
            //создаем лист для рисования HTMLCanvas
            graphics::HTMLCanvas list;
            list.ReSize(graphics::Point(10,10));
            graphics::HTMLPrinterTable table(list);

            DrawPicture (generator::ReadRectangles(input_file),table);

            table.Print(out);
        }else{
            throw std::runtime_error("Error opening file");
        }
    }

}  // namespace graph