#include <memory>
#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "html_generator.h"
#include "graphics.h"
#include "html.h"
#include "tests.h"

using namespace std::literals;

namespace generator{
    graphics::Objects ReadRectangles(std::istream& input){
        using namespace graphics;
        graphics::Objects result;
        int x1,y1,x2,y2;
        while(input>>x1>>y1>>x2>>y2){
            auto r1 = std::make_shared<Rectangle>(Point(x1,y1),Point(x2,y2));
            r1->SetColor(RundomColor());
            result.push_back(r1);
        }

        return move(result);
    }

    std::string CreateHTMLWithTable(graphics::Objects objects){
        html::Document doc;
        auto title_el = std::make_shared<html::ContainerElement>("title"s);
        title_el->addElement(std::make_shared<html::Text>("Graphic Table"s));
        doc.addHeaderElement(title_el);

        //создаем лист для рисования HTMLCanvas
        graphics::HTMLCanvas list;
        list.ReSize(graphics::Point(10,10));
        graphics::HTMLPrinterTable table(list);
        DrawPicture (objects,table);

        std::ostringstream str;
        table.Print(str);

        auto table_el = std::make_shared<html::ContainerElement>("table"s);
        table_el->addElement(std::make_shared<html::Text>(str.str()));
        doc.addBodyElement(table_el);
        return doc.Generate();
    }
}