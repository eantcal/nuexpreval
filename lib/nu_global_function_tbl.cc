//  
// This file is part of nuExprEval
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//

/* -------------------------------------------------------------------------- */

#include "nu_global_function_tbl.h"
#include "nu_basic_defs.h"
#include "nu_expr_var.h"
#include "nu_variant.h"
#include "nu_expr_eval.h"

#include <cstdlib>
#include <ctime>
#include <functional>
#include <stdlib.h>
#include <string>
#include <math.h>


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

global_function_tbl_t* global_function_tbl_t::_instance = nullptr;
global_operator_tbl_t* global_operator_tbl_t::_instance = nullptr;


/* -------------------------------------------------------------------------- */

inline static void check_arg_num(
    const nu::func_args_t& args, int expected_arg_num, const std::string& fname)
{
    std::string error = "'" + fname + "': expects to be passed "
        + nu::to_string(expected_arg_num) + " argument(s)";

    switch (expected_arg_num) {
    case 0:
        error = "'" + fname + "': expects to be passed no arguments";
        break;

    case 1:
        error = "'" + fname + "': expects to be passed one argument";
        break;
    }

    bool valid_args = (expected_arg_num == 0 && args.size() == 0)
        || (expected_arg_num == 0 && args.size() == 1 && args[0]->empty())
        || (expected_arg_num == 1 && args.size() == 1 && !args[0]->empty())
        || (expected_arg_num > 1 && int(args.size()) == expected_arg_num);

    syntax_error_if(!valid_args, error);
}


/* -------------------------------------------------------------------------- */

void get_functor_vargs(ctx_t& ctx, const std::string& name,
    const nu::func_args_t& args,
    const std::vector<variant_t::type_t>& check_vect,
    std::vector<variant_t>& vargs)
{
    check_arg_num(args, int(check_vect.size()), name);

    for (auto& arg : args)
        vargs.push_back(arg->eval(ctx));

    int i = 0;

    for (auto& vargt : check_vect) {
        bool invalid_check = true;

        if (vargt == variant_t::type_t::UNDEFINED) {
            // Do not care about this argument
            continue;
        }

        // Accept implicit conversion from/to types double/float/int
        if (variable_t::is_number(vargt)
            && variable_t::is_number(vargs[i].get_type())) {
            invalid_check = false;
        } else {
            invalid_check = vargs[i].get_type() != vargt;
        }

        syntax_error_if(invalid_check, "'" + name
                + "': expects to be passed argument " + nu::to_string(i + 1)
                + " as " + variant_t::get_type_desc(vargt));

        ++i;
    }
}


/* -------------------------------------------------------------------------- */

// RT F()(T arg)
template <class F, typename RT, typename T>
variant_t functor_RT_T(ctx_t& ctx, const std::string& name,
    const nu::func_args_t& args, variant_t::type_t argt)
{
    std::vector<variant_t::type_t> check_vect = { argt };
    std::vector<variant_t> vargs;
    get_functor_vargs(ctx, name, args, check_vect, vargs);

    auto arg = static_cast<T>(vargs[0]);

    return nu::variant_t(RT(F()(arg)));
}


/* -------------------------------------------------------------------------- */

// RT F()(T1 arg1, T2 arg2)
template <class F, typename RT, typename T1, typename T2>
variant_t functor_RT_T1_T2(ctx_t& ctx, const std::string& name,
    const nu::func_args_t& args, variant_t::type_t argt1,
    variant_t::type_t argt2)
{
    std::vector<variant_t::type_t> check_vect = { argt1, argt2 };
    std::vector<variant_t> vargs;
    get_functor_vargs(ctx, name, args, check_vect, vargs);

    auto arg1 = static_cast<T1>(vargs[0]);
    auto arg2 = static_cast<T2>(vargs[1]);

    return nu::variant_t(RT(F()(arg1, arg2)));
}


/* -------------------------------------------------------------------------- */

// RT F()(T1 arg1, T2 arg2, T3 arg3)
template <class F, typename RT, typename T1, typename T2, typename T3>
variant_t functor_RT_T1_T2_T3(ctx_t& ctx, const std::string& name,
    const nu::func_args_t& args, variant_t::type_t argt1,
    variant_t::type_t argt2, variant_t::type_t argt3)
{
    std::vector<variant_t::type_t> check_vect = { argt1, argt2, argt3 };
    std::vector<variant_t> vargs;
    get_functor_vargs(ctx, name, args, check_vect, vargs);

    auto arg1 = static_cast<T1>(vargs[0]);
    auto arg2 = static_cast<T2>(vargs[1]);
    auto arg3 = static_cast<T3>(vargs[2]);

    return nu::variant_t(RT(F()(arg1, arg2, arg3)));
}


/* -------------------------------------------------------------------------- */

// RT F()(T1 arg1, T2 arg2, T3 arg3)
template <class F, typename RT, typename T1, typename T2, typename T3,
    typename T4>
variant_t functor_RT_T1_T2_T3_T4(ctx_t& ctx, const std::string& name,
    const nu::func_args_t& args, variant_t::type_t argt1,
    variant_t::type_t argt2, variant_t::type_t argt3, variant_t::type_t argt4)
{
    std::vector<variant_t::type_t> check_vect = { argt1, argt2, argt3, argt4 };
    std::vector<variant_t> vargs;
    get_functor_vargs(ctx, name, args, check_vect, vargs);

    auto arg1 = static_cast<T1>(vargs[0]);
    auto arg2 = static_cast<T2>(vargs[1]);
    auto arg3 = static_cast<T3>(vargs[2]);
    auto arg4 = static_cast<T3>(vargs[3]);

    return nu::variant_t(RT(F()(arg1, arg2, arg3, arg4)));
}


/* -------------------------------------------------------------------------- */

// int F()(float)
template <class F>
variant_t functor_int_int(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T<F, int, int>(
        ctx, name, args, variant_t::type_t::INTEGER);
}

/* -------------------------------------------------------------------------- */

// int F()(float)
template <class F>
variant_t functor_int_float(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T<F, int, float>(
        ctx, name, args, variant_t::type_t::FLOAT);
}


/* -------------------------------------------------------------------------- */

// int F()(double)
template <class F>
variant_t functor_int_double(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T<F, int, double>(
        ctx, name, args, variant_t::type_t::DOUBLE);
}


/* -------------------------------------------------------------------------- */

// int F()(string)
template <class F>
variant_t functor_int_string(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T<F, int, std::string>(
        ctx, name, args, variant_t::type_t::STRING);
}


/* -------------------------------------------------------------------------- */

// string F()(int)
template <class F>
variant_t functor_string_int(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T<F, std::string, int>(
        ctx, name, args, variant_t::type_t::INTEGER);
}


/* -------------------------------------------------------------------------- */

// string F()(float)
template <class F>
variant_t functor_string_float(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T<F, std::string, float>(
        ctx, name, args, variant_t::type_t::FLOAT);
}


/* -------------------------------------------------------------------------- */

// string F()(double)
template <class F>
variant_t functor_string_double(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T<F, std::string, double>(
        ctx, name, args, variant_t::type_t::DOUBLE);
}


/* -------------------------------------------------------------------------- */

// string F()(string)
template <class F>
variant_t functor_string_string(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T<F, std::string, std::string>(
        ctx, name, args, variant_t::type_t::STRING);
}


/* -------------------------------------------------------------------------- */

// float F()(string)
template <class F>
variant_t functor_float_string(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T<F, float, std::string>(
        ctx, name, args, variant_t::type_t::STRING);
}


/* -------------------------------------------------------------------------- */

// double F()(string)
template <class F>
variant_t functor_double_string(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T<F, double, std::string>(
        ctx, name, args, variant_t::type_t::STRING);
}


/* -------------------------------------------------------------------------- */

// string F()(string, int)
template <class F>
variant_t functor_string_string_int(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T1_T2<F, std::string, std::string, int>(
        ctx, name, args, variant_t::type_t::STRING, variant_t::type_t::INTEGER);
}


/* -------------------------------------------------------------------------- */

// string F()(double, int)
template <class F>
variant_t functor_string_double_int(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T1_T2<F, std::string, double, int>(
        ctx, name, args, variant_t::type_t::DOUBLE, variant_t::type_t::INTEGER);
}


/* -------------------------------------------------------------------------- */

// int F()(string, string)
template <class F>
variant_t functor_int_string_string(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T1_T2<F, int, std::string, std::string>(
        ctx, name, args, variant_t::type_t::STRING, variant_t::type_t::STRING);
}


/* -------------------------------------------------------------------------- */

// string F()(string, int, int)
template <class F>
variant_t functor_string_string_int_int(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T1_T2_T3<F, std::string, std::string, int, int>(ctx, name,
        args, variant_t::type_t::STRING, variant_t::type_t::INTEGER,
        variant_t::type_t::INTEGER);
}


/* -------------------------------------------------------------------------- */

// string F()(string, int, string)
template <class F>
variant_t functor_string_string_int_string(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return functor_RT_T1_T2_T3<F, std::string, std::string, int, std::string>(
        ctx, name, args, variant_t::type_t::STRING, variant_t::type_t::INTEGER,
        variant_t::type_t::STRING);
}

/* -------------------------------------------------------------------------- */

// T F()(T) where T is int
template <class T, class F>
variant_t math_functor_aux(ctx_t& ctx, const std::string& name,
    const nu::func_args_t& args, std::true_type)
{
    return functor_RT_T<F, T, T>(
        ctx, name, args, { variant_t::type_t::INTEGER });
}


/* -------------------------------------------------------------------------- */

// T F()(T) where T is double
template <class T, class F>
variant_t math_functor_aux(ctx_t& ctx, const std::string& name,
    const nu::func_args_t& args, std::false_type)
{
    return functor_RT_T<F, T, T>(
        ctx, name, args, { variant_t::type_t::DOUBLE });
}


/* -------------------------------------------------------------------------- */

// T F()(T) where T might be either float or int
template <class T, class F>
variant_t math_functor(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    return math_functor_aux<T, F>(ctx, name, args, std::is_integral<T>());
}


/* -------------------------------------------------------------------------- */

// T F()(T,T) where T might be either float or int
template <class T, class F>
variant_t math_functor2(
    ctx_t& ctx, const std::string& name, const nu::func_args_t& args)
{
    if (std::is_integral<T>::value) {
        return functor_RT_T1_T2<F, T, T, T>(ctx, name, args,
            variant_t::type_t::INTEGER, variant_t::type_t::INTEGER);
    }

    return functor_RT_T1_T2<F, T, T, T>(
        ctx, name, args, variant_t::type_t::DOUBLE, variant_t::type_t::DOUBLE);
}


/* -------------------------------------------------------------------------- */

static variant_t process_operator(ctx_t& ctx,
    const std::string& operator_name, const nu::func_args_t& args)
{
    rt_error_code_t::get_instance().throw_if(
        args.size() != 1, rt_error_code_t::E_INVALID_ARGS);


    auto var = args[0];
    auto var_ptr = dynamic_cast<expr_var_t*>(var.get());

    rt_error_code_t::get_instance().throw_if(
        var_ptr == nullptr, rt_error_code_t::E_INVALID_ARGS);

    const auto variable_name = var_ptr->name();

    rt_error_code_t::get_instance().throw_if(!
        ctx.is_defined(variable_name),
        rt_error_code_t::E_INV_IDENTIF);

    auto variable_value = &(ctx)[variable_name];

    if (operator_name == NU_EXPREVAL_OP_INC) {
        variable_value->increment();
    } else if (operator_name == NU_EXPREVAL_OP_DEC) {
        variable_value->decrement();
    } else {
        rt_error_code_t::get_instance().throw_if(
            true, rt_error_code_t::E_FUNC_UNDEF);
    }

    return *variable_value;
}


/* -------------------------------------------------------------------------- */

global_function_tbl_t& global_function_tbl_t::get_instance()
{
    if (!_instance) {
        _instance = new global_function_tbl_t();
        assert(_instance);

        global_function_tbl_t& fmap = *_instance;

/*

__FUNCTOR_BUILDER(sin)

===>

struct _sin { float operator()(float x) noexcept { return ::sin(x); } };
fmap["sin"] = functor<float, _sin>;

*/


#ifdef __FUNCTOR_BUILDER
#warning "__FUNCTOR_BUILDER already defined..."
#undef __FUNCTOR_BUILDER
#endif

#define __FUNCTOR_BUILDER(_FNC_)                                               \
    struct _##_FNC_ {                                                          \
        float operator()(float x) noexcept { return _FNC_(x); }                \
    };                                                                         \
    fmap[#_FNC_] = math_functor<float, _##_FNC_>;

        __FUNCTOR_BUILDER(truncf);

#ifdef __DOUBLE_FUNCTOR_BUILDER
#warning "__FUNCTOR_BUILDER already defined..."
#undef __DOUBLE_FUNCTOR_BUILDER
#endif


#define __DOUBLE_FUNCTOR_BUILDER(_FNC_)                                        \
    struct _##_FNC_ {                                                          \
        double operator()(double x) noexcept { return _FNC_(x); }              \
    };                                                                         \
    fmap[#_FNC_] = math_functor<double, _##_FNC_>;

        __DOUBLE_FUNCTOR_BUILDER(sin);
        __DOUBLE_FUNCTOR_BUILDER(cos);
        __DOUBLE_FUNCTOR_BUILDER(tan);
        __DOUBLE_FUNCTOR_BUILDER(log);
        __DOUBLE_FUNCTOR_BUILDER(log10);
        __DOUBLE_FUNCTOR_BUILDER(exp);
        __DOUBLE_FUNCTOR_BUILDER(abs);
        __DOUBLE_FUNCTOR_BUILDER(asin);
        __DOUBLE_FUNCTOR_BUILDER(acos);
        __DOUBLE_FUNCTOR_BUILDER(atan);
        __DOUBLE_FUNCTOR_BUILDER(sinh);
        __DOUBLE_FUNCTOR_BUILDER(cosh);
        __DOUBLE_FUNCTOR_BUILDER(tanh);
        __DOUBLE_FUNCTOR_BUILDER(sqrt);


        struct _sign {
            double operator()(double x) noexcept {
                return x > 0.0F ? 1.0F : (x == 0.0F ? 0.0F : -1.0F);
            }
        };


        fmap["sign"] = math_functor<double, _sign>;


        struct _min {
            double operator()(double x, double y) noexcept {
                return x < y ? x : y;
            }
        };


        fmap["min"] = math_functor2<double, _min>;


        struct _max {
            double operator()(double x, double y) noexcept {
                return x > y ? x : y;
            }
        };


        fmap["max"] = math_functor2<double, _max>;


        struct _pow {
            double operator()(double x, double y) noexcept {
                return ::pow(x, y);
            }
        };


        fmap["pow"] = math_functor2<double, _pow>;


        struct _int_truncate {
            int operator()(double x) noexcept {
                // Truncate to greatest integer less or equal to Argument
                // Example:
                // int(-5) => -5
                // int(-5.1) => -6
                // int(5.9) => 5
                return int((x < 0.0F)
                        ? int((abs(x)) - int(abs(x)) > 0.0F ? int(x) - 1
                                                            : int(x))
                        : int(x));
            }
        };

        // Truncate to greatest integer less or equal to Argument
        fmap["int"] = functor_int_double<_int_truncate>;


        // sqr is an alias of sqrt
        fmap["sqr"] = math_functor<double, _sqrt>;


        struct _rnd {
            double operator()(double x) noexcept {
                if (x < 0.0F) {
                    // Seed the random-number generator with the
                    // current time so that the numbers will be
                    // different every time we run.
                    ::srand((unsigned)time(NULL));
                    ::rand();
                }

                return double(::rand()) / RAND_MAX;
            }
        };

        /*
            RND - Random Number in [0.0 .. 1.0]
        Syntax:
            RND(<Seed>)
        If (<Seed> < 0) the Random number generator is initialized
            Examples:
                RND(-625) -> 3.85114436E-06
                RND(0) -> 0.464844882
                RND(0) -> 0.0156260729
        */

        fmap["rnd"] = math_functor<double, _rnd>;


        struct _boolean_not {
            int operator()(double x) noexcept {
                return int((x == 0.0F) ? 1 : 0);
            }
        };

        fmap["not"] = functor_int_double<_boolean_not>;


        struct _bitwise_not {
            int operator()(int x) noexcept { return ~x; }
        };

        fmap["b_not"] = math_functor<int, _bitwise_not>;


        struct _len_str {
            int operator()(const std::string x) noexcept
            {
                return int(x.size());
            }
        };

        fmap["len"] = functor_int_string<_len_str>;


        struct _asc_str {
            int operator()(const std::string x) noexcept
            {
                return (x.empty() ? 0 : x.c_str()[0]) & 0xff;
            }
        };

        fmap["asc"] = functor_int_string<_asc_str>;


        struct _space_str {
            std::string operator()(int nspace) noexcept
            {
                std::string s;
                nspace = nspace < 0 ? 0 : nspace;

                for (int i = 0; i < nspace; ++i)
                    s += " ";

                return s;
            }
        };

        // functor_string_int
        fmap["spc"] = functor_string_int<_space_str>;


        struct _chr_str {
            std::string operator()(int code) noexcept
            {
                char s[2] = { 0 };
                s[0] = code;
                return s;
            }
        };

        fmap["chr"] = functor_string_int<_chr_str>;


        struct _left_str {
            std::string operator()(const std::string& s, int n) noexcept
            {
                if (n <= 0)
                    return std::string();
                else if (n > int(s.size()))
                    n = int(s.size());

                return s.substr(0, n);
            }
        };

        fmap["left"] = functor_string_string_int<_left_str>;


        struct _lcase_str {
            std::string operator()(const std::string& s) noexcept
            {
                std::string ret = s;
                std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
                return ret;
            }
        };

        fmap["lcase"] = functor_string_string<_lcase_str>;


        struct _ucase_str {
            std::string operator()(const std::string& s) noexcept
            {
                std::string ret = s;
                std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
                return ret;
            }
        };

        fmap["ucase"] = functor_string_string<_ucase_str>;


        // Built-in unary operators

        fmap[NU_EXPREVAL_OP_INC] = process_operator;
        fmap[NU_EXPREVAL_OP_DEC] = process_operator;


        struct _right_str {
            std::string operator()(const std::string& s, int n) noexcept
            {
                if (n <= 0)
                    return s;
                else if (n > int(s.size()))
                    n = int(s.size());

                int skip = int(s.size()) - n;

                return s.substr(skip, n);
            }
        };

        fmap["right"] = functor_string_string_int<_right_str>;


        struct _instrcs {
            int operator()(
                const std::string& s, const std::string& search_str) noexcept  {
                if (search_str.empty())
                    return 0;
                else if (s.empty() || search_str.size() > s.size())
                    return -1;
                else if (search_str.size() == s.size() && s == search_str)
                    return 0;

                std::string mystr = s;
                int pos = 0;

                while (search_str.size() <= mystr.size()) {
                    if (mystr.substr(0, search_str.size()) == search_str)
                        return pos;

                    ++pos;
                    mystr = mystr.substr(1, mystr.size() - 1);
                }

                return -1;
            }
        };

        fmap["instrcs"] = functor_int_string_string<_instrcs>;


        struct _instr : public _instrcs {
            int operator()(
                const std::string& s, const std::string& search_str) noexcept {
                std::string mys = s;
                std::string ss = search_str;
                std::transform(mys.begin(), mys.end(), mys.begin(), toupper);
                std::transform(ss.begin(), ss.end(), ss.begin(), toupper);

                return _instrcs::operator()(mys, ss);
            }
        };

        fmap["instr"] = functor_int_string_string<_instr>;


        struct _sub_str {
            // SUBSTR(s$,pos,n)
            // return a string of n characters from s$ beginning
            // with the pos-th character (0 is first character)
            // Comment: pos >= 0, n >= 0

            std::string operator()(
                const std::string& s, int pos, int n) noexcept {
                if (pos < 1)
                    pos = 0;

                if (pos >= int(s.size()))
                    return std::string();

                if (n < 0)
                    n = 0;

                if ((pos + n) >= int(s.size()))
                    n = int(s.size()) - pos;

                return s.substr(pos, n);
            }
        };


        fmap["substr"] = functor_string_string_int_int<_sub_str>;


        struct _mid_str {
            // MID(s$,pos,n)
            // return a string of n characters from s$ beginning
            // with the pos-th character (1 is first character)
            // Comment: pos >= 1, n >= 0

            std::string operator()(
                const std::string& s, int pos, int n) noexcept {
                --pos;

                if (pos < 1)
                    pos = 0;

                if (pos >= int(s.size()))
                    return std::string();

                if (n < 0)
                    n = 0;

                if ((pos + n) >= int(s.size()))
                    n = int(s.size()) - pos;

                return s.substr(pos, n);
            }
        };


        fmap["mid"] = functor_string_string_int_int<_mid_str>;


        struct _patch_str {
            // PSTR(s$,pos,c)
            // return a string s$ with the pos-th character replaced by c
            // with pos >= 0

            std::string operator()(
                const std::string& s, int pos, const std::string& c_s) noexcept
            {

                if (pos >= int(s.size())) {
                    pos = int(s.size() - 1);
                }

                if (pos < 1) {
                    pos = 0;
                }


                std::string ret = s;

                char c = c_s.empty() ? '\0' : c_s[0];

                ret[pos] = c;

                return ret;
            }
        };

        fmap["pstr"] = functor_string_string_int_string<_patch_str>;


        struct _val_str {
            double operator()(const std::string& x) noexcept {
                try {
                    return nu::stod(x);
                }

                catch (...) {
                    return 0.0;
                }
            }
        };


        fmap["val"] = functor_double_string<_val_str>;


        struct _to_str {
            std::string operator()(double x) noexcept
            {
                if (::floor(x) == x) {
                    return to_string(int(x));
                }

                return to_string(x);
            }
        };


        fmap["str"] = functor_string_double<_to_str>;


        struct _to_str_precision {
            std::string operator()(double x, int digits) noexcept
            {
                char buffer[1024] = { 0 };
                std::string format = "%." + std::to_string(abs(digits)) + "f";
                snprintf(buffer, sizeof(buffer) - 1, format.c_str(), x);

                return buffer;
            }
        };

        fmap["strp"] = functor_string_double_int<_to_str_precision>;


        struct _to_hex_str {
            std::string operator()(double x) noexcept
            {
                std::stringstream ss;
                ss << std::hex << int(x);
                return ss.str();
            }
        };

        fmap["hex"] = functor_string_double<_to_hex_str>;


        auto functor_pi = [](ctx_t& ctx, const std::string& name,
            const nu::func_args_t& args) {
            check_arg_num(args, 0, name);
            return nu::variant_t(3.1415926535897F);
        };

        fmap["pi"] = functor_pi;


        auto functor_sizeof = [](ctx_t& ctx, const std::string& name,
            const nu::func_args_t& args) {
            std::vector<variant_t> vargs;
            get_functor_vargs(
                ctx, name, args, { variant_t::type_t::UNDEFINED }, vargs);

            return nu::variant_t(integer_t(vargs[0].vector_size()));
        };


        fmap["size"] = functor_sizeof;
    }


    return *_instance;
}


/* -------------------------------------------------------------------------- */

global_operator_tbl_t& global_operator_tbl_t::get_instance()
{
    if (!_instance) {
        _instance = new global_operator_tbl_t();
        assert(_instance);

        global_operator_tbl_t& opmap = *_instance;
        using arg_t = const variant_t&;

        opmap["mod"] = [](arg_t a, arg_t b) { return a.int_mod(b); };
        opmap["div"] = [](arg_t a, arg_t b) { return a.int_div(b); };
        opmap["<="] = [](arg_t a, arg_t b) { return a <= b; };
        opmap[">="] = [](arg_t a, arg_t b) { return a >= b; };
        opmap["="] = [](arg_t a, arg_t b) { return a == b; };
        opmap["<>"] = [](arg_t a, arg_t b) { return a != b; };
        opmap["<"] = [](arg_t a, arg_t b) { return a < b; };
        opmap[">"] = [](arg_t a, arg_t b) { return a > b; };
        opmap["+"] = [](arg_t a, arg_t b) { return a + b; };
        opmap["-"] = [](arg_t a, arg_t b) { return a - b; };
        opmap["/"] = [](arg_t a, arg_t b) { return a / b; };
        opmap["*"] = [](arg_t a, arg_t b) { return a * b; };
        opmap["^"] = [](arg_t a, arg_t b) { return a.power(b); };
        opmap["\\"] = [](arg_t a, arg_t b) { return a.int_div(b); };
        opmap["and"] = [](arg_t a, arg_t b) { return a && b; };
        opmap["or"] = [](arg_t a, arg_t b) { return a || b; };
        opmap["xor"] = [](arg_t a, arg_t b) { return a != b; };

        opmap["bor"] = [](arg_t a, arg_t b) { return a.to_int() | b.to_int(); };
        opmap["band"]
            = [](arg_t a, arg_t b) { return a.to_int() & b.to_int(); };
        opmap["bxor"]
            = [](arg_t a, arg_t b) { return a.to_int() ^ b.to_int(); };
        opmap["bshr"]
            = [](arg_t a, arg_t b) { return a.to_int() >> b.to_int(); };
        opmap["bshl"]
            = [](arg_t a, arg_t b) { return a.to_int() << b.to_int(); };
    }

    return *_instance;
}


/* -------------------------------------------------------------------------- */

} // nu
