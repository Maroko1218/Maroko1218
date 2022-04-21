/**********************************************************************/
/* lab 1 DVG C01 - Parser OBJECT                                      */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"               /* when the keytoktab is added   */
#include "lexer.h"                   /* when the lexer     is added   */
#include "symtab.h"                  /* when the symtab    is added   */
#include "optab.h"                   /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 0
static int  lookahead=0;
static int  is_parse_ok=1;

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t) {
   if(DEBUG) printf("\n --------In match expected: %4d, found: %4d", t, lookahead);
   if (lookahead == t) lookahead = get_token();
   else {
      is_parse_ok=0;

      switch (t)
      {
      case typ:
         printf("SYNTAX:   Type name expected found: %s\n", get_lexeme());
         break;
      case id:
         printf("SYNTAX:   ID expected. Found: %s\n", get_lexeme());
         break;
      default: 
         printf("SYNTAX:   Symbol expected: %s found: %s\n", tok2lex(t), get_lexeme());
         break;
      }
   }
}

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/
static void matchprogheader() {
   if (lookahead != id) {
      addp_name("???");
   } else {
      addp_name(get_lexeme()); 
   }
   match(id);
}

static void program_header() {
   if (DEBUG) printf("\n *** In  program_header");
   match(program); matchprogheader(); match('('); match(input);
   match(','); match(output); match(')'); match(';');
}
/**********************************************************************/
/* The var part                                                       */
/**********************************************************************/
static void declarevariable() {
   if (!find_name(get_lexeme())) {
      addv_name(get_lexeme()); match(id);
   } else {
      printf("SEMANTIC: The variable %s is already declared\n", get_lexeme());
      match(id);
   }
}

static void type() {
   if (lookahead == integer) {
      setv_type(integer); match(integer);
   } else if (lookahead == boolean) {
      setv_type(boolean); match(boolean);
   } else if (lookahead == real) {
      setv_type(real); match(real);
   } else {
      setv_type(error);
      match(typ);
   }
}

static void id_list() {
   //if (DEBUG) printf("\n *** In id_list");
   if (lookahead == id) {
      declarevariable(); 
   }
   if (lookahead == ',') { match(','); id_list(); }
}

static void var_dec() {
   id_list(); match(':'); type(); match(';');
}

static void var_dec_list() {
   var_dec(); if (lookahead == id) { var_dec_list(); }
}

static void var_part() {
   if (DEBUG) printf("\n *** In var_part");
   match(var); var_dec_list();
}
/**********************************************************************/
/* The stat part                                                      */
/**********************************************************************/
static toktyp expr(); //This is here to remove warnings with the "upwards" call to expr() from factor

static toktyp getvariable() {
   if (find_name(get_lexeme())) {
      toktyp temp = get_ntype(get_lexeme());
      match(id);
      return temp;
   } else {
      if (lookahead == id) {
         if (find_name(get_lexeme())) {
            printf("SEMANTIC: variable name %s undeclared\n", get_lexeme());
            is_parse_ok = 0;
            match(id);
            return undef;
         }
         printf("SEMANTIC: variable name %s undeclared\n", get_lexeme());
         is_parse_ok = 0;
         match(id);
         return error;
      }
      is_parse_ok = 0;
      match(id);
      return error;
   }
}

static toktyp operand() {
   if (lookahead == id) {
      toktyp temp = getvariable();
      return temp;
   } else if (lookahead == number) {
      match(number);
      return integer;
   } else {
      printf("SYNTAX:   Operand Expected\n");
      return error;
   }
}

static toktyp factor() {
   toktyp temp;
   if (lookahead == '(') {
      match('('); temp = expr(); match(')');
      return temp;
   } else {
      return operand();
   }
}

static toktyp term() {
   toktyp leftside, rightside;
   leftside = factor(); if (lookahead == '*') { 
      match('*'); 
      rightside = factor();
      return get_otype('*', leftside, rightside);
   }
   return leftside;
}

static toktyp expr() {
   toktyp leftside, rightside;
   leftside = term(); if (lookahead == '+') { 
      match('+'); 
      rightside = expr(); 
      return get_otype('+', leftside, rightside);
   }
   return leftside;
}

//same as assign stat hence we wont make an assign_stat function.
static void stat() {
   toktyp leftside, rightside;
   leftside = getvariable(); match(assign); rightside = expr();
   if (leftside != rightside) {
      printf("SEMANTIC: Assign types: %s := %s\n", tok2lex(leftside), tok2lex(rightside));
      is_parse_ok = 0;
   }
}

static void stat_list() {
   stat(); if (lookahead == ';') { match(';'); stat_list(); }
}

static void stat_part(){
   if (DEBUG) printf("\n *** In stat_part");
   match(begin), stat_list(); match(end); match('.');
   if (lookahead != '$') {
      is_parse_ok = 0;
      printf("SYNTAX:   Extra symbols after end of parse!\n          ");
      while (lookahead != '$') {
         printf("%s ", get_lexeme());
         lookahead = get_token();
      }
      
   }
   
}
   
/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser() {
   if (DEBUG) printf("\n *** In  parser");
   lookahead = get_token();        // get the first token
   if (lookahead == '$') {         // If the file is empty only a dollar will be found
      printf("WARNING:   Input file is empty\n");
      is_parse_ok = 0;
      return is_parse_ok;
   }
   program_header();               // call the first grammar rule
   var_part();                     // call the second grammar rule
   stat_part();                    // call the third grammar rule
   return is_parse_ok;             // status indicator
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/