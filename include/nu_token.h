//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#ifndef __NU_TOKEN_H__
#define __NU_TOKEN_H__


/* -------------------------------------------------------------------------- */

#include <algorithm>
#include <deque>
#include <memory>
#include <string>

#include "nu_cpp_lang.h"


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

//! Tonken class indentifier
enum class tkncl_t {
    UNDEFINED,
    BLANK,
    NEWLINE,
    IDENTIFIER,
    INTEGRAL,
    REAL,
    OPERATOR,
    SUBEXP_BEGIN,
    SUBEXP_END,
    STRING_LITERAL,
    STRING_COMMENT,
    SUBSCR_BEGIN,
    SUBSCR_END,
    LINE_COMMENT
};


/* -------------------------------------------------------------------------- */

/**
 * This class holds a token data
 */
class token_t {
    friend class base_tknzr_t;

public:
    enum class case_t { LOWER, NOCHANGE };

    using data_ptr_t = std::shared_ptr<std::string>;

    token_t(const std::string& id, tkncl_t t, size_t pos,
        data_ptr_t expr_ptr) noexcept : _identifier(id),
        _type(t),
        _position(pos),
        _expression_ptr(expr_ptr)
    {}

    token_t() = delete;
    token_t(const token_t&) = default;
    token_t& operator=(const token_t&) = default;

    void set_identifier(const std::string& id) noexcept {
        _identifier = id;
    }

    const std::string& identifier() const noexcept { 
        return _identifier; 
    }
        
    tkncl_t type() const noexcept { 
        return _type; 
    }

    void set_type(tkncl_t cl) noexcept { 
        _type = cl; 
    }

    size_t position() const noexcept { 
        return _position; 
    }

    void set_position(size_t pos) noexcept { 
        _position = pos; 
    }

    std::string expression() const noexcept { 
        return *_expression_ptr; 
    }

    data_ptr_t expression_ptr() const noexcept { 
        return _expression_ptr; 
    }

    token_t(token_t&& other)
        : _identifier(std::move(other._identifier))
        , _type(std::move(other._type))
        , _position(std::move(other._position))
        , _expression_ptr(std::move(other._expression_ptr))
    {
    }

    token_t& operator=(token_t&& other) {
        if (this != &other) {
            _identifier = std::move(other._identifier);
            _type = std::move(other._type);
            _position = std::move(other._position);
            _expression_ptr = std::move(other._expression_ptr);
        }

        return *this;
    }

protected:
    token_t(size_t pos, data_ptr_t expr_ptr) noexcept
        : _position(pos),
          _expression_ptr(expr_ptr)
    {
    }

private:
    std::string _identifier;
    tkncl_t _type = tkncl_t::UNDEFINED;
    size_t _position = 0;
    data_ptr_t _expression_ptr;
};


/* -------------------------------------------------------------------------- */

} // namespace nu


/* -------------------------------------------------------------------------- */

#endif // __NU_TOKEN_H__
