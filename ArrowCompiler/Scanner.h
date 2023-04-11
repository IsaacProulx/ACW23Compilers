/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@                                                               @@@@
@@          /       ==============================        /          @@
@         ////           @@       @@ #@                  ////         @
@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @
@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @
@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @
@     (((((/)))((    ------------------------------    ((((./////*    @
@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @
@    ///// / /////   ==============================  * ////* / ////   @
@     ///// ///// ((                               (( ///// /////     @
@    ((((   / , (((((                             (((((  //   /(((    @
@    (((((((/ . (((((                          (((((* / (((((((       @
@      (((((( //((((/((((                    *((((/((((/( (((((/      @
@       .//,   * /   (((((                   (((((  ///    .//.       @
@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @
@         //////// ,// ((( /////,     ////// ((( //  /////// *        @
@            (((((((((,// * /////     /////   (//(((((((((            @
@            ((((((((((((/////         //.///  (((((((((((.           @
@                   (///////// //(   (//.//////////                   @
@                  (/////////             //////////                  @
@                                                                     @
@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@
@@@@                                                               @@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Sep 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	VoMID_T,	/*  1: Variable or Method identifier token */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	LBR_T,		/*  5: Left brace token */
	RBR_T,		/*  6: Right brace token */
	KW_T,		/*  7: Keyword token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	INL_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	
	LSB_T,		/* 12: Left square bracket token */
	RSB_T,		/* 13: Right square bracket token */
	COM_T,		/* 14: Comment token */
	BOOL_T,
	INTLIT_T,
	FLOATLIT_T,
	ARITHOP_T,
	RELOP_T,
	LOGOP_T,
	BITOP_T,
	COMMA_T,
	QUES_T,
	COL_T
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { 
	OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_EXP, OP_MOD, 
	OP_INCR, OP_DECR, 
	OP_ADDASGN, OP_SUBASGN, OP_MULASGN, OP_DIVASGN, OP_EXPASGN, OP_MODASGN
} AriOperator;
typedef enum RelationalOperators { 
	OP_EQ, OP_NE, OP_GT, OP_GE, OP_LT, OP_LE,
	OP_CONCAT, OP_SPREAD,
	OP_ASGN, OP_ARROW
} RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum BitwiseOperators {
	OP_LSH, OP_RSH, OP_BNOT, OP_BAND, OP_BXOR, OP_BOR,
	OP_LSHASGN, OP_RSHASGN, OP_BANDASGN, OP_BXORASGN, OP_BORASGN
} BitOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	arrow_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	BitOperator bitwiseOperator;		/* bitwise operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	arrow_int intValue;						/* integer literal attribute (value) */
	arrow_int keywordIndex;					/* keyword index in the keyword table */
	arrow_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	arrow_float floatValue;					/* floating-point literal attribute (value) */
	arrow_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	arrow_char errLexeme[ERR_LEN + 1];		/* error token attribite */
	arrow_bool boolValue;
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	arrow_byte flags;			/* Flags information */
	union {
		arrow_int intValue;				/* Integer value */
		arrow_float floatValue;			/* Float value */
		arrow_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	arrow_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
/* TODO: ADD COL FOR SLASH*/
//Upper case: col0
//Lower case: col1
#define CHRCOL2 '_'
//Digit: col3
#define CHRCOL4 '.'
#define CHRCOL5 '"'
#define CHRCOL6 '\''
#define CHRCOL7 '`'
#define CHRCOL8 '\n'
//#define CHRCOL3 '&'
#define OTHERCOL 10

/* These constants will be used on VID / MID function */
#define MNIDPREFIX '&'

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESNR	19		/* Error state with no retract */
#define ESWR	20		/* Error state with retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 14

/* TO_DO: Transition table - type of states defined in separate table */
static arrow_int transitionTable[][TABLE_COLUMNS] = {
	/*[A-Z],     [a-z],    _,      [0-9],  .,      ",         ',        `,         \n,      EOF,    other
	  Upper(0),  Lower(1), Und(2), Dig(3), Dot(4), QuotD(5),  QuotS(6), BkTk(7),   EOL(8),	EOF(9)	other(10)*/
	{    7,	     6,        7,      4,      3,      10,        9,        11,        0,       0,    ESNR}, // S0: NOAS
	{    1,	     1,        1,      1,      1,       1,        1,         1,        1,    ESWR,       1}, // S1: NOAS
	{    2,	     2,        2,      2,      2,       2,        2,         2,		  12,      12,       2}, // S2: NOAS
	{ ESNR,	  ESNR,     ESNR,      5,     21,    ESNR,     ESNR,      ESNR,		ESNR,    ESWR,    ESNR}, // S3: NOAS
	{   14,	    14,       14,      4,      5,      14,       14,        14,       14,      14,      14}, // S4: NOAS
	{   13,	    13,       13,      5,     13,      13,       13,        13,	      13,      13,      13}, // S5: NOAS
	{    7,	     6,        7,      7,      8,       8,        8,         8,		   8,       8,       8}, // S6: NOAS
	{    7,	     7,        7,      7,     17,      17,       17,        17,       17,      17,      17}, // S7: NOAS
	{   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S8: KEY or BOOL or VoMID
	{    9,	     9,        9,      9,      9,       9,       18,         9,     ESWR,    ESWR,       9}, // S9: NOAS
	{   10,	    10,       10,     10,     10,      18,       10,        10,     ESWR,    ESWR,      10}, // S10: NOAS
	{   11,	    11,       11,     11,     11,      11,       11,        18,       11,    ESWR,      11}, // S11: NOAS
	{   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S12: ASNR (Comment)
	{   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S13: ASWR (Float Literal)
	{   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S14: ASWR (Integer Literal)
	{   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S15: ASWR (Boolean Literal)
	{   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S16: ASWR (KeyWord)
	{   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S17: ASWR (VoMID)
	{   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S18: ASNR (String Literal)
	{   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S19: ASNR (Err1)
    {   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S20: ASWR (Err2)
	{   22,	    22,       22,     22,     23,      22,       22,        22,       22,      22,      22}, // S21: NOAS
	{   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S22: ASWR (Concatenation)
	{   FS,	    FS,       FS,     FS,     FS,      FS,       FS,        FS,       FS,      FS,      FS}, // S23: ASNR (Spread) (may not be used)
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static arrow_int stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	NOFS, /* 02 */
	NOFS, /* 03 */
	NOFS, /* 04 */
	NOFS, /* 05 */
	NOFS, /* 06 */
	NOFS, /* 07 */
	FSWR, /* 08 */
	NOFS, /* 09 */
	NOFS, /* 10 */
	NOFS, /* 11 */
	FSNR, /* 12 (Comment) */
	FSWR, /* 13 (Float Literal) */
	FSWR, /* 14 (Integer Literal) */
	FSWR, /* 15 (Boolean Literal) */
	FSWR, /* 16 (KeyWord) */
	FSWR, /* 17 (VoMID) */
	FSNR, /* 18 (String Literal) */
	FSNR, /* 19 (Err1 - no retract) */
	FSWR, /* 20 (Err2 - with retract) */
	NOFS, /* 21 */
	FSWR, /* 22 (Concatenation Operator) */
	FSNR, /* 23 (Spread Operator) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
arrow_int startScanner(ReaderPointer psc_buf);
Token tokenizer(arrow_void);
static arrow_int nextClass(arrow_char c);				/* character class function */
static arrow_int nextState(arrow_int, arrow_char);		/* state machine function */
arrow_void printToken(Token t);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(arrow_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(arrow_char lexeme[]);
Token funcVoMID	(arrow_char lexeme[]);
Token funcKEY	(arrow_char lexeme[]);
Token funcErr	(arrow_char lexeme[]);
Token funcIL	(arrow_char lexeme[]);
Token funcIntLiteral    (arrow_char lexeme[]);
Token funcFloatLiteral		(arrow_char lexeme[]);
//Token funcBoolLiteral(arrow_char lexeme[]);
Token funcRelOp	(arrow_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -     [00] */
	NULL,		/* -     [01] */
	NULL,		/* -	 [02] */
	NULL,		/* -	 [03] */
	NULL,		/* -     [04] */
	NULL,		/* -	 [05] */
	NULL,		/* -	 [06] */
	NULL,		/* -	 [07] */
	funcKEY,	/* -     [08] */
	NULL,		/* -     [09] */
	NULL,		/* -	 [10] */
	NULL,		/* -     [11] */
	NULL,		/* COM   [12] */
	funcFloatLiteral,	/* FL    [13] - Float Literal*/
	funcIntLiteral,		/* IL    [14] - Integer Literal */
	NULL,		/* BL    [15] - Boolean Literal */
	funcKEY,	/* KEY   [16] - Key Word */
	funcVoMID,	/* VoMID [17] - VoMID */
	funcSL, 	/* SL	 [18] - String Literal */
	funcErr,	/* Err1	 [19] - Err1 */
	funcErr,	/* Err2	 [20] - Err2 */
	NULL,
	funcRelOp,
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 18

/* TO_DO: Define the list of keywords */
static arrow_char* keywordTable[KWT_SIZE] = {
	"let",
	"const",
	"int",
	"float",
	"string",
	"bool",
	"list",
	"function",
	"return",
	"if",
	"else",
	"for",
	"while",
	"break",
	"continue",
	"try",
	"catch",
	"finally"
};

/* About indentation (useful for positional languages (ex: Python, Cobol) */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	arrow_char indentationCharType;
	arrow_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
arrow_int numScannerErrors;

#endif
