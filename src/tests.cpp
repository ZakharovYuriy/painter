#include <iostream>
#include <vector>

#include "graphics.h"
#include "tests.h"

using namespace graph;

namespace tests {

    void GeneralGraphicsTest (std::ostream& out){
        std::vector<const Drawable*> rects;
        auto r1 = Rectangle(Point(1,1),Point(5,5));
        auto r2 = Rectangle(Point(6,6),Point(10,10));

        r1.SetColor(Color(5,10,55));
        r2.SetColor(Color(255,0,22));

        rects.push_back(&r1);
        rects.push_back(&r2);

        //создаем лист для рисования HTMLCanvas
        HTMLCanvas list;
        list.ReSize(Point(10,10));
        HTMLPrinterTable table(list); 
        DrawPicture(rects,table);

        table.Print(out);
    }

}  // namespace graph