#pragma once

#include <iostream>
#include <vector>

#include "graphics.h"

namespace tests {
    // простой пример ручного вызова большинства функций рисования
    // a simple example of manually calling most drawing functions
    void GeneralGraphicsTest (std::ostream& out);

    // Тестовый вызов построения только наполнения таблицы из примеров из папки tests 
    // Test call for building only the filling of the table from the examples from the tests folder
    void ParsingRectanglesFromFile(std::ostream& out);

}  // namespace tests