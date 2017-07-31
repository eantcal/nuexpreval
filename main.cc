//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#include "nu_expr_eval.h"
#include <iostream>
#include <sstream>
#include <string>


/* -------------------------------------------------------------------------- */

int main(int argc, char* argv[])
{
    if (argc<2) {
        std::cerr << argv[0] << "mathexpr" << std::endl;
        return 1;
    }

    std::stringstream ss;

    for (int i=1; i<argc; ++i) 
        ss << argv[i];

    std::string s_expr = ss.str();

    nu::tokenizer_t st(s_expr);
    nu::expr_compiler_t ep;

    auto expr = ep.compile(st);

    try {
        nu::ctx_t ctx;
        auto result = expr->eval(ctx);
        std::cout << result.to_str() << std::endl;
    }
    catch (nu::runtime_error_t& e) {
        std::cerr << e.get_error_code() << " - " << e.what() << std::endl;
        return e.get_error_code();
    }
    catch (nu::exception_t& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

