//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#ifndef __NU_EXPREVAL_DEFS_H__
#define __NU_EXPREVAL_DEFS_H__


/* -------------------------------------------------------------------------- */

// Scanner config. data
#define NU_EXPREVAL_BLANKS " \t\r"
#define NU_EXPREVAL_NEWLINES "\n"

#define NU_EXPREVAL_OP_INC "++"
#define NU_EXPREVAL_OP_DEC "--"

#define NU_EXPREVAL_BEGIN_SUBEXPR '('
#define NU_EXPREVAL_END_SUBEXPR ')'
#define NU_EXPREVAL_BEGIN_STRING "\""
#define NU_EXPREVAL_END_STRING "\""
#define NU_EXPREVAL_ESCAPE_CHAR '\\'
#define NU_EXPREVAL_BEGIN_SUBSCR '['
#define NU_EXPREVAL_END_SUBSCR ']'

#define NU_EXPREVAL_PARAM_SEP ","

#define NU_EXPREVAL_EXPONENT_SYMB 'E'

#define NU_EXPREVAL_BEGIN_SUBEXPR_OP "("
#define NU_EXPREVAL_END_SUBEXPR_OP ")"
#define NU_EXPREVAL_BEGIN_SUBSCR_OP "["
#define NU_EXPREVAL_END_SUBSCR_OP "]"

#define NU_EXPREVAL_SINGLE_CHAR_OPS ".+-*/^,\\=\";:<>?'"
#define NU_EXPREVAL_WORD_OPS                                                      \
    {                                                                          \
        "bxor", "band", "bshr", "bshl", "bor", NU_EXPREVAL_OP_INC,                \
            NU_EXPREVAL_OP_DEC, "mod", "div", "xor", "and", "or", "<>", "<=",     \
            ">="                                                               \
    }
#define NU_EXPREVAL_BEGIN_SUBEXPR '('
#define NU_EXPREVAL_END_SUBEXPR ')'
#define NU_EXPREVAL_BEGIN_STRING "\""
#define NU_EXPREVAL_END_STRING "\""
#define NU_EXPREVAL_ESCAPE_CHAR '\\'

#define NU_EXPREVAL_LINE_COMMENT { "'" }


/* -------------------------------------------------------------------------- */

// Error strings
#define NU_EXPREVAL_ERROR_STR__SYNTAXERROR "Syntax Error"
#define NU_EXPREVAL_ERROR_STR__ERRORLOADING "Error loading file or file not found"


/* -------------------------------------------------------------------------- */

#endif
