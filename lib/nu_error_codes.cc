//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#include "nu_error_codes.h"
#include <cassert>


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

rt_error_code_t* rt_error_code_t::_instance_ptr = nullptr;


/* -------------------------------------------------------------------------- */

void rt_error_code_t::throw_exc(value_t errcode, const std::string& stmt)
{
    struct err_t : public error_code_t {
        int _err = 0;

        err_t(int err)
            : _err(err)
        {
        }

        int get() const noexcept { return _err; }
    };

    std::string errmsg = stmt.empty() ? "" : stmt + " ";
    errmsg += rt_error_code_t::get_instance().message(errcode);

    err_t err(errcode);

    runtime_error_t::error_if(true, runtime_error_t(err, errmsg));
}


/* -------------------------------------------------------------------------- */

std::string rt_error_code_t::message(value_t err_code)
{
    std::string ret;

    auto err_it = _err_desc_tbl.find(err_code);

    if (err_it != _err_desc_tbl.end())
        ret = err_it->second;

    return ret;
}


/* -------------------------------------------------------------------------- */

rt_error_code_t& rt_error_code_t::get_instance() noexcept
{
    if (!_instance_ptr)
        _instance_ptr = new rt_error_code_t();

    assert(_instance_ptr);

    return *_instance_ptr;
}


/* -------------------------------------------------------------------------- */

rt_error_code_t::rt_error_code_t()
{
    auto& e = _err_desc_tbl;
    e[E_DIV_BY_ZERO] = "division by zero";
    e[E_INVALID_ARGS] = "invalid arguments";
    e[E_FUNC_UNDEF] = "function not defined";
    e[E_TYPE_MISMATCH] = "type mismatch";
    e[E_TYPE_ILLEGAL] = "type illegal";
    e[E_INV_IDENTIF] = "invalid identifier";
    e[E_VAL_OUT_OF_RANGE] = "value out of range";
    e[E_VAR_UNDEF] = "variable not defined";
}


/* -------------------------------------------------------------------------- */

void syntax_error(const std::string& expr, size_t pos, const std::string& msg)
{
    std::string err(msg.empty() ? "Syntax Error" : msg);
    err += " at (" + nu::to_string(pos + 1) + "):\n";

    if (expr.size() > pos) {
        err += expr + "\n";

        for (size_t i = 0; i < pos; ++i)
            err += " ";

        for (size_t i = 0; i < expr.size() - pos; ++i)
            err += "^";
    }

    throw exception_t(err);
}


/* -------------------------------------------------------------------------- */

void syntax_error_if(
    bool condition, const std::string& expr, size_t pos, const std::string& msg)
{
    if (condition)
        syntax_error(expr, pos, msg);
}


/* -------------------------------------------------------------------------- */

void syntax_error_if(bool condition, const std::string& msg)
{
    if (condition)
        throw exception_t(msg);
}


/* -------------------------------------------------------------------------- */

}
