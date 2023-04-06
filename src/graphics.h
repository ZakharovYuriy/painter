#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <random>

namespace graphics {
    
    struct Point {
        Point() = default;
        Point(int x, int y)
            : x(x)
            , y(y) {
        }
        int x = 0;
        int y = 0;
    };

    struct Color {
        Color() = default;
        Color(int R, int G, int B)
            : r(R),
            g(G),
            b(B){
        }
        int r = 255;
        int g = 255;
        int b = 255;
    };

    Color RundomColor ();

    // Позволяет хранить и изменять изображение

    class ICanvas {
    public:
        virtual Color GetPixel(Point p) = 0;
        virtual void SetPixel(Point p, Color color) = 0;
        virtual Point GetSize() = 0;
        virtual void ReSize(Point p) = 0;
        virtual void Print() = 0;
    };

    class HTMLCanvas final : public ICanvas {
    public:
        HTMLCanvas (std::ostream& out):output_(out){
        };
        Color GetPixel(Point p) override;
        void SetPixel(Point p, Color color) override;
        Point GetSize() override;
        void ReSize(Point p) override;
        void Print() override;
    private:
        std::ostream& output_;
        std::vector<std::vector<Color>> canvas_;
        int width_ = -1;
        int height_ = -1;

        bool PixelInArea(Point p);
    };

    // Интерфейс Graphics предоставляет методы для рисования графических примитивов
    class IGraphics {
    public:
        virtual void MoveTo(Point p) = 0;
        virtual void LineTo(Point p) = 0;
        virtual void SetColor(Color color) = 0;
        // Прочие методы рисования графических примитивов
    };

    // Позволяет выводить изображение
    // В данной реализации принтера размер поля и ячек вычисляется
    // автоматически таким образм - чтобы вместить все элементы
    class SimplePrinter : public IGraphics {
    public:
        SimplePrinter(ICanvas& canvas)
            :canvas_(canvas){
        }
        // Реализация методов Graphics. Выполняет построение изображения в памяти компьютера
        void MoveTo(Point p) override;
        void LineTo(Point p) override;

        void SetColor(Color color);
        // Выводит изображение, построенное в памяти, на печать
        void Print();
    private:
        /* Данные, необходимые для хранения изображения в памяти и вывода его на печать */  
        ICanvas& canvas_;
        Color color_;  
        Point temp_point_;  

        int CountX(int y, Point first, Point last);
        int CountY(int x, Point first, Point last);
        //определение максимального размера поля
        Point MaxFieldSize(Point p1,Point p2);
    }; 

    /*
     * Интерфейс Drawable задаёт объекты, которые можно нарисовать с помощью Graphics
     */
    class IDrawable {
    public:
        virtual void Draw(IGraphics& g) const = 0;
        virtual ~IDrawable() = default;
    };

    // Класс Shape наследуется от Drawable, но не реализует метод Draw.
    // Это должны будут сделать подклассы Shape
    class Shape : public IDrawable {
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

        void Draw(IGraphics& g) const override;
    private:
        Point left_top_;
        int width_;
        int height_;
    };


    using Objects = std::vector<std::shared_ptr<graphics::IDrawable>>;
    
    void DrawElement(const IDrawable* element, IGraphics& g);

    void DrawPicture(Objects picture, IGraphics& g);

}  // namespace graph