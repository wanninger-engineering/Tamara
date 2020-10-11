#include <string.h>
#include <math.h>
#include "mpc.h"
#include "ParserDefinition.h"


mpc_parser_t* Number;
mpc_parser_t* Symbol;
mpc_parser_t* Expr;
mpc_parser_t* Sexpr;
mpc_parser_t* Qexpr;
mpc_parser_t* Boolean;
mpc_parser_t* Tama;
mpc_parser_t* String;
mpc_parser_t* Comment;

/* Init the parser for the language */
void initParserDefinition(void)
{
  /* Create new parsers */
  Number = mpc_new("number");
  Symbol = mpc_new("symbol");
  Expr = mpc_new("expr");
  Sexpr = mpc_new("sexpr");
  Qexpr = mpc_new("qexpr");
  Boolean = mpc_new("bool");
  Tama =  mpc_new("tama");
  String = mpc_new("string");
  Comment = mpc_new("comment");

  /* Parser language definition */
  mpca_lang(MPCA_LANG_DEFAULT,
	    "\
number : /-?[0-9]+(\\.[0-9]*)?/ ; \
bool   : \"#t\" | \"#f\" ;             \
string  : /\"(\\\\.|[^\"])*\"/ ; \
comment : /;[^\\r\\n]*/ ; \
symbol : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&\\|]+/ ; \
sexpr  : '(' <expr>* ')' ;                  \
qexpr  : '[' <expr>* ']' ;                  \
expr   : <number> | <symbol> | <sexpr> | <qexpr> | <bool> | <string> | <comment> ;    \
tama   : /^/ <expr>* /$/ ;                  \
  ",
	    Number, Boolean, String, Comment, Symbol, Sexpr, Qexpr, Expr, Tama);

}


void cleanupParserDefinition(void)
{
  /* Undefine and Delete our Parsers */
  mpc_cleanup(9, Number, Boolean, String, Comment, Symbol, Sexpr, Qexpr, Expr, Tama);
}
