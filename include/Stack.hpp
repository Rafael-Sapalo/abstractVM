/*
** EPITECH PROJECT, 2024
** B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
** File description:
** Stack
*/

#include "Operand.hpp"
#include <deque>

#ifndef STACK_HPP_
#define STACK_HPP_

namespace VM 
{
    class Stack {
        public:
            Stack();
            ~Stack();
            void push(IOperand *op);
            void pop();
            void clear();
            void dup();
            void swap();
            void add();
            void sub();
            void mul();
            void div();
            void mod();
            void dump() const;
            void print() const;
            void load(size_t const &index);
            void store(size_t const &index);
            void assert(eOperandType type, const std::string &value);
            std::deque<IOperand *> _stack;
            std::deque<IOperand *> _registers;
    };
}

#endif /* !STACK_HPP_ */
