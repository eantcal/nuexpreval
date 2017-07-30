//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#ifndef __NU_EXPREVAL_ERR_DEFS_H__
#define __NU_EXPREVAL_ERR_DEFS_H__


/* -------------------------------------------------------------------------- */

#include "nu_exception.h"
#include <map>
#include <string>


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

// Run-time error handling

class rt_error_code_t {
public:
    enum value_t {
        E_DIV_BY_ZERO,
        E_INVALID_ARGS,
        E_FUNC_UNDEF,
        E_TYPE_MISMATCH,
        E_TYPE_ILLEGAL,
        E_INV_IDENTIF,
        E_VAL_OUT_OF_RANGE,
        E_VAR_UNDEF
    };


    void throw_exc(value_t errcode, const std::string& stmt = "");


    inline void throw_if(
        bool cond, value_t errcode, const std::string& stmt = "")
    {
        if (cond)
            throw_exc(errcode, stmt);
    }


    std::string message(value_t);


    static rt_error_code_t& get_instance() noexcept;

private:
    static rt_error_code_t* _instance_ptr;

    rt_error_code_t();
    rt_error_code_t(const rt_error_code_t&) = delete;
    rt_error_code_t& operator=(const rt_error_code_t&) = delete;

    std::map<int, std::string> _err_desc_tbl;
};


/* -------------------------------------------------------------------------- */


void syntax_error(
    const std::string& expr, size_t pos, const std::string& msg = "");


/* -------------------------------------------------------------------------- */

void syntax_error_if(bool cond, const std::string& msg);


/* -------------------------------------------------------------------------- */

void syntax_error_if(bool cond, const std::string& expr, size_t pos,
    const std::string& msg = "");


/* -------------------------------------------------------------------------- */

}


/* -------------------------------------------------------------------------- */

#endif
