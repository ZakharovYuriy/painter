#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <variant>
#include <string>
#include <memory>

namespace html {

    //Интерфейс элементов HTML документов
    class Element{
    public:
        virtual std::string Generate() const = 0;
    };

    using Elements = std::vector<std::shared_ptr<Element>>;

    class ContainerElement : public Element{
    public:
        ContainerElement(const std::string& type):type_(type){
        }
        void addAttribute(const std::string& name, const std::string& value);
        void addElement(std::shared_ptr<Element>);
        std::string Generate() const override;
    private:
        std::string type_;
        std::unordered_map<std::string,std::string> attributes_;
        Elements elements_;
    };

    class Text : public Element{
    public:
        Text (const std::string& text):text_(text){
        };
        void addText(const std::string& text);
        std::string Generate() const override;
    private:
        std::string text_;
    };

    class Document : public Element{
    public:
        void addHeaderElement(std::shared_ptr<Element> title);
        void addBodyElement(std::shared_ptr<Element> body);
        std::string Generate() const override;
    private:
        Elements header_;
        Elements body_;
    };

}  // namespace graph