/*
** EPITECH PROJECT, 2024
** B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
** File description:
** Stack
*/

#include "Stack.hpp"
#include "../include/Exception.hpp"
#include "Factory.hpp"
#include <algorithm>
#include <iostream>


VM::Stack::Stack()
{
    this->_registers.resize(16);
    this->_registers.assign(16, nullptr);
}

VM::Stack::~Stack()
{
    for (IOperand *op: this->_stack) {
        if (op != nullptr) {
            delete op;
        }
    }
    this->_stack.clear();
    for (IOperand *op: this->_registers) {
        if (op != nullptr) {
            delete op;
        }
    }
    this->_registers.clear();
}

void VM::Stack::push(IOperand *op)
{
    std::deque<IOperand *>::iterator it = this->_stack.begin();
    this->_stack.insert(it, op);
}

void VM::Stack::pop()
{
    std::deque<IOperand *>::iterator it = this->_stack.begin();
    if (this->_stack.empty()) {
        throw Exception("Stack is empty");
    }
    delete this->_stack[0];
    this->_stack.erase(it);
}

void VM::Stack::clear()
{
    for (IOperand *op: this->_stack) {
        if (op != nullptr) {
            delete op;
        }
    }
    this->_stack.clear();
}

void VM::Stack::dup()
{
    if (this->_stack.empty()) {
        throw Exception("Stack is empty");
    }
    IOperand *duplicate = this->_stack.front()->next();
    this->_stack.push_front(duplicate);
}

void VM::Stack::swap()
{
    if (this->_stack.size() < 2) {
        throw Exception("Stack is too short");
    }
    std::swap(this->_stack[0], this->_stack[1]);
}

void VM::Stack::assert(eOperandType type, const std::string &value)
{
    if (this->_stack.size() > 0) {
        if (this->_stack[0]->getType() != type) {
            throw Exception("Assert failed");
        }
        if (this->_stack[0]->toString() != value) {
            throw Exception("Assert failed");
        }
    } else {
        throw Exception("Trying to asser: Stack is empty");
    }
}

void VM::Stack::add()
{
    if (this->_stack.size() > 1) {
        IOperand *tmp = *this->_stack[0] + *this->_stack[1];
        this->pop();
        this->pop();
        this->push(tmp);
    } else {
        throw Exception("Stack is too short");
    }
}
 
void VM::Stack::mul()
{
    if (this->_stack.size() > 1) {
        IOperand *tmp = *this->_stack[0] * *this->_stack[1];
        this->pop();
        this->pop();
        this->push(tmp);
    } else {
        throw Exception("Stack is too short");
    }
}

void VM::Stack::sub()
{
    if (this->_stack.size() > 1) {
        IOperand *tmp = *this->_stack[0] - *this->_stack[1];
        this->pop();
        this->pop();
        this->push(tmp);
    } else {
        throw Exception("Stack is too short");
    } 
}

void VM::Stack::div()
{
    if (this->_stack.size() > 1) {
        IOperand *tmp = *this->_stack[0] / *this->_stack[1];
        this->pop();
        this->pop();
        this->push(tmp);
    } else {
        throw Exception("Stack is too short");
    }
}

void VM::Stack::mod()
{
    if (this->_stack.size() > 1) {
        IOperand *tmp = *this->_stack[0] % *this->_stack[1];
        this->pop();
        this->pop();
        this->push(tmp);
    } else {
        throw Exception("Stack is too short");
    }
}

void VM::Stack::load(size_t const &index)
{
    if (index > 15) {
        throw Exception("Invalid index");
    }
    if (this->_registers[index] != nullptr) {
        this->push(this->_registers[index]->next());
    } else {
        throw Exception("Register is empty");
    }
}

void VM::Stack::store(size_t const &index)
{
    if (index > 15) {
        throw Exception("Invalid index");
    }
    if (this->_stack.size() > 0) {
        Factory Factory;
        this->_registers[index] = this->_stack[0]->next();
        this->pop();
    } else {
        throw Exception("Store on empty stack");
    }
}

void VM::Stack::print() const
{
    if (this->_stack.size() > 0) {
        if (this->_stack[0]->getType() == INT8) {
            std::cout << static_cast<char>(std::stoi(this->_stack[0]->toString())) << std::endl;
        } else {
            throw Exception("Print on non INT8 value");
        }
    } else {
        throw Exception("Print on empty stack");
    }
}

void VM::Stack::dump() const {
    for (IOperand *operand : this->_stack) {
        std::cout << operand->toString() << std::endl;
    }
}