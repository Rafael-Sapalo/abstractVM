/*
** EPITECH PROJECT, 2024
** B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
** File description:
** main
*/

#include <iostream>
#include <fstream>
#include "Exception.hpp"
#include "Parsing.hpp"

int main(int argc, char **argv) {
    std::istream *inputStream;
    std::ifstream file;

    if (argc > 2) {
        std::cerr << "Usage: ./abstractVM [file]" << std::endl;
        return 84;
    }

    if (argc == 2) {
        file.open(argv[1]);
        if (!file.is_open()) {
            std::cerr << "Error opening file" << std::endl;
            return 84;
        }
        inputStream = &file;
    } else {
        inputStream = &std::cin;
    }

    try {
        VM::Parsing parser;
        parser.doParsing(*inputStream);
        if (argc == 2) {
            file.close();
        }
    } catch(const VM::Exception& e) {
        std::cerr << e.what() << '\n';
        return 84;
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 84;
    }

    return 0;
}
