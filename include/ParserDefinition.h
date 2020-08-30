#include "mpc.h"
#include "Lval.h"

/* The parsers themselves  */
mpc_parser_t* Number;
mpc_parser_t* Symbol;
mpc_parser_t* Expr;
mpc_parser_t* Sexpr;
mpc_parser_t* Qexpr;
mpc_parser_t* Boolean;
mpc_parser_t* Tama;
mpc_parser_t* String;
mpc_parser_t* Comment;


/* Exported functions */
void initParserDefinition(void);
void cleanupParserDefinition(void);
