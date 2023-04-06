#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>

#include "graphics.h"

//Функции позволяющие создать HTML файл
//Functions that allow you to create an HTML file
namespace generator{
    // считывает данные из переданного потока и создает массив прямоугольников
    // reads data from the transmitted stream and creates an array of rectangles
    graphics::Objects ReadRectangles(std::istream& input);

    // Создает итоговый HTML документ и печатает таблицу из переданных обьектов
    // Creates a final HTML document and prints a table from the passed objects
    std::string CreateHTMLWithTable(graphics::Objects table);

} // namespace generator
