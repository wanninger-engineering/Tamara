#ifndef _PARSER_DEF_
#define _PARSER_DEF_

#include "mpc.h"
#include "Lval.h"

/* The parsers themselves  */
extern mpc_parser_t* Number;
extern mpc_parser_t* Symbol;
extern mpc_parser_t* Expr;
extern mpc_parser_t* Sexpr;
extern mpc_parser_t* Qexpr;
extern mpc_parser_t* Boolean;
extern mpc_parser_t* Tama;
extern mpc_parser_t* String;
extern mpc_parser_t* Comment;


/* Exported functions */
void initParserDefinition(void);
void cleanupParserDefinition(void);
#endif
