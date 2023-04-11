/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: Isaac Proulx
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
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern arrow_int line;
extern Token tokenizer();
extern arrow_char* keywordTable[];
arrow_int syntaxErrorNumber = 0;

#define STR_LANGNAME	"Julius"
#define LANG_WRTE		"print&"
#define LANG_READ		"input&"
#define LANG_MAIN		"main&"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_let,
	KW_const,
	KW_int,
	KW_float,
	KW_string,
	KW_bool,
	KW_list,
	KW_function,
	KW_return,
	KW_if,
	KW_else,
	KW_for,
	KW_while,
	KW_break,
	KW_continue,
	KW_try,
	KW_catch,
	KW_finally
};

/* Function definitions */
arrow_void startParser();
arrow_void matchToken(arrow_int, arrow_int);
arrow_void syncErrorHandler(arrow_int);
arrow_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
arrow_void typeName();

arrow_void codeSession();
arrow_void dataSession();
arrow_void optVarListDeclarations();
arrow_void optionalStatements();
arrow_void outputStatement();
arrow_void outputVariableList();
arrow_void program();
arrow_void statement();
arrow_void statements();
arrow_void statementsPrime();
arrow_void constantDeclarationStatement();
arrow_void declarationStatement();
arrow_void declarationExpression();
arrow_void assignmentStatement();
arrow_void assignmentExpression();

arrow_void arithmeticExpression();
arrow_void additiveArithmeticExpression();
arrow_void multiplicativeArithmeticExpression();
arrow_void exponentialArithmeticExpression();
arrow_void primaryArithmeticExpression();

arrow_void relationalExpression();
arrow_void relationalAExpression();
arrow_void primaryARelationalExpression();

arrow_void bitwiseExpression();
arrow_void bitwiseOrExpression();
arrow_void bitwiseXOrExpression();
arrow_void bitwiseAndExpression();
arrow_void bitwiseNotExpression();
arrow_void primaryBitwiseExpression();

arrow_void logicalExpression();
arrow_void logicalOrExpression();
arrow_void logicalAndExpression();
arrow_void logicalNotExpression();
arrow_void primaryLogicalExpression();

arrow_void functionDeclarationStatement();
arrow_void functionParameterList();
arrow_void functionArgumentList();

arrow_void listExpression();

arrow_void arrowFunction();
#endif
