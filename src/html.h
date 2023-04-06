#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <variant>
#include <string>
#include <memory>

namespace html {

    //Интерфейс элементов HTML документов
    class IElement{
    public:
        virtual std::string Generate() const = 0;
    };

    using Elements = std::vector<std::shared_ptr<IElement>>;

    class ContainerElement : public IElement{
    public:
        ContainerElement(const std::string& type):type_(type){
        }
        void addAttribute(const std::string& name, const std::string& value);
        void addElement(std::shared_ptr<IElement>);
        std::string Generate() const override;
    private:
        std::string type_;
        std::unordered_map<std::string,std::string> attributes_;
        Elements elements_;
    };

    class Text : public IElement{
    public:
        Text (const std::string& text):text_(text){
        };
        void addText(const std::string& text);
        std::string Generate() const override;
    private:
        std::string text_;
    };

    class Document : public IElement{
    public:
        void addHeaderElement(std::shared_ptr<IElement> title);
        void addBodyElement(std::shared_ptr<IElement> body);
        std::string Generate() const override;
    private:
        Elements header_;
        Elements body_;
    };

}  // namespace graph