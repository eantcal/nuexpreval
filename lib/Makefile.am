lib_LIBRARIES = libnuexpreval.a

libnuexpreval_a_SOURCES = $(top_srcdir)/config.h \
nu_error_codes.cc \
nu_expr_compiler.cc \
nu_expr_function.cc \
nu_expr_subscrop.cc \
nu_expr_syntax_tree.cc \
nu_expr_tknzr.cc \
nu_expr_unary_op.cc \
nu_expr_var.cc \
nu_global_function_tbl.cc \
nu_lxa.cc \
nu_string_tool.cc \
nu_token_list.cc \
nu_variable.cc \
nu_variant.cc 

AM_CXXFLAGS = $(INTI_CFLAGS) -pthread -std=c++11 -I$(top_srcdir)/include

libnuexpreval_a_LIBADD = $(INTI_LIBS) 

