//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#ifndef __NU_EXPR_BIN_H__
#define __NU_EXPR_BIN_H__


/* -------------------------------------------------------------------------- */

#include "nu_expr_any.h"
#include "nu_global_function_tbl.h"


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

class expr_bin_t : public expr_any_t {
public:
    using func_t = func_bin_t;

    //! ctor
    expr_bin_t(func_t f, expr_any_t::handle_t var1, expr_any_t::handle_t var2)
        : _func(f)
        , _var1(var1)
        , _var2(var2)
    {
    }


    expr_bin_t() = delete;
    expr_bin_t(const expr_bin_t&) = default;
    expr_bin_t& operator=(const expr_bin_t&) = default;

    //! Returns f(var1, var2) appling ctor given arguments
    virtual variant_t eval(ctx_t& ctx) const
    {
        return _func(_var1->eval(ctx), _var2->eval(ctx));
    }

    //! Returns false for a binary expression
    virtual bool empty() const noexcept override { 
        return false; 
    }

    std::string name() const noexcept override {
        std::string ret;

        if (_var1) {
            ret = _var1->name();

            if (_var2 && !_var2->name().empty()) {
                ret += ".";
                ret += _var2->name();
            }
        }

        return ret;
    }

    func_args_t get_args() const noexcept override {
        func_args_t ret;

        if (_var1)
            ret = _var1->get_args();
        if (_var2) {
            for (const auto& e : _var2->get_args())
                ret.push_back(e);
        }

        return ret;
    }


protected:
    func_bin_t _func;
    expr_any_t::handle_t _var1, _var2;
};


/* -------------------------------------------------------------------------- */

}


/* -------------------------------------------------------------------------- */

#endif
