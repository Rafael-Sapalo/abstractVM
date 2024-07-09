/*
** EPITECH PROJECT, 2024
** B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
** File description:
** Factory.cpp
*/

#include "Exception.hpp"
#include "Factory.hpp"
#include "Operand.hpp"
#include <cfloat>
#include <iostream>
#include <cstdint>


VM::IOperand *VM::Factory::createOperand(eOperandType type, const std::string &value)
{
    return (createType[type])(value);
}

VM::IOperand *VM::Factory::createInt8(const std::string &value)
{
    if (std::stoi(value) > INT8_MAX || std::stoi(value) < INT8_MIN)
        throw VM::Exception("Overflow or underflow on a value");
    return new Operand<int8_t>(value);
}

VM::IOperand *VM::Factory::createInt16(const std::string &value)
{
    if (std::stoi(value) > INT16_MAX || std::stoi(value) < INT16_MIN)
        throw VM::Exception("Overflow or underflow on a value");
    return new Operand<int16_t>(value);
}

VM::IOperand *VM::Factory::createInt32(const std::string &value)
{
    try {
        std::stoi(value);
    } catch (std::out_of_range &e) {
        throw VM::Exception("Overflow or underflow on a value");
    }
    return new Operand<int32_t>(value);
}

VM::IOperand *VM::Factory::createFloat(const std::string &value)
{
    try {
        std::stof(value);
    } catch (std::out_of_range &e) {
        throw VM::Exception("Overflow or underflow on a value");
    }
    return new Operand<float>(value);
}

VM::IOperand *VM::Factory::createDouble(const std::string &value)
{
    try {
        std::stod(value);
    } catch (std::out_of_range &e) {
        throw VM::Exception("Overflow or underflow on a value");
    }
    return new Operand<double>(value);
}
