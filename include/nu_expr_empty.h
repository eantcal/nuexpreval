//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#ifndef __NU_EXPR_EMPTY_H__
#define __NU_EXPR_EMPTY_H__


/* -------------------------------------------------------------------------- */

#include "nu_expr_any.h"
#include "nu_variant.h"


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

class expr_empty_t : public expr_any_t {
public:
    //! ctors
    expr_empty_t() = default;
    expr_empty_t(const expr_empty_t&) = default;
    expr_empty_t& operator=(const expr_empty_t&) = default;

    //! It does nothing for an empty object
    virtual variant_t eval(ctx_t&) const override {
        return variant_t(0);
    }

    //! Returns true for an empty expression
    virtual bool empty() const noexcept override { 
        return true; 
    }

    std::string name() const noexcept override { 
        return ""; 
    }

    func_args_t get_args() const noexcept override {
        func_args_t dummy;
        return dummy;
    }
};


/* -------------------------------------------------------------------------- */
}

#endif // __NU_EXPR_EMPTY_H__
