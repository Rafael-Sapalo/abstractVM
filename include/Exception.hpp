/*
** EPITECH PROJECT, 2024
** B-SYN-400-PAR-4-1-abstractVM-rafael.sapalo-esteves
** File description:
** Exception
*/

#include <exception>
#include <string>


#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

namespace VM {
    class Exception : public std::exception {
        public:
        Exception(std::string const &message): _message(message) {};
        ~Exception() = default;

        const char* what() const noexcept { return this->_message.c_str(); }

        protected:
        private:
            std::string _message;
    };
}

#endif /* !EXCEPTION_HPP_ */
