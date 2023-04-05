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
        if (height_ < p.y){
            canvas_.resize(p.y+1);
            for(int i = height_;  i < canvas_.size(); ++ i)
                canvas_[i].resize(width_+1);
            height_ = p.y;
        }
        if (width_ < p.x){
            width_ = p.x;
            for(auto& y : canvas_)
                y.resize(p.x+1);
        }
    }

    bool HTMLCanvas::PixelInArea(Point p){
        return p.x <= width_ && p.y <= height_; 
    }

    void HTMLCanvas::Print(){
        for(int y = 0; y <= height_; ++y){
            output_<<"<tr>"sv;
            for(int x = 0; x <= width_; ++x){
                output_ << "<th style=\"background-color: rgb("sv;
                auto color = GetPixel(Point(x,y));
                output_ << color.r << " "sv << color.g << " "sv << color.b;
                output_ <<")\"></th>\n"sv;
            }
            output_<<"</tr>\n"sv;
        }
    }

    void SimplePrinter::MoveTo(Point p){
        temp_point_ = p;
    }

    void SimplePrinter::LineTo(Point p){
        canvas_.ReSize(MaxFieldSize(p,temp_point_));
        if(p.x == temp_point_.x){
            int first = std::min(temp_point_.y, p.y);
            int last = std::max(temp_point_.y, p.y);
            for(int y = first; y <= last; ++y){
                canvas_.SetPixel(Point(p.x,y),color_);
            }
        }else if(p.y == temp_point_.y){
            int first = std::min(temp_point_.x, p.x);
            int last = std::max(temp_point_.x, p.x);
            for(int x = first; x <= last; ++x){
                    canvas_.SetPixel(Point(x,p.y),color_);
            }
        }else{
            int first_y = std::min(temp_point_.y, p.y);
            int last_y = std::max(temp_point_.y, p.y);
            for(int y = first_y; y <= last_y; ++y){
                canvas_.SetPixel(Point(CountX(y,temp_point_,p),y),color_);
            }
            int first_x = std::min(temp_point_.x, p.x);
            int last_x = std::max(temp_point_.x, p.x);
            for(int x = first_x; x <= last_x; ++x){
                canvas_.SetPixel(Point(x,CountY(x,temp_point_,p)),color_);
            }
        }
        temp_point_ = p;
    }

    Point SimplePrinter::MaxFieldSize(Point p1, Point p2){
        return Point(std::max(p1.x,p2.x),std::max(p1.y,p2.y));
    }

    void SimplePrinter::SetColor(Color color){
        color_ = color;
    }
    //изменяет размер полотна при указании точки вне поля
    void SimplePrinter::CorrectCanvasSize(Point p){
        if(canvas_.GetSize().x < p.x || canvas_.GetSize().y < p.y){
            canvas_.ReSize(p);
        }
    }

    // Выводит изображение, построенное в памяти, на печать
    void SimplePrinter::Print(){
        canvas_.Print();
    }

    int SimplePrinter::CountX(int y, Point first, Point last){
        return static_cast<int>(static_cast<double>(y - first.y) * (last.x - first.x) / (last.y - first.y) + first.x);
    }    
    int SimplePrinter::CountY(int x, Point first, Point last){
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