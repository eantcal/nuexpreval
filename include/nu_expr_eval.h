//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#ifndef __NU_EXPREVAL_H__
#define __NU_EXPREVAL_H__


/* -------------------------------------------------------------------------- */

#include "nu_error_codes.h"
#include "nu_expr_compiler.h"
#include "nu_global_function_tbl.h"
#include "nu_ctx.h"
#include "nu_tokenizer.h"


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

static inline
variant_t expr_eval(ctx_t& ctx, const std::string& data) {

    tokenizer_t st(data);
    expr_compiler_t ep;

    return ep.compile(st)->eval(ctx);
}


/* -------------------------------------------------------------------------- */

} // namespace nu


/* -------------------------------------------------------------------------- */

#endif // __NU_EVAL_EXPR_H__


/* -------------------------------------------------------------------------- */
