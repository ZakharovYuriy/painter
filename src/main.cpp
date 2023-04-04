#include <iostream>
#include <vector>
#include "graphics.h"

int main() {
using namespace graph;

    std::vector<const Drawable*> rects;
    auto r1 = Rectangle(graph::Point(1,1),Point(5,5));
    auto r2 = Rectangle(graph::Point(6,6),Point(10,10));

    rects.push_back(&r1);
    rects.push_back(&r2);

    //создаем лист для рисования HTMLCanvas
    HTMLCanvas list;
    list.ReSize(Point(20,20));
    HTMLPrinterTable table(list); 
    DrawPicture(rects,table);

    std::cout<<"hello world"<<std::endl;

    return 0;
}
