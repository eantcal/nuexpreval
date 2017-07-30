//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#ifndef __NU_EXPR_COMPILER_H__
#define __NU_EXPR_COMPILER_H__


/* -------------------------------------------------------------------------- */

#include "nu_exception.h"
#include "nu_expr_any.h"
#include "nu_expr_tknzr.h"
#include "nu_token_list.h"
#include "nu_ctx.h"

#include <list>


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

class expr_compiler_t {
public:
    //! ctors
    expr_compiler_t() = default;
    expr_compiler_t(const expr_compiler_t&) = delete;
    expr_compiler_t& operator=(const expr_compiler_t&) = delete;

    //! Creates an expression using tokens got by a given tokenizer
    expr_any_t::handle_t compile(expr_tknzr_t& tknzr);

    //! Creates an expression using a given token-list
    expr_any_t::handle_t compile(token_list_t tl, size_t expr_pos);


protected:
    static variant_t::type_t get_type(const token_t& t);

    expr_any_t::handle_t parse_operand(token_list_t& tl);

    bool parse_operator(token_list_t& tl, std::string& value);

    expr_any_t::handle_t parse(
        token_list_t& tl, expr_any_t::handle_t first_param = nullptr);

    static void reduce_brackets(token_list_t& rtl);
    static void convert_subscription_brackets(token_list_t& rtl);

    static void fix_real_numbers(token_list_t& rtl);
};


/* -------------------------------------------------------------------------- */

}


/* -------------------------------------------------------------------------- */

#endif // __NU_EXPR_COMPILER_H__
