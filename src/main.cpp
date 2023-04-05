#include <iostream>
#include <filesystem>
#include <fstream>

#include "tests.h"
#include "html_generator.h"

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

    if(argc > 0){
        const std::string_view path(argv[1]);
        GenerateHTML(path, "output.html"s);
    }else{
        std::cout<<"Running tests"s;
        tests::ParsingRectangles(std::cerr);
        tests::GeneralGraphicsTest(std::cerr);
    }

    return 0;
}
