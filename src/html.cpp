#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include "html.h"

using namespace std::literals;

namespace html {

    void ContainerElement::addAttribute(const std::string& name, const std::string& value){
        attributes_[name]=value;
    }
    
    void ContainerElement::addElement(std::shared_ptr<IElement> element){
        elements_.push_back(element);
    }

    std::string ContainerElement::Generate() const {
        std::string html;
        html += "<" + type_;

        // Добавляем атрибуты
        for (auto const& [name, value] : attributes_) {
            html += " " + name + "=\"" + value + "\"";
        }

        html += ">";

        // Добавляем вложенные элементы
        for (auto const& element : elements_) {
            html += element->Generate();
        }

        html += "</" + type_ + ">\n";

        return html;
    }

    void Text::addText(const std::string& text){
        text_ += text;
    }

    std::string Text::Generate() const{
        return text_;
    }

    void Document::addHeaderElement(std::shared_ptr<IElement> title){
        header_.push_back(title);
    }
    void Document::addBodyElement(std::shared_ptr<IElement> body){
        body_.push_back(body);
    }

    std::string Document::Generate() const{
        std::string html;
        html = "<!DOCTYPE html>\n<html>\n   <head>\n"s;
        
        for (auto const& element : header_) {
            html += element->Generate();
        }

        html += "   </head>\n  <body>\n"s;

        for (auto const& element : body_) {
            html += element->Generate();
        }

        html += "   </body>\n</html>\n"s;
        return html;
    }

}  // namespace graph