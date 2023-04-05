#include <memory>
#include <vector>
#include <iostream>

#include "html_generator.h"
#include "graphics.h"
#include "html.h"
#include "tests.h"

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
}