//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#include "nu_expr_subscrop.h"


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

variant_t expr_subscrop_t::eval(ctx_t& ctx) const
{
    if (!ctx.is_defined(_name))
        throw exception_t(
            std::string("Error: \"" + _name + "\" undefined symbol"));

    const variant_t& var_value = ctx[_name];
    (void)var_value; // TODO

    throw exception_t(std::string("Cannot evaluate \"" + _name + "\""));
}


/* -------------------------------------------------------------------------- */

} // namespace


/* -------------------------------------------------------------------------- */
