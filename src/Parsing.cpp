/*
** EPITECH PROJECT, 2024
** B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
** File description:
** Parsing
*/

#include "Parsing.hpp"
#include "Exception.hpp"
#include <regex>
#include <unordered_map>

bool isTypeValid(const std::string &line) {
    static const std::regex regex(R"(int8|int16|int32|float|double)");
    return std::regex_match(line, regex);
}

void VM::Parsing::doParsing(std::istream &strm) {
    std::string fstrm;
    std::string line;
    while (std::getline(strm, line)) {
        if (line == ";;")
            break;
        fstrm += line + '\n';
    }
    line.clear();
    for (char ch : fstrm) {
        if (line == "exit") {
            this->_lines.push_back(line);
            break;
        }
        if (ch == '\n') {
            this->tokenLines(line);
            line.clear();
        } else {
            line += ch;
        }
    }
    if (this->_lines.empty() || this->_lines.back() != "exit")
        throw Exception("No exit instruction");
    this->parseLines();
}

void VM::Parsing::parseLines() {
    size_t ln = 1;
    std::unordered_map<std::string, int> instructionMap = {
        {"push", 1}, {"pop", 2}, {"dump", 3}, {"assert", 4}, {"add", 5}, {"sub", 6},
        {"mul", 7}, {"div", 8}, {"mod", 9}, {"print", 10}, {"exit", 11}, {"clear", 12},
        {"dup", 13}, {"swap", 14}, {"load", 15}, {"store", 16}
    };

    for (size_t i = 0; i < this->_lines.size(); i++) {
        try {
            size_t index = 0;
            switch (instructionMap[this->_lines[i]]) {
                case 1:
                    if (this->_lines.size() < i + 3)
                        throw Exception("invalid push instruction");
                    this->pushOper(this->_lines[i + 1], this->_lines[i + 2]);
                    i += 2;
                    break;
                case 2:
                    this->_factory._stack.pop();
                    break;
                case 3:
                    this->_factory._stack.dump();
                    break;
                case 4:
                    if (this->_lines.size() < i + 3)
                        throw Exception("invalid assert instruction");
                    if (isTypeValid(this->_lines[i + 1]) && std::regex_match(this->_lines[i + 2], std::regex("-?[[:digit:]]+\\.*[[:digit:]]*"))) {
                        this->assertOpeand(this->_lines[i + 1], this->_lines[i + 2]);
                        i += 2;
                    } else {
                        throw Exception("invalid assert instruction");
                    }
                    break;
                case 5:
                    this->_factory._stack.add();
                    break;
                case 6:
                    this->_factory._stack.sub();
                    break;
                case 7:
                    this->_factory._stack.mul();
                    break;
                case 8:
                    this->_factory._stack.div();
                    break;
                case 9:
                    this->_factory._stack.mod();
                    break;
                case 10:
                    this->_factory._stack.print();
                    break;
                case 11:
                    return;
                case 12:
                    this->_factory._stack.clear();
                    break;
                case 13:
                    this->_factory._stack.dup();
                    break;
                case 14:
                    this->_factory._stack.swap();
                    break;
                case 15:
                    if (this->_lines.size() < i + 3)
                        throw Exception("invalid load instruction");
                    index = std::stoi(this->_lines[i + 2]);
                    this->_factory._stack.load(index);
                    i += 2;
                    break;
                case 16:
                    if (this->_lines.size() < i + 3)
                        throw Exception("invalid store instruction");
                    index = std::stoi(this->_lines[i + 2]);
                    this->_factory._stack.store(index);
                    i += 2;
                    break;
                default:
                    if (this->_lines[i][0] != ';') {
                        throw Exception("Unknown instruction");
                    }
                    break;
            }
            ln++;
        } catch (std::exception &e) {
            std::string error = "&cline " + std::to_string(ln) + ":&e " + e.what();
            throw Exception(error);
            return;
        }
    }
}

void VM::Parsing::pushOper(std::string const &type, std::string const &value) {
    VM::eOperandType operandType;
    if (type == "int8") {
        operandType = VM::eOperandType::INT8;
    } else if (type == "int16") {
        operandType = VM::eOperandType::INT16;
    } else if (type == "int32") {
        operandType = VM::eOperandType::INT32;
    } else if (type == "float") {
        operandType = VM::eOperandType::FLOAT;
    } else if (type == "double") {
        operandType = VM::eOperandType::DOUBLE;
    } else {
        throw Exception("invalid push instruction");
    }
    this->_factory._stack.push(this->_factory.createOperand(operandType, value));
}

void VM::Parsing::assertOpeand(std::string const &type, std::string const &value) {
    VM::eOperandType operandType;
    if (type == "int8") {
        operandType = VM::eOperandType::INT8;
    } else if (type == "int16") {
        operandType = VM::eOperandType::INT16;
    } else if (type == "int32") {
        operandType = VM::eOperandType::INT32;
    } else if (type == "float") {
        operandType = VM::eOperandType::FLOAT;
    } else if (type == "double") {
        operandType = VM::eOperandType::DOUBLE;
    } else {
        throw Exception("invalid assert instruction");
    }
    this->_factory._stack.assert(operandType, value);
}

void VM::Parsing::tokenLines(std::string &line) {
    std::regex regex(
        R"((int8|int16|int32|float|double)|(;.*$)|([[:alpha:]]+|\(-?[[:digit:]]+\.?[[:digit:]]*\)))"
    );
    std::smatch match;

    while (std::regex_search(line, match, regex)) {
        std::string token = match[0];

        if (token.front() == '(') {
            token = token.substr(1, token.size() - 2);
        }
        if (token.front() != ';') {
            this->_lines.push_back(token);
        }
        line = match.suffix().str();
    }
}