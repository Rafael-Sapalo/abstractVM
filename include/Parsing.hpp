/*
** EPITECH PROJECT, 2024
** B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
** File description:
** Parsing.hpp
*/

#include <istream>
#include <iostream>
#include <vector>
#include "Factory.hpp"

namespace VM
{
    class Parsing {
        public:
            Parsing() = default;
            ~Parsing() = default;
            void doParsing(std::istream &strm);
            void parseLines();
            void tokenLines(std::string &line);
            void assertOpeand(const std::string &type, const std::string &value);
            void pushOper(const std::string &type, const std::string &value);
            VM::Factory _factory;
        protected:
        private:
            std::vector<std::string> _lines;
    };
}

