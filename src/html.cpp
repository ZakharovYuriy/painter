#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

#include "html.h"

namespace HTML {

    void ContainerElement::addAttribute(const std::string& name, const std::string& value){
        attributes_[name]=value;
    }
    
    void ContainerElement::addElement(Element* element){
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

        html += "</" + type_ + ">";

        return html;
    }

    void Text::addText(const std::string& text){
        text_=text;
    }

    std::string Text::Generate() const{
        return text_;
    }

}  // namespace graph