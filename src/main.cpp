#include <iostream>
#include <filesystem>
#include <fstream>

#include "tests.h"
#include "html_generator.h"

// Открываем файлы на чтение и запись при успешном открытии - генерируем HTML страницу
// Open files for reading and writing on successful opening - generate an HTML page
void GenerateHTML (std::string_view path, std::string file_name){
    std::ifstream input_file(std::filesystem::canonical(path));
    std::ofstream output_file(file_name);
    if(input_file && output_file){
        output_file << generator::CreateHTMLWithTable(generator::ReadRectangles(input_file));
    }else{
        throw std::runtime_error("Error opening file");
    }
}

int main(int argc, char *argv[]) {
    using namespace std::literals;

    if(argc > 1){
        const std::string_view path(argv[1]);
        GenerateHTML(path, "output.html"s);
    }else{
        std::cout<<"Running tests"s;
        tests::ParsingRectanglesFromFile(std::cerr);
        //tests::GeneralGraphicsTest(std::cerr);
    }

    return 0;
}
