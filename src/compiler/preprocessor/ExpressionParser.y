/*
//
// Copyright (c) 2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

This file contains the Yacc grammar for GLSL ES preprocessor expression.

IF YOU MODIFY THIS FILE YOU ALSO NEED TO RUN generate_parser.sh,
WHICH GENERATES THE GLSL ES preprocessor expression parser.
*/

%{
//
// Copyright (c) 2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// This file is auto-generated by generate_parser.sh. DO NOT EDIT!

#if defined(__GNUC__)
// Triggered by the auto-generated pplval variable.
#if !defined(__clang__) && ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#else
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif
#elif defined(_MSC_VER)
#pragma warning(disable: 4065 4244 4701 4702)
#endif

#include "ExpressionParser.h"

#if defined(_MSC_VER)
#include <malloc.h>
#else
#include <stdlib.h>
#endif

#include <cassert>
#include <sstream>
#include <stdint.h>

#include "DiagnosticsBase.h"
#include "Lexer.h"
#include "Token.h"
#include "common/mathutil.h"

typedef int32_t YYSTYPE;
typedef uint32_t UNSIGNED_TYPE;

#define YYENABLE_NLS 0
#define YYLTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1

namespace {
struct Context
{
    pp::Diagnostics* diagnostics;
    pp::Lexer* lexer;
    pp::Token* token;
    int* result;
    bool parsePresetToken;

    pp::ExpressionParser::ErrorSettings errorSettings;
    bool *valid;

    void startIgnoreErrors() { ++ignoreErrors; }
    void endIgnoreErrors() { --ignoreErrors; }

    bool isIgnoringErrors() { return ignoreErrors > 0; }

    int ignoreErrors;
};
}  // namespace
%}

%pure-parser
%name-prefix "pp"
%parse-param {Context *context}
%lex-param {Context *context}

%{
static int yylex(YYSTYPE* lvalp, Context* context);
static void yyerror(Context* context, const char* reason);
%}

%token TOK_CONST_INT
%token TOK_IDENTIFIER
%left TOK_OP_OR
%left TOK_OP_AND
%left '|'
%left '^'
%left '&'
%left TOK_OP_EQ TOK_OP_NE
%left '<' '>' TOK_OP_LE TOK_OP_GE
%left TOK_OP_LEFT TOK_OP_RIGHT
%left '+' '-'
%left '*' '/' '%'
%right TOK_UNARY

%%

input
    : expression {
        *(context->result) = static_cast<int>($1);
        YYACCEPT;
    }
;

expression
    : TOK_CONST_INT
    | TOK_IDENTIFIER {
        if (!context->isIgnoringErrors())
        {
            // This rule should be applied right after the token is lexed, so we can
            // refer to context->token in the error message.
            context->diagnostics->report(context->errorSettings.unexpectedIdentifier,
                                         context->token->location, context->token->text);
            *(context->valid) = false;
        }
        $$ = $1;
    }
    | expression TOK_OP_OR {
        if ($1 != 0)
        {
            // Ignore errors in the short-circuited part of the expression.
            // ESSL3.00 section 3.4:
            // If an operand is not evaluated, the presence of undefined identifiers
            // in the operand will not cause an error.
            // Unevaluated division by zero should not cause an error either.
            context->startIgnoreErrors();
        }
    } expression {
        if ($1 != 0)
        {
            context->endIgnoreErrors();
            $$ = static_cast<YYSTYPE>(1);
        }
        else
        {
            $$ = $1 || $4;
        }
    }
    | expression TOK_OP_AND {
        if ($1 == 0)
        {
            // Ignore errors in the short-circuited part of the expression.
            // ESSL3.00 section 3.4:
            // If an operand is not evaluated, the presence of undefined identifiers
            // in the operand will not cause an error.
            // Unevaluated division by zero should not cause an error either.
            context->startIgnoreErrors();
        }
    } expression {
        if ($1 == 0)
        {
            context->endIgnoreErrors();
            $$ = static_cast<YYSTYPE>(0);
        }
        else
        {
            $$ = $1 && $4;
        }
    }
    | expression '|' expression {
        $$ = $1 | $3;
    }
    | expression '^' expression {
        $$ = $1 ^ $3;
    }
    | expression '&' expression {
        $$ = $1 & $3;
    }
    | expression TOK_OP_NE expression {
        $$ = $1 != $3;
    }
    | expression TOK_OP_EQ expression {
        $$ = $1 == $3;
    }
    | expression TOK_OP_GE expression {
        $$ = $1 >= $3;
    }
    | expression TOK_OP_LE expression {
        $$ = $1 <= $3;
    }
    | expression '>' expression {
        $$ = $1 > $3;
    }
    | expression '<' expression {
        $$ = $1 < $3;
    }
    | expression TOK_OP_RIGHT expression {
        if ($3 < 0 || $3 > 31)
        {
            if (!context->isIgnoringErrors())
            {
                std::ostringstream stream;
                stream << $1 << " >> " << $3;
                std::string text = stream.str();
                context->diagnostics->report(pp::Diagnostics::PP_UNDEFINED_SHIFT,
                                             context->token->location,
                                             text.c_str());
                *(context->valid) = false;
            }
            $$ = static_cast<YYSTYPE>(0);
        }
        else if ($1 < 0)
        {
            // Logical shift right.
            $$ = static_cast<YYSTYPE>(static_cast<UNSIGNED_TYPE>($1) >> $3);
        }
        else
        {
            $$ = $1 >> $3;
        }
    }
    | expression TOK_OP_LEFT expression {
        if ($3 < 0 || $3 > 31)
        {
            if (!context->isIgnoringErrors())
            {
                std::ostringstream stream;
                stream << $1 << " << " << $3;
                std::string text = stream.str();
                context->diagnostics->report(pp::Diagnostics::PP_UNDEFINED_SHIFT,
                                             context->token->location,
                                             text.c_str());
                *(context->valid) = false;
            }
            $$ = static_cast<YYSTYPE>(0);
        }
        else
        {
            // Logical shift left. Casting to unsigned is needed to ensure there's no signed integer
            // overflow, which some tools treat as an error.
            $$ = static_cast<YYSTYPE>(static_cast<UNSIGNED_TYPE>($1) << $3);
        }
    }
    | expression '-' expression {
        $$ = gl::WrappingDiff<YYSTYPE>($1, $3);
    }
    | expression '+' expression {
        $$ = gl::WrappingSum<YYSTYPE>($1, $3);
    }
    | expression '%' expression {
        if ($3 == 0)
        {
            if (!context->isIgnoringErrors())
            {
                std::ostringstream stream;
                stream << $1 << " % " << $3;
                std::string text = stream.str();
                context->diagnostics->report(pp::Diagnostics::PP_DIVISION_BY_ZERO,
                                             context->token->location,
                                             text.c_str());
                *(context->valid) = false;
            }
            $$ = static_cast<YYSTYPE>(0);
        }
        else if (($1 == std::numeric_limits<YYSTYPE>::min()) && ($3 == -1))
        {
            // Check for the special case where the minimum representable number is
            // divided by -1. If left alone this has undefined results.
            $$ = 0;
        }
        else
        {
            $$ = $1 % $3;
        }
    }
    | expression '/' expression {
        if ($3 == 0)
        {
            if (!context->isIgnoringErrors())
            {
                std::ostringstream stream;
                stream << $1 << " / " << $3;
                std::string text = stream.str();
                context->diagnostics->report(pp::Diagnostics::PP_DIVISION_BY_ZERO,
                                            context->token->location,
                                            text.c_str());
                *(context->valid) = false;
            }
            $$ = static_cast<YYSTYPE>(0);
        }
        else if (($1 == std::numeric_limits<YYSTYPE>::min()) && ($3 == -1))
        {
            // Check for the special case where the minimum representable number is
            // divided by -1. If left alone this leads to integer overflow in C++, which
            // has undefined results.
            $$ = std::numeric_limits<YYSTYPE>::max();
        }
        else
        {
            $$ = $1 / $3;
        }
    }
    | expression '*' expression {
        $$ = gl::WrappingMul($1, $3);
    }
    | '!' expression %prec TOK_UNARY {
        $$ = ! $2;
    }
    | '~' expression %prec TOK_UNARY {
        $$ = ~ $2;
    }
    | '-' expression %prec TOK_UNARY {
        // Check for negation of minimum representable integer to prevent undefined signed int
        // overflow.
        if ($2 == std::numeric_limits<YYSTYPE>::min())
        {
            $$ = std::numeric_limits<YYSTYPE>::min();
        }
        else
        {
            $$ = -$2;
        }
    }
    | '+' expression %prec TOK_UNARY {
        $$ = + $2;
    }
    | '(' expression ')' {
        $$ = $2;
    }
;

%%

int yylex(YYSTYPE *lvalp, Context *context)
{
    pp::Token *token = context->token;
    if (!context->parsePresetToken)
    {
        context->lexer->lex(token);
    }
    context->parsePresetToken = false;

    int type = 0;

    switch (token->type)
    {
      case pp::Token::CONST_INT: {
        unsigned int val = 0;
        int testVal = 0;
        if (!token->uValue(&val) || (!token->iValue(&testVal) &&
                                     context->errorSettings.integerLiteralsMustFit32BitSignedRange))
        {
            context->diagnostics->report(pp::Diagnostics::PP_INTEGER_OVERFLOW,
                                         token->location, token->text);
            *(context->valid) = false;
        }
        *lvalp = static_cast<YYSTYPE>(val);
        type = TOK_CONST_INT;
        break;
      }
      case pp::Token::IDENTIFIER:
        *lvalp = static_cast<YYSTYPE>(-1);
        type = TOK_IDENTIFIER;
        break;
      case pp::Token::OP_OR:
        type = TOK_OP_OR;
        break;
      case pp::Token::OP_AND:
        type = TOK_OP_AND;
        break;
      case pp::Token::OP_NE:
        type = TOK_OP_NE;
        break;
      case pp::Token::OP_EQ:
        type = TOK_OP_EQ;
        break;
      case pp::Token::OP_GE:
        type = TOK_OP_GE;
        break;
      case pp::Token::OP_LE:
        type = TOK_OP_LE;
        break;
      case pp::Token::OP_RIGHT:
        type = TOK_OP_RIGHT;
        break;
      case pp::Token::OP_LEFT:
        type = TOK_OP_LEFT;
        break;
      case '|':
      case '^':
      case '&':
      case '>':
      case '<':
      case '-':
      case '+':
      case '%':
      case '/':
      case '*':
      case '!':
      case '~':
      case '(':
      case ')':
        type = token->type;
        break;

      default:
        break;
    }

    return type;
}

void yyerror(Context *context, const char *reason)
{
    context->diagnostics->report(pp::Diagnostics::PP_INVALID_EXPRESSION,
                                 context->token->location,
                                 reason);
}

namespace pp {

ExpressionParser::ExpressionParser(Lexer *lexer, Diagnostics *diagnostics)
    : mLexer(lexer),
      mDiagnostics(diagnostics)
{
}

bool ExpressionParser::parse(Token *token,
                             int *result,
                             bool parsePresetToken,
                             const ErrorSettings &errorSettings,
                             bool *valid)
{
    Context context;
    context.diagnostics = mDiagnostics;
    context.lexer = mLexer;
    context.token = token;
    context.result = result;
    context.ignoreErrors = 0;
    context.parsePresetToken = parsePresetToken;
    context.errorSettings    = errorSettings;
    context.valid            = valid;
    int ret = yyparse(&context);
    switch (ret)
    {
      case 0:
      case 1:
        break;

      case 2:
        mDiagnostics->report(Diagnostics::PP_OUT_OF_MEMORY, token->location, "");
        break;

      default:
        assert(false);
        mDiagnostics->report(Diagnostics::PP_INTERNAL_ERROR, token->location, "");
        break;
    }

    return ret == 0;
}

}  // namespace pp
