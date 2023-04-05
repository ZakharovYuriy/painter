#include <iostream>
#include <string>
#include <vector>

#include "graphics.h"

using namespace std::literals;

namespace graphics {

    Color RundomColor (){
        // Создаем генератор случайных чисел mt19937
        std::mt19937 rng{std::random_device{}()};

        // Создаем распределение для генерации целых чисел от 0 до 255
        std::uniform_int_distribution<int> distribution{0, 255};

        // Генерируем случайные числа
        return Color (distribution(rng),distribution(rng),distribution(rng));
    }

    Color HTMLCanvas::GetPixel(Point p){
        if (PixelInArea(p))
            return canvas_[p.y][p.x];
        else 
            throw std::range_error("outside the field");
    }

    void HTMLCanvas::SetPixel(Point p, Color color){
        if (PixelInArea(p))
            canvas_[p.y][p.x] = color;
        else 
            throw std::range_error("outside the field");
    }

    Point HTMLCanvas::GetSize(){
        return Point(width_,height_);
    }

    void HTMLCanvas::ReSize(Point p){
        if (width_ < p.y){
            canvas_.resize(p.y+1);
            width_ = p.y;
        }
        if (height_ < p.x){
            height_ = p.x;
            for(auto& x : canvas_)
                x.resize(p.x+1);
        }
    }

    bool HTMLCanvas::PixelInArea(Point p){
        return p.x <= width_ && p.y <= height_; 
    }

    void HTMLPrinterTable::MoveTo(Point p){
        temp_point_ = p;
    }

    void HTMLPrinterTable::LineTo(Point p){
        if(p.x == temp_point_.x){
            int first = std::min(temp_point_.y, p.y);
            int last = std::max(temp_point_.y, p.y);
            for(int y = first; y <= last; ++y){
                picture_.SetPixel(Point(p.x,y),color_);
            }
        }else if(p.y == temp_point_.y){
            int first = std::min(temp_point_.x, p.x);
            int last = std::max(temp_point_.x, p.x);
            for(int x = first; x <= last; ++x){
                    picture_.SetPixel(Point(x,p.y),color_);
            }
        }else{
            int first_y = std::min(temp_point_.y, p.y);
            int last_y = std::max(temp_point_.y, p.y);
            for(int y = first_y; y <= last_y; ++y){
                picture_.SetPixel(Point(CountX(y,temp_point_,p),y),color_);
            }
            int first_x = std::min(temp_point_.x, p.x);
            int last_x = std::max(temp_point_.x, p.x);
            for(int x = first_x; x <= last_x; ++x){
                picture_.SetPixel(Point(x,CountY(x,temp_point_,p)),color_);
            }
        }
        temp_point_ = p;
    }

    void HTMLPrinterTable::SetColor(Color color){
        color_ = color;
    }
    //изменяет размер полотна при указании точки вне поля
    void HTMLPrinterTable::CorrectCanvasSize(Point p){
        if(picture_.GetSize().x < p.x || picture_.GetSize().y < p.y){
            picture_.ReSize(p);
        }
    }

    // Выводит изображение, построенное в памяти, на печать
    void HTMLPrinterTable::Print(std::ostream& output){
        auto size = picture_.GetSize();
        output<<"<table style=\"width: 100%\">"sv<<std::endl;
        for(int y = 0; y <= size.y; ++y){
            output<<"<tr>"sv;
            for(int x = 0; x <= size.x; ++x){
                output << "<th style=\"background-color: rgb("sv;
                auto color = picture_.GetPixel(Point(x,y));
                output << color.r << " "sv << color.g << " "sv << color.b;
                output <<")\"></th>\n"sv;
            }
            output<<"</tr>\n"sv;
        }
        output<<"</table>"sv<<std::endl;
    }

    int HTMLPrinterTable::CountX(int y, Point first, Point last){
        return static_cast<int>(static_cast<double>(y - first.y) * (last.x - first.x) / (last.y - first.y) + first.x);
    }    
    int HTMLPrinterTable::CountY(int x, Point first, Point last){
        return static_cast<int>((static_cast<double>(last.y - first.y)/(last.x - first.x)) * (x - first.x) + first.y);
    } 

    void DrawElement(const Drawable* element, Graphics& g) {
        element->Draw(g);
    };

    Color Shape::GetColor() const { return color_; }
    void Shape::SetColor(Color color) { color_ = color; }

    void Rectangle::Draw(Graphics& g) const {
        g.SetColor(GetColor());
        g.MoveTo(left_top_);
        g.LineTo({left_top_.x + width_, left_top_.y});
        g.LineTo({left_top_.x + width_, left_top_.y + height_});
        g.LineTo({left_top_.x, left_top_.y + height_});
        g.LineTo(left_top_);
    }

    void DrawPicture(Objects picture, Graphics& g) {
        for (auto drawable : picture) {
            drawable->Draw(g);
        }
    };
}  // namespace graph