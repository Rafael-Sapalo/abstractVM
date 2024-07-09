/*
** EPITECH PROJECT, 2024
** B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
** File description:
** Factory
*/

#include "IOperand.hpp"
#include "Stack.hpp"
#include <string>

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

namespace VM 
{
    class Factory {

        public:
            Factory(): _stack(Stack()) {};
            ~Factory() = default;
            static IOperand *createOperand(eOperandType type, const std::string &value);
            static IOperand *createInt8(const std::string &value);
            static IOperand *createInt16(const std::string &value);
            static IOperand *createInt32(const std::string &value);
            static IOperand *createFloat(const std::string &value);
            static IOperand *createDouble(const std::string &value);
            Stack _stack;
            static constexpr IOperand *(*createType[5])(const std::string &value) = {
                &Factory::createInt8,
                &Factory::createInt16,
                &Factory::createInt32,
                &Factory::createFloat,
                &Factory::createDouble
            };
    };
}

#endif /* !FACTORY_HPP_ */
