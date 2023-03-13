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
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

/* #define NDEBUG        to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern ReaderPointer stringLiteralTable;	/* String literal table */
arrow_int line;								/* Current line number of the source code */
extern arrow_int errorNumber;				/* Defined in platy_st.c - run-time error number */

extern arrow_int stateType[];
extern arrow_char* keywordTable[];
extern PTR_ACCFUN finalStateTable[];
extern arrow_int transitionTable[][TABLE_COLUMNS];

/* Local(file) global objects - variables */
static ReaderPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static ReaderPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */

arrow_int startScanner(ReaderPointer psc_buf) {
	/* in case the buffer has been read previously  */
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ***********************************************************
 */

Token tokenizer(julius_void) {

	/* TO_DO: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	arrow_char c;	/* input symbol */
	arrow_int state = 0;		/* initial state of the FSM */
	arrow_int lexStart;		/* start offset of a lexeme in the input char buffer (array) */
	arrow_int lexEnd;		/* end offset of a lexeme in the input char buffer (array)*/

	arrow_int lexLength;		/* token length */
	arrow_int i;				/* counter */
	arrow_char newc;			/* new char */
	
	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = readerGetChar(sourceBuffer);
		//printf("%c",c);
		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO: All patterns that do not require accepting functions */
		switch (c) {

		/* Cases for spaces */
		case ' ':
		case '\t':
		case '\f':
			break;
		case '\n':
			line++;
			break;

		/* Cases for symbols */
		case ';':
			currentToken.code = EOS_T;
			return currentToken;
		case ',':
			currentToken.code = COMMA_T;
			return currentToken;
		case '(':
			currentToken.code = LPR_T;
			return currentToken;
		case ')':
			currentToken.code = RPR_T;
			return currentToken;
		case '{':
			currentToken.code = LBR_T;
			return currentToken;
		case '}':
			currentToken.code = RBR_T;
			return currentToken;
		case '[':
			currentToken.code = LSB_T;
			return currentToken;
		case ']':
			currentToken.code = RSB_T;
			return currentToken;
		/* Operators (Most of Them) */
		/* concatenation must be handled by the state machine, since floats can start with '.' */
		case '?':
			currentToken.code = QUES_T;
			return currentToken;
		case ':':
			currentToken.code = COL_T;
			return currentToken;
		case '=':
			currentToken.code = RELOP_T;
			currentToken.attribute.relationalOperator = OP_ASGN;
			newc = readerGetChar(sourceBuffer);
			if (newc == '>') currentToken.attribute.relationalOperator = OP_ARROW;
			else if (newc == '=') currentToken.attribute.relationalOperator = OP_EQ;
			else readerRetract(sourceBuffer);
			return currentToken;
		case '>':
			newc = readerGetChar(sourceBuffer);
			if (newc == '>') {
				currentToken.code = BITOP_T;
				currentToken.attribute.bitwiseOperator = OP_RSH;
				if (readerGetChar(sourceBuffer) == '=') currentToken.attribute.bitwiseOperator = OP_RSHASGN;
				else readerRetract(sourceBuffer);
				return currentToken;
			}
			currentToken.code = RELOP_T;
			currentToken.attribute.relationalOperator = OP_GT;
			if (newc == '=') currentToken.attribute.relationalOperator = OP_GE;
			else readerRetract(sourceBuffer);
			return currentToken;
		case '<':
			newc = readerGetChar(sourceBuffer);
			if (newc == '<') {
				currentToken.code = BITOP_T;
				currentToken.attribute.bitwiseOperator = OP_LSH;
				if (readerGetChar(sourceBuffer) == '=') currentToken.attribute.bitwiseOperator = OP_LSHASGN;
				else readerRetract(sourceBuffer);
				return currentToken;
			}
			currentToken.code = RELOP_T;
			currentToken.attribute.relationalOperator = OP_LT;
			if (newc == '=') currentToken.attribute.relationalOperator = OP_LE;
			else readerRetract(sourceBuffer);
			return currentToken;
		case '!':
			if (readerGetChar(sourceBuffer) == '=') {
				currentToken.code = RELOP_T;
				currentToken.attribute.relationalOperator = OP_NE;
			}else {
				currentToken.code = LOGOP_T;
				currentToken.attribute.logicalOperator = OP_NOT;
				readerRetract(sourceBuffer);
			}
			return currentToken;
		case '&':
			newc = readerGetChar(sourceBuffer);
			if (newc == '&') {
				currentToken.code = LOGOP_T;
				currentToken.attribute.logicalOperator = OP_AND;
			}else if (newc == '=') {
				currentToken.code = BITOP_T;
				currentToken.attribute.bitwiseOperator = OP_BANDASGN;
			}else {
				currentToken.code = BITOP_T;
				currentToken.attribute.bitwiseOperator = OP_BAND;
				readerRetract(sourceBuffer);
			}
			return currentToken;
		case '|':
			newc = readerGetChar(sourceBuffer);
			if (newc == '|') {
				currentToken.code = LOGOP_T;
				currentToken.attribute.logicalOperator = OP_OR;
			}
			else if (newc == '=') {
				currentToken.code = BITOP_T;
				currentToken.attribute.bitwiseOperator = OP_BORASGN;
			}
			else {
				currentToken.code = BITOP_T;
				currentToken.attribute.bitwiseOperator = OP_BOR;
				readerRetract(sourceBuffer);
			}
			return currentToken;
		case '^':
			currentToken.code = BITOP_T;
			currentToken.attribute.bitwiseOperator = OP_BXOR;
			newc = readerGetChar(sourceBuffer);
			if (newc == '=') currentToken.attribute.bitwiseOperator = OP_BXORASGN;
			else readerRetract(sourceBuffer);
			return currentToken;
		case '~':
			currentToken.code = BITOP_T;
			currentToken.attribute.bitwiseOperator = OP_BNOT;
			return currentToken;
		case '+':
			//addition
			currentToken.code = ARITHOP_T;
			currentToken.attribute.arithmeticOperator = OP_ADD;
			newc = readerGetChar(sourceBuffer);
			if (newc == '+') currentToken.attribute.arithmeticOperator = OP_INCR;
			else if (newc == '=') currentToken.attribute.arithmeticOperator = OP_ADDASGN;
			else readerRetract(sourceBuffer);
			return currentToken;
		case '-':
			//subtraction
			currentToken.code = ARITHOP_T;
			currentToken.attribute.arithmeticOperator = OP_SUB;
			newc = readerGetChar(sourceBuffer);
			if (newc == '-') currentToken.attribute.arithmeticOperator = OP_DECR;
			else if (newc == '=') currentToken.attribute.arithmeticOperator = OP_SUBASGN;
			else readerRetract(sourceBuffer);
			return currentToken;
		case '*':
			//multiplication
			currentToken.code = ARITHOP_T;
			currentToken.attribute.arithmeticOperator = OP_MUL;
			newc = readerGetChar(sourceBuffer);
			if (newc == '*') {
				//exponentiation
				currentToken.attribute.arithmeticOperator = OP_EXP;
				newc = readerGetChar(sourceBuffer);
				if (newc == '=') currentToken.attribute.arithmeticOperator = OP_EXPASGN;
				else readerRetract(sourceBuffer);
				return currentToken;
			}
			if (newc == '=') currentToken.attribute.arithmeticOperator = OP_MULASGN;
			else readerRetract(sourceBuffer);
			return currentToken;
		case '%':
			//modulo
			currentToken.code = ARITHOP_T;
			currentToken.attribute.arithmeticOperator = OP_MOD;
			newc = readerGetChar(sourceBuffer);
			if (newc == '=') currentToken.attribute.arithmeticOperator = OP_MODASGN;
			else readerRetract(sourceBuffer);
			return currentToken;
		case '/':
			newc = readerGetChar(sourceBuffer);
			if (newc != '/' && newc != '*') {
				//division
				currentToken.code = ARITHOP_T;
				currentToken.attribute.arithmeticOperator = OP_DIV;
				if (newc == '=') currentToken.attribute.arithmeticOperator = OP_DIVASGN;
				else readerRetract(sourceBuffer);
				return currentToken;
			}
			currentToken.code = COM_T;
			if (newc == '/') {
				//single line comment
				do {
					newc = readerGetChar(sourceBuffer);
					//Maybe do something with comment text later
				} while (newc != '\n' && newc != SEOF_0 && newc != SEOF_255);
				readerRetract(sourceBuffer);
				return currentToken;
			}
			//multi line comment
			do {
				newc = readerGetChar(sourceBuffer);
				if (newc == '*') {
					if (readerGetChar(sourceBuffer) == '/') break;
					//false alarm
					readerRetract(sourceBuffer);
					continue;
				}
				/*if (newc == SEOF_0 || newc == SEOF_255) {
					//give EOF in comment warning
				}*/
			} while (newc != SEOF_0 && newc != SEOF_255);
			return currentToken;

		/* Cases for END OF FILE */
		case CHARSEOF0:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_0;
			return currentToken;
		case CHARSEOF255:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_255;
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO: Adjust / check the logic for your language */

		default: // general case
			state = nextState(state, c);
			lexStart = readerGetPosRead(sourceBuffer) - 1;
			readerSetMark(sourceBuffer, lexStart);
			int pos = 0;
			while (stateType[state] == NOFS) {
				c = readerGetChar(sourceBuffer);
				if (c == '\n') printf("newline\n");
				state = nextState(state, c);
				pos++;
			}
			if (stateType[state] == FSWR)
				readerRetract(sourceBuffer);
			lexEnd = readerGetPosRead(sourceBuffer);
			lexLength = lexEnd - lexStart;
			lexemeBuffer = readerCreate((arrow_int)lexLength + 2, 0, MODE_FIXED);
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}
			readerRestore(sourceBuffer);
			for (i = 0; i < lexLength; i++)
				readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
			readerAddChar(lexemeBuffer, READER_TERMINATOR);
			currentToken = (*finalStateTable[state])(readerGetContent(lexemeBuffer, 0));
			readerRestore(lexemeBuffer); //xxx
			return currentToken;
		} // switch

	} //while

} // tokenizer


/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */

arrow_int nextState(arrow_int state, arrow_char c) {
	arrow_int col;
	arrow_int next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
}

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
/* TO_DO: Use your column configuration */

/* Adjust the logic to return next column in TT */
/*	[A-z](0), [0-9](1),	_(2), &(3), "(4), SEOF(5), other(6) */

arrow_int nextClass(arrow_char c) {
	arrow_int val = -1;
	switch (c) {
	case CHRCOL2:
		val = 2;
		break;
	case CHRCOL4:
		val = 4;
		break;
	case CHRCOL5:
		val = 5;
		break;
	case CHRCOL6:
		val = 6;
		break;
	case CHRCOL7:
		val = 7;
		break;
	case CHRCOL8:
		val = 8;
		break;
	case CHARSEOF0:
	case CHARSEOF255:
		val = 12;
		break;
	default:
		if (c > 127 || c < 0)
			val = OTHERCOL;
		else if (isupper(c))
			val = 0;
		else if (islower(c))
			val = 1;
		else if (isdigit(c))
			val = 3;
		else
			val = OTHERCOL;
	}
	return val;
}


 /*
  ************************************************************
  * Acceptance State Function IL
  *		Function responsible to identify IL (integer literals).
  * - It is necessary respect the limit (ex: 2-byte integer in C).
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for IL */

Token funcIL(arrow_char lexeme[]) {
	Token currentToken = { 0 };
	arrow_int tlong; //arrow only uses longs (no ints)
	if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ESNR])(lexeme);
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = INL_T;
			currentToken.attribute.intValue = (arrow_int)tlong;
		}
		else {
			currentToken = (*finalStateTable[ESNR])(lexeme);
		}
	}
	return currentToken;
}


/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */

Token funcVoMID(arrow_char lexeme[]) {
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	currentToken.code = VoMID_T;
	strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
	currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table 
 *   (stringLiteralTable). You need to include the literals in 
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
/* TO_DO: Adjust the function for SL */

Token funcSL(arrow_char lexeme[]) {
	Token currentToken = { 0 };
	arrow_int i = 0, len = (arrow_int)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
		currentToken.code = RTE_T;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	currentToken.code = STR_T;
	return currentToken;
}

/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */

Token funcKEY(arrow_char lexeme[]) {
	Token currentToken = { 0 };
	arrow_int kwindex = -1, j = 0;
	if (!strcmp(lexeme, "true")) {
		currentToken.code = BOOL_T;
		currentToken.attribute.boolValue = ARROW_TRUE;
		return currentToken;
	}
	if (!strcmp(lexeme, "false")) {
		currentToken.code = BOOL_T;
		currentToken.attribute.boolValue = ARROW_FALSE;
		return currentToken;
	}
	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KW_T;
		currentToken.attribute.codeType = kwindex;
	}
	else {
		currentToken = funcVoMID(lexeme);
	}
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */

Token funcErr(arrow_char lexeme[]) {
	Token currentToken = { 0 };
	arrow_int i = 0, len = (arrow_int)strlen(lexeme);
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = CHARSEOF0;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == '\n')
			line++;
	currentToken.code = ERR_T;
	return currentToken;
}

Token funcIntLiteral(arrow_char lexeme[]) {
	Token currentToken = { 0 };
	arrow_int i = 0, len = (arrow_int)strlen(lexeme);
	currentToken.code = INTLIT_T;
	currentToken.attribute.intValue = 0;
	for (i = 0; i < len; i++) {
		currentToken.attribute.intValue *= 10;
		currentToken.attribute.intValue += lexeme[i] - '0';
	}
	return currentToken;
}

Token funcFloatLiteral(arrow_char lexeme[]) {
	Token currentToken = { 0 };
	arrow_int i = 0, len = (arrow_int)strlen(lexeme);
	currentToken.code = FLOATLIT_T;
	currentToken.attribute.floatValue = atof(lexeme);
	return currentToken;
}

/*
Token BoolLiteral(arrow_char lexeme[]) {
	Token currentToken = { 0 };
	arrow_int i = 0, len = (arrow_int)strlen(lexeme);
	currentToken.code = INTLIT_T;
	currentToken.attribute.intValue = 0;
	for (i = 0; i < len; i++) {
		currentToken.attribute.intValue *= 10;
		currentToken.attribute.intValue += lexeme[i] - '0';
	}
	return currentToken;
}*/

Token funcRelOp(arrow_char lexeme[]) {
	Token currentToken = { 0 };
	currentToken.code = RELOP_T;
	if (!strcmp(lexeme, "...")) {
		currentToken.attribute.relationalOperator = OP_SPREAD;
	}
	else if (!strcmp(lexeme, "..")) {
		currentToken.attribute.relationalOperator = OP_CONCAT;
	}
	return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

arrow_void printToken(Token t) {

	/* External variables */
	extern arrow_char* keywordTable[]; /* link to keyword table in */
	extern numScannerErrors;			/* link to number of errors (defined in Scanner.h) */

	switch (t.code) {
	case RTE_T:
		//numScannerErrors++;
		printf("RTE_T\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case ERR_T:
		numScannerErrors++;
		printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
		/* TO_DO: Update numScannerErrors */
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case VoMID_T:
		printf("VoMID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T\t\t%d\t ", (arrow_int)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (arrow_int)t.attribute.codeType));
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case KW_T:
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.codeType]);
		break;
	case EOS_T:
		printf("EOS_T\n");
		break;
	case COMMA_T:
		printf("COMMA_T\n");
		break;
	case LSB_T:
		printf("LSB_T\n");
		break;
	case RSB_T:
		printf("RSB_T\n");
		break;
	case COM_T:
		printf("COM_T\n");
		break;
	case BOOL_T:
		printf("BOOL_T\n");
		break;
	case INTLIT_T:
		printf("INTLIT_T\t%ld\n", t.attribute.intValue);
		break;
	case FLOATLIT_T:
		printf("FLOATLIT_T\t%f\n", t.attribute.floatValue);
		break;
	case ARITHOP_T:
		printf("ARITHOP_T\t");
		switch (t.attribute.arithmeticOperator) {
		case OP_ADD:
			printf("+\n");
			break;
		case OP_SUB:
			printf("-\n");
			break;
		case OP_MUL:
			printf("*\n");
			break;
		case OP_DIV:
			printf("/\n");
			break;
		case OP_EXP:
			printf("**\n");
			break;
		case OP_MOD:
			printf("%%\n");
			break;

		case OP_INCR:
			printf("++\n");
			break;
		case OP_DECR:
			printf("--\n");
			break;

		case OP_ADDASGN:
			printf("+=\n");
			break;
		case OP_SUBASGN:
			printf("-=\n");
			break;
		case OP_MULASGN:
			printf("*=\n");
			break;
		case OP_DIVASGN:
			printf("/=\n");
			break;
		case OP_EXPASGN:
			printf("**=\n");
			break;
		case OP_MODASGN:
			printf("%%=\n");
			break;
		}
		break;
	case RELOP_T:
		printf("RELOP_T\t\t");
		switch (t.attribute.relationalOperator) {
		case OP_EQ:
			printf("==\n");
			break;
		case OP_NE:
			printf("!=\n");
			break;
		case OP_LT:
			printf("<\n");
			break;
		case OP_LE:
			printf("<=\n");
			break;
		case OP_GT:
			printf(">\n");
			break;
		case OP_GE:
			printf(">=\n");
			break;
		case OP_CONCAT:
			printf("..\n");
			break;
		case OP_SPREAD:
			printf("...\n");
			break;
		case OP_ASGN:
			printf("=\n");
			break;
		case OP_ARROW:
			printf("=>\n");
			break;
		}
		break;
	case LOGOP_T:
		printf("LOGOP_T\t\t");
		switch (t.attribute.logicalOperator) {
		case OP_AND:
			printf("&&\n");
			break;
		case OP_OR:
			printf("||\n");
			break;
		case OP_NOT:
			printf("!\n");
			break;
		}
		break;
	case BITOP_T:
		printf("BITOP_T\t\t");
		switch (t.attribute.bitwiseOperator) {
		case OP_LSH:
			printf("<<\n");
			break;
		case OP_RSH:
			printf(">>\n");
			break;
		case OP_BNOT:
			printf("~\n");
			break;
		case OP_BAND:
			printf("&\n");
			break;
		case OP_BXOR:
			printf("^\n");
			break;
		case OP_BOR:
			printf("|\n");
			break;

		case OP_LSHASGN:
			printf("<<=\n");
			break;
		case OP_RSHASGN:
			printf(">>=\n");
			break;
		case OP_BANDASGN:
			printf("&=\n");
			break;
		case OP_BXORASGN:
			printf("^=\n");
			break;
		case OP_BORASGN:
			printf("|=\n");
			break;
		}
		break;
	case QUES_T:
		printf("QUES_T\n");
		break;
	case COL_T:
		printf("COL_T\n");
		break;
	default:
		//numScannerErrors++;
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/
