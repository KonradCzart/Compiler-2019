// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "parser.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.tab.hh"

// User implementation prologue.

#line 51 "parser.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 18 "parser.yy" // lalr1.cc:413

   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   #include "driver.hpp"

#undef yylex
#define yylex scanner.yylex

#line 64 "parser.tab.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "parser.yy" // lalr1.cc:479
namespace Compiler {
#line 150 "parser.tab.cc" // lalr1.cc:479

  /// Build a parser object.
  Parser::Parser (Scanner  &scanner_yyarg, CompilerDriver  &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 3: // NUM
      case 4: // PIDENTIFIER
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 3: // NUM
      case 4: // PIDENTIFIER
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 3: // NUM
      case 4: // PIDENTIFIER
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 3: // NUM
      case 4: // PIDENTIFIER
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }
  // Implementation of make_symbol for each symbol type.
  Parser::symbol_type
  Parser::make_ENDSCANN (const location_type& l)
  {
    return symbol_type (token::ENDSCANN, l);
  }

  Parser::symbol_type
  Parser::make_NUM (const std::string& v, const location_type& l)
  {
    return symbol_type (token::NUM, v, l);
  }

  Parser::symbol_type
  Parser::make_PIDENTIFIER (const std::string& v, const location_type& l)
  {
    return symbol_type (token::PIDENTIFIER, v, l);
  }

  Parser::symbol_type
  Parser::make_ERROR (const location_type& l)
  {
    return symbol_type (token::ERROR, l);
  }

  Parser::symbol_type
  Parser::make_SEMICOLON (const location_type& l)
  {
    return symbol_type (token::SEMICOLON, l);
  }

  Parser::symbol_type
  Parser::make_COLON (const location_type& l)
  {
    return symbol_type (token::COLON, l);
  }

  Parser::symbol_type
  Parser::make_LBR (const location_type& l)
  {
    return symbol_type (token::LBR, l);
  }

  Parser::symbol_type
  Parser::make_RBR (const location_type& l)
  {
    return symbol_type (token::RBR, l);
  }

  Parser::symbol_type
  Parser::make_ASSIGN (const location_type& l)
  {
    return symbol_type (token::ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_EQUAL (const location_type& l)
  {
    return symbol_type (token::EQUAL, l);
  }

  Parser::symbol_type
  Parser::make_NEQUAL (const location_type& l)
  {
    return symbol_type (token::NEQUAL, l);
  }

  Parser::symbol_type
  Parser::make_LESS (const location_type& l)
  {
    return symbol_type (token::LESS, l);
  }

  Parser::symbol_type
  Parser::make_GREAT (const location_type& l)
  {
    return symbol_type (token::GREAT, l);
  }

  Parser::symbol_type
  Parser::make_LESSEQ (const location_type& l)
  {
    return symbol_type (token::LESSEQ, l);
  }

  Parser::symbol_type
  Parser::make_GREATEQ (const location_type& l)
  {
    return symbol_type (token::GREATEQ, l);
  }

  Parser::symbol_type
  Parser::make_DECLARE (const location_type& l)
  {
    return symbol_type (token::DECLARE, l);
  }

  Parser::symbol_type
  Parser::make_IN (const location_type& l)
  {
    return symbol_type (token::IN, l);
  }

  Parser::symbol_type
  Parser::make_IF (const location_type& l)
  {
    return symbol_type (token::IF, l);
  }

  Parser::symbol_type
  Parser::make_THEN (const location_type& l)
  {
    return symbol_type (token::THEN, l);
  }

  Parser::symbol_type
  Parser::make_ELSE (const location_type& l)
  {
    return symbol_type (token::ELSE, l);
  }

  Parser::symbol_type
  Parser::make_ENDIF (const location_type& l)
  {
    return symbol_type (token::ENDIF, l);
  }

  Parser::symbol_type
  Parser::make_WHILE (const location_type& l)
  {
    return symbol_type (token::WHILE, l);
  }

  Parser::symbol_type
  Parser::make_DO (const location_type& l)
  {
    return symbol_type (token::DO, l);
  }

  Parser::symbol_type
  Parser::make_ENDWHILE (const location_type& l)
  {
    return symbol_type (token::ENDWHILE, l);
  }

  Parser::symbol_type
  Parser::make_ENDDO (const location_type& l)
  {
    return symbol_type (token::ENDDO, l);
  }

  Parser::symbol_type
  Parser::make_FOR (const location_type& l)
  {
    return symbol_type (token::FOR, l);
  }

  Parser::symbol_type
  Parser::make_FROM (const location_type& l)
  {
    return symbol_type (token::FROM, l);
  }

  Parser::symbol_type
  Parser::make_TO (const location_type& l)
  {
    return symbol_type (token::TO, l);
  }

  Parser::symbol_type
  Parser::make_ENDFOR (const location_type& l)
  {
    return symbol_type (token::ENDFOR, l);
  }

  Parser::symbol_type
  Parser::make_DOWNTO (const location_type& l)
  {
    return symbol_type (token::DOWNTO, l);
  }

  Parser::symbol_type
  Parser::make_READ (const location_type& l)
  {
    return symbol_type (token::READ, l);
  }

  Parser::symbol_type
  Parser::make_WRITE (const location_type& l)
  {
    return symbol_type (token::WRITE, l);
  }

  Parser::symbol_type
  Parser::make_END (const location_type& l)
  {
    return symbol_type (token::END, l);
  }

  Parser::symbol_type
  Parser::make_ADD (const location_type& l)
  {
    return symbol_type (token::ADD, l);
  }

  Parser::symbol_type
  Parser::make_SUB (const location_type& l)
  {
    return symbol_type (token::SUB, l);
  }

  Parser::symbol_type
  Parser::make_MUL (const location_type& l)
  {
    return symbol_type (token::MUL, l);
  }

  Parser::symbol_type
  Parser::make_DIV (const location_type& l)
  {
    return symbol_type (token::DIV, l);
  }

  Parser::symbol_type
  Parser::make_MOD (const location_type& l)
  {
    return symbol_type (token::MOD, l);
  }



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 3: // NUM
      case 4: // PIDENTIFIER
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 3: // NUM
      case 4: // PIDENTIFIER
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 3: // NUM
      case 4: // PIDENTIFIER
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 3:
#line 54 "parser.yy" // lalr1.cc:859
    { std::cout<<"dasdasda";}
#line 905 "parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 81 "parser.yy" // lalr1.cc:859
    {  }
#line 911 "parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 82 "parser.yy" // lalr1.cc:859
    {  }
#line 917 "parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 83 "parser.yy" // lalr1.cc:859
    {  }
#line 923 "parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 84 "parser.yy" // lalr1.cc:859
    {  }
#line 929 "parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 85 "parser.yy" // lalr1.cc:859
    {  }
#line 935 "parser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 86 "parser.yy" // lalr1.cc:859
    {  }
#line 941 "parser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 90 "parser.yy" // lalr1.cc:859
    {  }
#line 947 "parser.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 91 "parser.yy" // lalr1.cc:859
    {  }
#line 953 "parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 92 "parser.yy" // lalr1.cc:859
    {  }
#line 959 "parser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 93 "parser.yy" // lalr1.cc:859
    {  }
#line 965 "parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 94 "parser.yy" // lalr1.cc:859
    {  }
#line 971 "parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 95 "parser.yy" // lalr1.cc:859
    {  }
#line 977 "parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 99 "parser.yy" // lalr1.cc:859
    { std::cout << yystack_[0].value.as< std::string > ();  }
#line 983 "parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 100 "parser.yy" // lalr1.cc:859
    {  }
#line 989 "parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 104 "parser.yy" // lalr1.cc:859
    {  }
#line 995 "parser.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 105 "parser.yy" // lalr1.cc:859
    {  }
#line 1001 "parser.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 106 "parser.yy" // lalr1.cc:859
    {  }
#line 1007 "parser.tab.cc" // lalr1.cc:859
    break;


#line 1011 "parser.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char Parser::yypact_ninf_ = -16;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      -8,   -16,    15,    -2,   -16,     6,   147,   -16,    28,    27,
       1,     1,   147,    14,    35,     1,     9,   -16,    36,    53,
      52,   -16,    39,    10,   -16,    41,   149,    38,    57,    85,
     -16,   -16,     1,    93,    88,    90,   147,     1,     1,     1,
       1,     1,     1,   147,     1,     1,   -16,   -16,    94,    33,
      92,   -16,   -16,   104,   -16,   -16,   -16,   -16,   -16,   -16,
      25,    -7,    22,   -16,     1,     1,     1,     1,     1,    96,
     147,   -16,   -16,   -16,     1,     1,   -16,   -16,   -16,   -16,
     -16,   -16,    71,    81,    82,   -16,   147,   147,   115,   131,
     -16,   -16
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       2,     4,     0,     0,     1,     0,     0,     5,     0,    32,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     0,
       0,    30,     0,     0,    31,     0,     0,     0,     0,     0,
       3,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    17,     0,    18,
       0,    34,    33,     0,    24,    25,    26,    27,    28,    29,
       0,     0,     0,     9,     0,     0,     0,     0,     0,     0,
       0,    11,    12,    13,     0,     0,    19,    20,    21,    22,
      23,     6,     0,     0,     0,    10,     0,     0,     0,     0,
      14,    15
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -16,   -16,   -16,    -9,   -15,   -16,    -4,    47,    -6
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,    16,    17,    48,    22,    23,    24
  };

  const unsigned char
  Parser::yytable_[] =
  {
      18,    31,     5,    26,    21,     9,    18,    25,    28,     1,
      18,    31,     7,     9,     8,     4,     6,    43,    27,    73,
      18,    37,    38,    39,    40,    41,    42,    53,    10,     9,
      18,    19,    11,    12,    60,    20,    13,    18,    31,     9,
      61,    14,    15,    30,    10,    31,    32,    18,    11,    12,
      72,    74,    13,    75,    18,    34,    35,    14,    15,    36,
      33,    82,    29,    46,    18,    43,    45,    31,    64,    65,
      66,    67,    68,    31,    31,     9,    18,    88,    89,    49,
      18,    18,    18,    18,    54,    55,    56,    57,    58,    59,
      10,    47,    62,    85,    11,    12,    50,    51,    13,    52,
      63,    69,    81,    14,    15,    86,    87,     0,     9,     0,
       0,    76,    77,    78,    79,    80,     0,     0,     0,     9,
       0,    83,    84,    10,     0,    70,    71,    11,    12,     0,
       0,    13,     0,     0,    10,     9,    14,    15,    11,    12,
       0,     0,    13,     0,     0,    90,     0,    14,    15,     0,
      10,     9,     0,     9,    11,    12,     0,     0,    13,     0,
       0,    91,     0,    14,    15,     0,    10,     0,    10,     0,
      11,    12,    44,    12,    13,     0,    13,     0,     0,    14,
      15,    14,    15
  };

  const signed char
  Parser::yycheck_[] =
  {
       6,    16,     4,    12,     3,     4,    12,    11,    14,    17,
      16,    26,     6,     4,     8,     0,    18,    24,     4,    26,
      26,    11,    12,    13,    14,    15,    16,    36,    19,     4,
      36,     3,    23,    24,    43,     8,    27,    43,    53,     4,
      44,    32,    33,    34,    19,    60,    10,    53,    23,    24,
      25,    29,    27,    31,    60,     3,     4,    32,    33,    20,
       7,    70,    15,     6,    70,    24,    28,    82,    35,    36,
      37,    38,    39,    88,    89,     4,    82,    86,    87,    32,
      86,    87,    88,    89,    37,    38,    39,    40,    41,    42,
      19,     6,    45,    22,    23,    24,     3,     9,    27,     9,
       6,     9,     6,    32,    33,    24,    24,    -1,     4,    -1,
      -1,    64,    65,    66,    67,    68,    -1,    -1,    -1,     4,
      -1,    74,    75,    19,    -1,    21,    22,    23,    24,    -1,
      -1,    27,    -1,    -1,    19,     4,    32,    33,    23,    24,
      -1,    -1,    27,    -1,    -1,    30,    -1,    32,    33,    -1,
      19,     4,    -1,     4,    23,    24,    -1,    -1,    27,    -1,
      -1,    30,    -1,    32,    33,    -1,    19,    -1,    19,    -1,
      23,    24,    23,    24,    27,    -1,    27,    -1,    -1,    32,
      33,    32,    33
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    17,    41,    42,     0,     4,    18,     6,     8,     4,
      19,    23,    24,    27,    32,    33,    43,    44,    48,     3,
       8,     3,    46,    47,    48,    46,    43,     4,    48,    47,
      34,    44,    10,     7,     3,     4,    20,    11,    12,    13,
      14,    15,    16,    24,    23,    28,     6,     6,    45,    47,
       3,     9,     9,    43,    47,    47,    47,    47,    47,    47,
      43,    46,    47,     6,    35,    36,    37,    38,    39,     9,
      21,    22,    25,    26,    29,    31,    47,    47,    47,    47,
      47,     6,    43,    47,    47,    22,    24,    24,    43,    43,
      30,    30
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    40,    41,    41,    42,    42,    42,    43,    43,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    45,    45,
      45,    45,    45,    45,    46,    46,    46,    46,    46,    46,
      47,    47,    48,    48,    48
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     0,     5,     0,     3,     8,     2,     1,     4,
       7,     5,     5,     5,     9,     9,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     4,     4
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "NUM", "PIDENTIFIER", "ERROR",
  "SEMICOLON", "COLON", "LBR", "RBR", "ASSIGN", "EQUAL", "NEQUAL", "LESS",
  "GREAT", "LESSEQ", "GREATEQ", "DECLARE", "IN", "IF", "THEN", "ELSE",
  "ENDIF", "WHILE", "DO", "ENDWHILE", "ENDDO", "FOR", "FROM", "TO",
  "ENDFOR", "DOWNTO", "READ", "WRITE", "END", "ADD", "SUB", "MUL", "DIV",
  "MOD", "$accept", "start", "declarations", "commands", "command",
  "expression", "condition", "value", "identifier", YY_NULLPTR
  };


  const unsigned char
  Parser::yyrline_[] =
  {
       0,    52,    52,    54,    57,    59,    60,    64,    65,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    81,    82,
      83,    84,    85,    86,    90,    91,    92,    93,    94,    95,
      99,   100,   104,   105,   106
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
    };
    const unsigned int user_token_number_max_ = 294;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 5 "parser.yy" // lalr1.cc:1167
} // Compiler
#line 1412 "parser.tab.cc" // lalr1.cc:1167
#line 109 "parser.yy" // lalr1.cc:1168

void
Compiler::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
