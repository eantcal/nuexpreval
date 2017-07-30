//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#include "nu_expr_function.h"


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

variant_t expr_function_t::eval(ctx_t& ctx) const
{
    if (!global_function_tbl_t::get_instance().is_defined(_name)) {
        variant_t* var = nullptr;

        if (!var && ctx.is_defined(_name)) {
            var = &(ctx[_name]);
        }

        if (!var)
            throw exception_t(
                std::string("Error: \"" + _name + "\" undefined symbol"));

        return (*var)[_var[0]->eval(ctx).to_int()];
    }

    return global_function_tbl_t::get_instance()[_name](ctx, _name, _var);
}


/* -------------------------------------------------------------------------- */

} // namespace nu
