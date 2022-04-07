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
/* #include "lexer.h"       */       /* when the lexer     is added   */
/* #include "symtab.h"      */       /* when the symtab    is added   */
/* #include "optab.h"       */       /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 1
static int  lookahead=0;
static int  is_parse_ok=1;

/**********************************************************************/
/* RAPID PROTOTYPING - simulate the token stream & lexer (get_token)  */
/**********************************************************************/
/* define tokens + keywords NB: remove this when keytoktab.h is added */
/**********************************************************************/
//enum tvalues { program = 257, id, input, output, var, integer, begin, assign, number, end, boolean, real};
/**********************************************************************/
/* Simulate the token stream for a given program                      */
/**********************************************************************/
static int tokens[] = {program, id, '(', input, ',', output, ')', ';', var, id, ',', id, ',', id, ',', id, ',', id, ':', integer, ';', begin, id, assign, id, '+', id, '+', id, '+', id, '*', number, end, '.', '$' };

/**********************************************************************/
/*  Simulate the lexer -- get the next token from the buffer          */
/**********************************************************************/
static int pget_token()
{  
   static int i=0;
   if (tokens[i] != '$') return tokens[i++]; else return '$';
   }

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t)
{
   if(DEBUG) printf("\n --------In match expected: %4d, found: %4d", t, lookahead);
   if (lookahead == t) lookahead = pget_token();
   else {
      is_parse_ok=0;
      printf("\n *** Unexpected Token: expected: %4d found: %4d (in match)",
              t, lookahead);
      }
   }

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/
static void program_header() {
   if (DEBUG) printf("\n *** In  program_header");
   match(program); match(id); match('('); match(input);
   match(','); match(output); match(')'); match(';');
}
/**********************************************************************/
/* The var part                                                       */
/**********************************************************************/
static void type() {
   if (lookahead == integer) {
      match(integer);
   } else if (lookahead == boolean) {
      match(boolean);
   } else {
      match(real);
   }
}

static void id_list() {
   //if (DEBUG) printf("\n *** In id_list");
   match(id); if (lookahead == ',') { match(','); id_list(); }
}

static void var_dec() {
   id_list(); match(':'); type(); match(';'); // match(integer) to be replaced with some sort of type(); function to match integer and booleans
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
static void expr(); //This is here to remove warnings with the "upwards" call to expr() from factor

static void operand() {
   if (lookahead == id) match(id);
   else match(number);
}

static void factor() {
   if (lookahead == '(') {
      match('('); expr(); match(')');
   } else {
      operand();
   }
}

static void term(){
   factor(); if (lookahead == '*') { match('*'); factor(); }// '*' to be replaced with mulop which is * or /
}

static void expr() {
   term(); if (lookahead == '+') { match('+'); expr(); }// '+' to be replaced with addop which is + or -
}

//same as assign stat hence we wont make an assign_stat function.
static void stat() { 
   match(id); match(assign); expr();
}

static void stat_list() {
   stat(); if (lookahead == ';') { match(';'); stat_list(); }
}

static void stat_part(){
   if (DEBUG) printf("\n *** In stat_part");
   match(begin), stat_list(); match(end); match('.');
}
   
/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser() {
   if (DEBUG) printf("\n *** In  parser");
   lookahead = pget_token();       // get the first token
   program_header();               // call the first grammar rule
   var_part();                     // call the second grammar rule
   stat_part();                    // call the third grammar rule
   return is_parse_ok;             // status indicator
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/