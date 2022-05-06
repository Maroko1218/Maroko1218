lexer([ ], [ ]).
lexer([H|T], [F|S]) :-match(H, F), lexer(T,S). 

match(L, F) :- L = '(', F is 40.
match(L, F) :- L = ')', F is 41.
match(L, F) :- L = '*', F is 42.
match(L, F) :- L = '+', F is 43.
match(L, F) :- L = ',', F is 44.
match(L, F) :- L = '.', F is 46.
match(L, F) :- L = ':', F is 58.
match(L, F) :- L = ';', F is 59.
match(L, F) :- L = 'program', F is 256.
match(L, F) :- L = 'input', F is 257.
match(L, F) :- L = 'output', F is 258.
match(L, F) :- L = 'var', F is 259.
match(L, F) :- L = 'integer', F is 260.
match(L, F) :- L = 'begin', F is 261.
match(L, F) :- L = 'end', F is 262.
match(L, F) :- L = 'real', F is 264.
match(L, F) :- name(L, [T|S]), char_type(T, alpha), match_id(S), F is 270.
match(L, F) :- L = ':=', F is 271.
match(L, F) :- name(L, [T|S]), char_type(T, digit), match_digit(S), F is 272.


match_digit([ ]).
match_digit([H|T]) :- char_type(H, digit), match_digit(T).

match_id([ ]).
match_id([H|T]) :- char_type(H, alnum), match_id(T).



read_in(File, [W|Ws]) :- see(File), get0(C), readword(C, W, C1), restsent(W, C1, Ws), seen. 

/******************************************************************************/
/* From Programming in Prolog (4th Ed.) Clocksin & Mellish, Springer (1994)   */
/* Chapter 5, pp 101-103 (DFR (140421) modified for input from a file)        */
/******************************************************************************/

read_in(File,[W|Ws]) :- see(File), get0(C), readword(C, W, C1), restsent(W, C1, Ws), nl, seen.

/******************************************************************************/
/* Given a word and the character after it, read in the rest of the sentence  */
/******************************************************************************/

restsent(W, _, [])         :- W = -1.                /* added EOF handling */
restsent(W, _, [])         :- lastword(W).
restsent(_, C, [W1 | Ws ]) :- readword(C, W1, C1), restsent(W1, C1, Ws).

/******************************************************************************/
/* Read in a single word, given an initial character,                         */
/* and remembering what character came after the word (NB!)                   */
/******************************************************************************/

readword(C, W, _)  :- C = -1, W = C.                    /* added EOF handling */
readword(C, W, C2) :- C = 58, get0(C1), readwordaux(C, W, C1, C2). 
readword(C, W, C1) :- single_character( C ), name(W, [C]), get0(C1).
readword(C, W, C2) :-
    in_word(C, NewC ),
    get0(C1),
    restword(C1, Cs, C2),
    name(W, [NewC|Cs]).

readword(_, W, C2) :- get0(C1), readword(C1, W, C2).

readwordaux(C, W, C1, C2) :- C1 = 61, name(W, [C, C1]), get0(C2).
readwordaux(C, W, C1, C2) :- C1 \= 61, name(W, [C]), C1 = C2. 

restword(C, [NewC|Cs], C2) :-
    in_word(C, NewC),
    get0(C1),
    restword(C1, Cs, C2).

restword(C, [ ], C).


/******************************************************************************/
/* These characters form words on their own                                   */
/******************************************************************************/

single_character(40).                  /* ( */
single_character(41).                  /* ) */
single_character(42).                  /* + */
single_character(43).                  /* * */
single_character(44).                  /* , */
single_character(59).                  /* ; */
single_character(58).                  /* : */
single_character(61).                  /* = */
single_character(46).                  /* . */

/******************************************************************************/
/* These characters can appear within a word.                                 */
/* The second in_word clause converts character to lower case                 */
/******************************************************************************/

in_word(C, C) :- C>96, C<123.             /* a b ... z */
in_word(C, L) :- C>64, C<91, L is C+32.   /* A B ... Z */
in_word(C, C) :- C>47, C<58.              /* 1 2 ... 9 */

/******************************************************************************/
/* These words terminate a sentence                                           */
/******************************************************************************/

lastword('.').
/*** The fax machine ***/
leftpar --> [40].
rightpar --> [41].
mulop --> [42].
addop --> [43].
comma --> [44].
dot --> [46].
colon --> [58].
scolon --> [59].
program --> [256].
input --> [257].
output --> [258].
var --> [259].
integer --> [260].
begin --> [261].
end --> [262].
real --> [264].
id --> [270].
assign --> [271].
number --> [272].
/*** End of fax ***/

operand --> id; number.
factor --> leftpar, expr, rightpar; operand.
term --> factor; factor, mulop, term.
expr --> term; term, addop, expr.
stat --> id, assign, expr.
stat_list --> stat; stat, scolon, stat_list.
stat_part --> begin, stat_list, end, dot.

type --> integer; real.
id_list -->  id; id, comma, id_list.
var_dec --> id_list, colon, type, scolon.
var_dec_list --> var_dec; var_dec, var_dec_list.
var_part --> var, var_dec_list.

header --> program, id, leftpar, input, comma, output, rightpar, scolon.
prog --> header, var_part, stat_part.

parser(Tokens, Result) :- (prog(Tokens, Result), Result=[], write('Parse Succeed!')); write('Parse Fail!').
lab2(File, Result) :- read_in(File, L), lexer(L, Tokens), parser(Tokens, Result).