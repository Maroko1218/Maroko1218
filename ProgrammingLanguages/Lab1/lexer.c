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
static char buffer[BUFSIZE];       /* Program buffer which stores the entire program text */
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
static void pbuffer();

static void get_prog() {
    while(Progcheck == 0 && fgets(cbuffer, BUFSIZE, stdin)){
        strcat(buffer, cbuffer);
    }
    if (Progcheck == 0) {
        strcat(buffer, "$");
        pbuffer();
    }
    Progcheck = 1;
}

/**********************************************************************/
/* Display the buffer                                                 */
/**********************************************************************/  

static void pbuffer() {
    printf("________________________________________________________\n THE PROGRAM TEXT\n________________________________________________________\n");
    printf("%s", buffer);
    printf("\n________________________________________________________\n");
}

/**********************************************************************/
/* Copy a character from the program buffer to the lexeme buffer      */
/**********************************************************************/

static void get_char() {
    lexbuf[plex++] = buffer[pbuf++];
    lexbuf[plex] = '\0';
}

/**********************************************************************/
/* Skip whitespace and newline characters in the program buffer       */
/**********************************************************************/

static void skip_whitespace() {
    while (buffer[pbuf] == ' ' || buffer[pbuf] == '\n' || buffer[pbuf] == '\r') {
        pbuf++;
    }
}

/**********************************************************************/
/* Check if the lexeme is a number                                    */
/**********************************************************************/

static int is_num(char chr) {
    if (chr == '0' || chr == '1' || 
        chr == '2' || chr == '3' || 
        chr == '4' || chr == '5' || 
        chr == '6' || chr == '7' || 
        chr == '8' || chr == '9') {
        return 1;
    }
    return 0;
}

/**********************************************************************/
/* Read from program buffer until a special character                 */
/**********************************************************************/

static void read_lexeme() {
    while (buffer[pbuf] != ' ' && buffer[pbuf] != '\n' && buffer[pbuf] != '\r' && buffer[pbuf] != ',' && buffer[pbuf] != '.'
        && buffer[pbuf] != '(' && buffer[pbuf] != ')'  && buffer[pbuf] != ';' && buffer[pbuf] != ':'
        && pbuf < strlen(buffer)) {
        get_char();
        if (is_num(lexbuf[0]) && !is_num(buffer[pbuf])) {
            break;
        }
        
    }
    if (plex == 0) {
        get_char();
        if (buffer[pbuf - 1] == ':' && buffer[pbuf] == '=') {
            get_char();
        }
    }
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
    skip_whitespace();
    read_lexeme();
    plex = 0;
    if (is_num(lexbuf[0])) {
        return lex2tok("number");
    }
    toktyp temp = lex2tok(lexbuf);
    if (temp == number || temp == undef || temp == predef || temp == tempty || temp == error || temp == typ) {
        return key2tok(lexbuf);
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

