//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#include "nu_expr_var.h"
#include "nu_error_codes.h"

/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

variant_t expr_var_t::eval(ctx_t& ctx) const
{
    if (!ctx.is_defined(_name)) {
        rt_error_code_t::get_instance().throw_exc(
            rt_error_code_t::E_VAR_UNDEF, _name);
    }
    
    return ctx[_name];
}

/* -------------------------------------------------------------------------- */

}


/* -------------------------------------------------------------------------- */
