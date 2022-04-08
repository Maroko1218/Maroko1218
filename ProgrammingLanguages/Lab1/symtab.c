/**********************************************************************/
/* lab 1 DVG C01 - Symbol Table OBJECT                                */
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

#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/

#define TABSIZE 1024                   /* symbol table size           */
#define NAMELEN   20                   /* name length                 */

typedef char tname[NAMELEN];

static tname name[TABSIZE];
static toktyp role[TABSIZE];
static toktyp type[TABSIZE];
static int size[TABSIZE];
static int addr[TABSIZE];

static int numrows=0;                  /* number of rows in the ST    */
static int startp =0;                  /* start position program in ST*/

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
/**********************************************************************/
/*  GET methods (one for each attribute)                              */
/**********************************************************************/

static char* get_name(int ftref) { return name[ftref]; }
static toktyp get_role(int ftref) { return role[ftref]; }
static toktyp get_type(int ftref) { return type[ftref]; }
static int get_size(int ftref) { return size[ftref]; }
static int get_addr(int ftref) { return addr[ftref]; }

/**********************************************************************/
/*  SET methods (one for each attribute)                              */
/**********************************************************************/

static void set_name(int ftref, char* fpname) { strcpy(name[ftref], fpname);}
static void set_role(int ftref, toktyp frole) { role[ftref] = frole; }
static void set_type(int ftref, toktyp ftype) { type[ftref] = ftype; }
static void set_size(int ftref, int fsize) { size[ftref] = fsize; }
static void set_addr(int ftref, int faddr) { addr[ftref] = faddr; }

/**********************************************************************/
/*  Add a row to the symbol table                                     */
/**********************************************************************/

static void addrow(char* fname, toktyp frole, toktyp ftype, int fsize, int faddr) {
    printf("\n *** TO BE DONE");
}

/**********************************************************************/
/*  Initialise the symbol table                                       */
/**********************************************************************/

static void initst() {
    addrow(tok2lex(predef), typ, predef, 0, 0);
    addrow(tok2lex(undef), typ, predef, 0, 0);
    addrow(tok2lex(error), typ, predef, 0, 0);
    addrow(tok2lex(integer), typ, predef, 4, 0);
    addrow(tok2lex(boolean), typ, predef, 4, 0);
    addrow(tok2lex(real), typ, predef, 8, 0);
}

/**********************************************************************/
/*  return a reference to the ST (index) if name found else nfound    */
/**********************************************************************/

static int get_ref(char* fpname) {
    printf("\n *** TO BE DONE"); 
    return 0;
}

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/*  Display the symbol table                                          */
/**********************************************************************/

static void p_symrow(int ftref) {
   printf("\n *** TO BE DONE");
}

void p_symtab() {
    printf("\n *** TO BE DONE");
}

/**********************************************************************/
/*  Add a program name to the symbol table                            */
/**********************************************************************/

void addp_name(char* fpname) { 
    printf("\n *** TO BE DONE");
}

/**********************************************************************/
/*  Add a variable name to the symbol table                           */
/**********************************************************************/

void addv_name(char* fpname) {
    printf("\n *** TO BE DONE");
}

/**********************************************************************/
/*  Find a name in the the symbol table                               */
/*  return a Boolean (true, false) if the name is in the ST           */
/**********************************************************************/

int find_name(char* fpname) { 
    printf("\n *** TO BE DONE"); 
    return 0;
}

/**********************************************************************/
/*  Set the type of an id list in the symbol table                    */
/**********************************************************************/

void setv_type(toktyp ftype) {
    printf("\n *** TO BE DONE");
}

/**********************************************************************/
/*  Get the type of a variable from the symbol table                  */
/**********************************************************************/

toktyp get_ntype(char* fpname) { 
    printf("\n *** TO BE DONE"); 
    return 0;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/