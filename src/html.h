#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <variant>
#include <string>


namespace HTML {

    //Интерфейс элементов HTML документов
    class Element{
    public:
        virtual std::string Generate() const = 0;
    };

    class ContainerElement : public Element{
    public:
        ContainerElement(const std::string& type):type_(type){
        }
        void addAttribute(const std::string& name, const std::string& value);
        void addElement(Element*);
        std::string Generate() const override;
    private:
        std::string type_;
        std::unordered_map<std::string,std::string> attributes_;
        std::vector<Element*> elements_;
    };

    class Text : public Element{
    public:
        void addText(const std::string& text);
        std::string Generate() const override;
    private:
        std::string text_;
    };

    class Document : public Element{
    public:
        void addHeaderElement(Element* title);
        void addBodyElement(Element*);
        std::string Generate() const override;
    private:
        std::vector<Element*>  header_;
        std::vector<Element*>  body_;
    };

}  // namespace graph