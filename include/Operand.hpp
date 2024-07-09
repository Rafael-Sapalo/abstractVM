/*
** EPITECH PROJECT, 2024
** B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
** File description:
** Operand
*/

#include "IOperand.hpp"

#ifndef OPERAND_HPP_
#define OPERAND_HPP_

namespace VM 
{

    template<typename T>
    class Operand: public IOperand {
        public:
            Operand(const std::string &value);
            ~Operand() = default;

            std::string toString() const override;
            eOperandType getType() const override;

            IOperand *next() const override;
            IOperand* operator+(const IOperand& rhs) const override;
            IOperand* operator-(const IOperand& rhs) const override;
            IOperand* operator*(const IOperand& rhs) const override;
            IOperand* operator/(const IOperand& rhs) const override;
            IOperand* operator%(const IOperand& rhs) const override;
        protected:
        private:
            T _value;
            eOperandType _type;
    };

    template class Operand<int8_t>;
    template class Operand<int16_t>;
    template class Operand<int32_t>;
    template class Operand<float>;
    template class Operand<double>;
}

#endif /* !OPERAND_HPP_ */
