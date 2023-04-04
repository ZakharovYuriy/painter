#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace graph {

    struct Point {
        Point() = default;
        Point(double x, double y)
            : x(x)
            , y(y) {
        }
        double x = 0;
        double y = 0;
    };

    struct Color {
        Color() = default;
        Color(int r, int g, int b)
            : r(),
            g(),
            b(){
        }
        int8_t r = 0;
        int8_t g = 0;
        int8_t b = 0;
    };

    // Позволяет хранить и изменять изображение
    class HTMLCanvas final {
    public:
        Color GetPixel(Point p);
        void  SetPixel(Point p, Color color);
        Point GetSize();
        void ReSize(Point p);
    private:
        std::vector<std::vector<Color>> canvas_;
        int width_ = 0;
        int height_ = 0;

        bool PixelInArea(Point p);
    };

    // Интерфейс Graphics предоставляет методы для рисования графических примитивов
    class Graphics {
    public:
        virtual void MoveTo(Point p) = 0;
        virtual void LineTo(Point p) = 0;
        virtual void SetColor(Color color) = 0;
        // Прочие методы рисования графических примитивов
    };

    // Позволяет выводить изображение
    class HTMLPrinterTable : public Graphics {
    public:
        HTMLPrinterTable(HTMLCanvas& picture)
            :picture_(picture){
        }
        // Реализация методов Graphics. Выполняет построение изображения в памяти компьютера
        void MoveTo(Point p) override;
        void LineTo(Point p) override;

        void SetColor(Color color);
        //изменяет размер полотна при указании точки вне поля
        void CorrectCanvasSize(Point p);

        // Выводит изображение, построенное в памяти, на печать
        void Print(std::iostream& output);
    private:
        /* Данные, необходимые для хранения изображения в памяти и вывода его на печать */  
        HTMLCanvas& picture_;
        Color color_;  
        Point temp_point_;  

        int CountX(int y, Point first, Point last);
        int CountY(int x, Point first, Point last);
    }; 

    /*
     * Интерфейс Drawable задаёт объекты, которые можно нарисовать с помощью Graphics
     */
    class Drawable {
    public:
        virtual void Draw(Graphics& g) const = 0;
        virtual ~Drawable() = default;
    };

    // Класс Shape наследуется от Drawable, но не реализует метод Draw.
    // Это должны будут сделать подклассы Shape
    class Shape : public Drawable {
    public:
        Color GetColor() const;
        void SetColor(Color color);
    private:
        Color color_;
    }; 

    class Rectangle final: public Shape {
    public:
        Rectangle(Point left_top, Point right_bottom)
            :left_top_(left_top),
            width_(right_bottom.x - left_top.x),
            height_(right_bottom.y - left_top.y){
        }

        void Draw(Graphics& g) const override;
    private:
        Point left_top_;
        double width_;
        double height_;
    };

    void DrawElement(const Drawable* element, Graphics& g);

    void DrawPicture(const std::vector<const Drawable*>& picture, Graphics& g);

}  // namespace graph