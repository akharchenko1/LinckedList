#pragma once
#include <cstdlib>
#include <exception>
#include <string>


namespace LinkedLists {


    class LinkedListsException : public std::exception {
    private:
        std::string errorMessage_;
    public:
        LinkedListsException() = default;

        explicit LinkedListsException(const std::string& errorMessage) {
            errorMessage_ = errorMessage;
        }

        const char* what() const noexcept override {
        return errorMessage_.c_str();
        }
    };

}
