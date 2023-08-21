/*
 * Dargon Programming Language
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 *
 * FILE: Exception.h
 *
 * DESCRIPTION: Dargon-specific exceptions.
 *
 * SINCE: v0.1
 *
 */

#ifndef DARGON_EXCEPT_H
#define DARGON_EXCEPT_H

#include <stdexcept>
#include <string>

namespace dargon {

	/**
     * @brief Dargon-specific exception.
    */
    class Exception : public std::exception {
    public:
        Exception(const std::string& msg) : _msg(msg) {}
        virtual const char* what() const noexcept override;
    private:
        const std::string _msg;
    };

};

#endif
