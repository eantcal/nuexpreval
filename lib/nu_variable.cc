//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#include "nu_variable.h"
#include "nu_exception.h"

#include <algorithm>
#include <cassert>
#include <set>


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

bool variable_t::is_valid_name(std::string name)
{
    if (name.empty())
        return false;

    std::transform(name.begin(), name.end(), name.begin(), tolower);

    auto letter = [](char c) { return c >= 'a' && c <= 'z'; };

    char first_char = name.c_str()[0];

    if (!letter(first_char) && first_char != '_')
        return false;

    if (name.size() == 1)
        return first_char != '_';

    auto number = [](char c) { return (c >= '0' && c <= '9'); };

    char prev_c = 0;

    for (size_t i = 1; i < name.size(); ++i) {
        char c = name.c_str()[i];

        bool valid = letter(c) || (c == '.' && prev_c != '.') || c == '_'
            || number(c);

        if (!valid)
            return false;

        prev_c = c;
    }

    return true;
}


/* -------------------------------------------------------------------------- */

} // namespace nu
