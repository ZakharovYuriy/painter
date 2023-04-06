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
        // создаем итоговый документ
        // creating the final document
        html::Document doc;
        // добавляем в Header Название страницы
        // adding the Page name to the Header
        auto title_el = std::make_shared<html::ContainerElement>("title"s);
        title_el->addElement(std::make_shared<html::Text>("Graphic Table"s));
        doc.addHeaderElement(title_el);

        // добавляем в Header форматирование таблицы
        // adding table formatting to Header
        auto style_el = std::make_shared<html::ContainerElement>("style"s);
        style_el->addElement(std::make_shared<html::Text>(
            "html,body {height: 100%; margin: 0; padding: 0;}\n"s + 
            "table {width: 100%; height: 100%;}"s
        ));
        doc.addHeaderElement(style_el);

        // создаем лист для рисования HTMLCanvas
        // creating a sheet for drawing HTML Canvas
        std::ostringstream str;
        graphics::HTMLCanvas list(str);
        
        // рисуем обьекты в таблицу
        // draw objects in the table
        graphics::SimplePrinter table_printer(list);
        DrawPicture (objects,table_printer);      
        table_printer.Print();

        // добавляем в Body таблицу
        // adding a table to the Body
        auto table_el = std::make_shared<html::ContainerElement>("table"s);
        table_el->addElement(std::make_shared<html::Text>(str.str()));
        doc.addBodyElement(table_el);
        // генерируем текстовое представление HTML документа
        // generating a text representation of an HTML document
        return doc.Generate();
    }
} // namespace generator