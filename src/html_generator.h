#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>

#include "graphics.h"

namespace generator{
    
    graphics::Objects ReadRectangles(std::istream& input);

    std::string CreateHTMLWithTable(graphics::Objects table);

} // namespace generator
