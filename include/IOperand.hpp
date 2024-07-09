/*
** EPITECH PROJECT, 2024
** B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
** File description:
** IOperand
*/

#include <string>

#ifndef IOPERAND_HPP_
#define IOPERAND_HPP_

namespace VM {
    enum eOperandType {
        INT8,
        INT16,
        INT32,
        FLOAT,
        DOUBLE
    };

class IOperand {
    public:
        virtual std::string toString() const = 0;
        virtual eOperandType getType() const = 0;

        virtual IOperand *next() const = 0;
        virtual IOperand* operator+(const IOperand& rhs) const = 0;
        virtual IOperand* operator-(const IOperand& rhs) const = 0;
        virtual IOperand* operator*(const IOperand& rhs) const = 0;
        virtual IOperand* operator/(const IOperand& rhs) const = 0;
        virtual IOperand* operator%(const IOperand& rhs) const = 0;

        virtual ~IOperand() {};

    protected:
    private:
};

}

#endif /* !IOPERAND_HPP_ */
