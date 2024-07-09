/*
** EPITECH PROJECT, 2024
** B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
** File description:
** Operand
*/

#include "Operand.hpp"
#include "Factory.hpp"
#include "Exception.hpp"
#include <sstream>
#include <cmath>

std::string convertToStringWithPrecision(double const &num, const int &precision) {
    std::stringstream ss;
    ss.unsetf(std::ios::floatfield);
    ss.precision(precision);
    ss << num;
    return ss.str();
}

template <typename T>
VM::Operand<T>::Operand(const std::string &value) {
    if (typeid(T) == typeid(int8_t))
        this->_value = static_cast<T>(std::stoi(value));
    else if (typeid(T) == typeid(int16_t))
        this->_value = static_cast<T>(std::stoi(value));
    else if (typeid(T) == typeid(int32_t))
        this->_value = static_cast<T>(std::stoi(value));
    else if (typeid(T) == typeid(float))
        this->_value = static_cast<T>(std::stof(value));
    else
        this->_value = static_cast<T>(std::stod(value));
}

template <typename T>
VM::eOperandType VM::Operand<T>::getType() const {
    if (typeid(T) == typeid(int8_t))
        return INT8;
    else if (typeid(T) == typeid(int16_t))
        return INT16;
    else if (typeid(T) == typeid(int32_t))
        return INT32;
    else if (typeid(T) == typeid(float))
        return FLOAT;
    else
        return DOUBLE;
}

template <typename T>
VM::IOperand *VM::Operand<T>::next() const {
    return new Operand<T>(this->toString());
}

template <typename T>
std::string VM::Operand<T>::toString() const {
    std::string str = std::to_string(this->_value);
    if (!(typeid(T) != typeid(float) && typeid(T) != typeid(double))) {
        size_t precision = 0;
        if (this->getType() == FLOAT)
            precision = 7;
        else
            precision = 15;
        std::stringstream sf;
        sf.unsetf(std::ios::floatfield);
        sf.precision(precision);
        sf << this->_value;
        str = sf.str();
    }
    return str;
}

template <typename T>
VM::IOperand *VM::Operand<T>::operator+(const VM::IOperand &rhs) const {
    VM::Factory factory;
    if (this->getType() > rhs.getType()) {
        if (typeid(T) != typeid(float) && typeid(T) != typeid(double) && typeid(rhs) != typeid(float) && typeid(rhs) != typeid(double)) {
            return factory.createOperand(this->getType(), std::to_string(std::stoi(rhs.toString()) + this->_value));
        } else if (typeid(T) == typeid(float)) {
            return factory.createOperand(FLOAT, std::to_string(std::stof(rhs.toString()) + this->_value));
        } else {
            return factory.createOperand(DOUBLE, std::to_string(std::stod(rhs.toString()) + this->_value));
        }
    } else {
        return factory.createOperand(rhs.getType(), convertToStringWithPrecision(std::stod(rhs.toString()) + this->_value, 16));
    }
}

template <typename T>
VM::IOperand *VM::Operand<T>::operator-(const VM::IOperand &rhs) const {
    VM::Factory factory;
    if (this->getType() > rhs.getType()) {
        if (typeid(T) != typeid(float) && typeid(T) != typeid(double) && typeid(rhs) != typeid(float) && typeid(rhs) != typeid(double)) {
            return factory.createOperand(this->getType(), std::to_string(std::stoi(rhs.toString()) - this->_value));
        } else if (typeid(T) == typeid(float)) {
            return factory.createOperand(FLOAT, std::to_string(std::stof(rhs.toString()) - this->_value));
        } else {
            return factory.createOperand(DOUBLE, std::to_string(std::stod(rhs.toString()) - this->_value));
        }
    } else {
        return factory.createOperand(rhs.getType(), convertToStringWithPrecision(std::stod(rhs.toString()) - this->_value, 16));
    }
}

template <typename T>
VM::IOperand *VM::Operand<T>::operator*(const VM::IOperand &rhs) const {
    VM::Factory factory;
    if (this->getType() > rhs.getType()) {
        if (typeid(T) != typeid(float) && typeid(T) != typeid(double) && typeid(rhs) != typeid(float) && typeid(rhs) != typeid(double)) {
            return factory.createOperand(this->getType(), std::to_string(std::stoi(rhs.toString()) * this->_value));
        } else if (typeid(T) == typeid(float)) {
            return factory.createOperand(FLOAT, std::to_string(std::stof(rhs.toString()) * this->_value));
        } else {
            return factory.createOperand(DOUBLE, std::to_string(std::stod(rhs.toString()) * this->_value));
        }
    } else {
        return factory.createOperand(rhs.getType(), convertToStringWithPrecision(std::stod(rhs.toString()) * this->_value, 16));
    }
}

template <typename T>
VM::IOperand *VM::Operand<T>::operator/(const VM::IOperand &rhs) const {
    if (this->_value == 0)
        throw VM::Exception("Division by zero");
    VM::Factory factory;
    if (this->getType() > rhs.getType()) {
        if (typeid(T) != typeid(float) && typeid(T) != typeid(double) && typeid(rhs) != typeid(float) && typeid(rhs) != typeid(double)) {
            return factory.createOperand(this->getType(), std::to_string(std::stoi(rhs.toString()) / this->_value));
        } else if (typeid(T) == typeid(float)) {
            return factory.createOperand(FLOAT, std::to_string(std::stof(rhs.toString()) / this->_value));
        } else {
            return factory.createOperand(DOUBLE, std::to_string(std::stod(rhs.toString()) / this->_value));
        }
    } else {
        return factory.createOperand(rhs.getType(), convertToStringWithPrecision(std::stod(rhs.toString()) / this->_value, 16));
    }
}

template <typename T>
VM::IOperand *VM::Operand<T>::operator%(const VM::IOperand &rhs) const {
    if (this->_value == 0)
        throw VM::Exception("Modulo by zero");
    VM::Factory factory;
    if (this->getType() > rhs.getType()) {
        if (typeid(T) != typeid(float) && typeid(T) != typeid(double) && typeid(rhs) != typeid(float) && typeid(rhs) != typeid(double)) {
            return factory.createOperand(this->getType(), std::to_string(std::stoi(rhs.toString()) % static_cast<int>(this->_value)));
        } else if (typeid(T) == typeid(float)) {
            return factory.createOperand(FLOAT, std::to_string(std::fmod(std::stof(rhs.toString()), this->_value)));
        } else {
            return factory.createOperand(DOUBLE, std::to_string(std::fmod(std::stod(rhs.toString()), this->_value)));
        }
    } else {
        return factory.createOperand(rhs.getType(), convertToStringWithPrecision(std::fmod(std::stod(rhs.toString()), this->_value), 16));
    }
}