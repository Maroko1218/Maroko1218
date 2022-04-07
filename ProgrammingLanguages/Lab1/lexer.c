/**********************************************************************/
/* lab 1 DVG C01 - Lexer OBJECT                                       */
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
#define BUFSIZE 1024
#define LEXSIZE 30
static int Progcheck = 0;
static char cbuffer[BUFSIZE];      /* Character buffer for reading in the program */
static char buffer[BUFSIZE];
static char lexbuf[LEXSIZE];
static int pbuf = 0;               /* current index program buffer */
static int plex = 0;               /* current index lexeme buffer  */

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
/**********************************************************************/
/* buffer functions                                                   */
/**********************************************************************/
/**********************************************************************/
/* Read the input file into the buffer                                */
/**********************************************************************/

static void get_prog() {
    while(Progcheck == 0 && fgets(cbuffer, BUFSIZE, stdin)){
        strcat(buffer, cbuffer);
    }
    Progcheck = 1;
    //printf("%s", buffer); //Debug
}

/**********************************************************************/
/* Display the buffer                                                 */
/**********************************************************************/  

static void pbuffer() {
    printf("%s", buffer);
}

/**********************************************************************/
/* Copy a character from the program buffer to the lexeme buffer      */
/**********************************************************************/

static void get_char() {
    lexbuf[plex++] = buffer[pbuf++];
    lexbuf[plex] = '\0';
    
}

/**********************************************************************/
/* End of buffer handling functions                                   */
/**********************************************************************/

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Return a token                                                     */
/**********************************************************************/

int get_token() {
    get_prog();
    plex = 0;
    get_char();
    while (lexbuf[plex - 1] == ' ' || lexbuf[plex - 1] == '\n') {
        plex = 0;
        get_char();
    }

    while (lexbuf[plex - 1] != ' ' && lexbuf[plex - 1] != '\n' && lexbuf[plex - 1] != ',' && lexbuf[plex - 1] != '(' && lexbuf[plex - 1] != ')' && lexbuf[plex - 1] != ';') {
        get_char();
        if (lexbuf[plex - 1] == ',' || lexbuf[plex - 1] == '(' || lexbuf[plex - 1] == ')' || lexbuf[plex - 1] == ';') {
            lexbuf[plex - 1] = '\000';
            pbuf--;
            return lex2tok(lexbuf);
        }
    }
    if (lexbuf[plex - 1] == ' ' || lexbuf[plex - 1] == '\n') {
        lexbuf[plex - 1] = '\000';    
    } else {
        lexbuf[plex] = '\000';
    }
    
    return lex2tok(lexbuf);
}

/**********************************************************************/
/* Return a lexeme                                                    */
/**********************************************************************/

char* get_lexeme() {
    return lexbuf;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/

