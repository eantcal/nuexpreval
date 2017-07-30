//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#ifndef __NU_VARIABLE_H__
#define __NU_VARIABLE_H__

#include "nu_cpp_lang.h"

#include <set>
#include <string>


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

struct variable_t {
    enum class type_t {
        UNDEFINED,
        INTEGER,
        FLOAT,
        DOUBLE,
        STRING,
        BOOLEAN,
        LONG64,
        ANY
    };


    static bool is_valid_name(std::string name);


    static inline bool is_number(type_t t) noexcept {
        return t == type_t::LONG64 || t == type_t::INTEGER || t == type_t::FLOAT
            || t == type_t::DOUBLE || t == type_t::BOOLEAN;
    }


    static inline bool is_float(type_t t) noexcept {
        return t == type_t::FLOAT || t == type_t::DOUBLE;
    }


    static inline bool is_integral(type_t t) noexcept {
        return t == type_t::LONG64 || t == type_t::INTEGER
            || t == type_t::BOOLEAN;
    }
};


/* -------------------------------------------------------------------------- */

} // namespace nu


/* -------------------------------------------------------------------------- */

#endif // __NU_VARIABLE_H__
