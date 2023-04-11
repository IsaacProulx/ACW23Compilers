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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

arrow_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
arrow_void matchToken(arrow_int tokenCode, arrow_int tokenAttribute) {
	arrow_int matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
arrow_void syncErrorHandler(arrow_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
arrow_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case COM_T:
		printf("COM_T\n");
		break;
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case VoMID_T:
		printf("VoMID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
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
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
arrow_void program() {
	for (;;) {
		//printf("%d\n", lookahead.code);
		switch (lookahead.code) {
		case SEOF_T:
			printf("%s%s\n", STR_LANGNAME, ": Program parsed");
			return;
		default:
			statements(ARROW_FALSE);
			break;
		}
	}
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
arrow_void statements(arrow_bool inFunction) {
	while (lookahead.code == COM_T) {
		matchToken(COM_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
	}
	statement(inFunction);
	//statementsPrime();
	//printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
arrow_void statementsPrime() {
	switch (lookahead.code) {
	case VoMID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements(ARROW_FALSE);
			break;
		}
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <declaration statement> | <assignment statement> | <conditional statement> |
 *	<iteration statement> | <function call statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
arrow_void statement(arrow_bool inFunction) {
	//printf("Thing: %d\n", lookahead.attribute.codeType);
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_let:
			declarationStatement();
			break;
		case KW_const:
			constantDeclarationStatement();
			break;
		case KW_function:
			functionDeclarationStatement();
			return;
		case KW_return:
			if (inFunction == ARROW_FALSE) {
				printf("return outside of function\n");
				printError();
				break;
			}
			matchToken(KW_T, KW_return);
			logicalExpression();
			printf("%s%s\n", STR_LANGNAME, ": Return statement parsed");
			break;
		case KW_for:
			matchToken(KW_T, KW_for);
			matchToken(LPR_T, NO_ATTR);
			printf("for\n");
			if (lookahead.code == KW_T) {
				if (lookahead.attribute.codeType == KW_let) declarationStatement();
				else if (lookahead.attribute.codeType == KW_const) constantDeclarationStatement();
			}
			matchToken(EOS_T, NO_ATTR);
			relationalExpression();
			matchToken(EOS_T, NO_ATTR);
			assignmentExpression();
			matchToken(RPR_T, NO_ATTR);
			matchToken(LBR_T, NO_ATTR);
			while (lookahead.code != RBR_T) statements(ARROW_FALSE);
			matchToken(RBR_T, NO_ATTR);

			printf("%s%s\n", STR_LANGNAME, ": For loop parsed");
			break;
		default:
			printError();
		}
		break;
	case VoMID_T:
		matchToken(VoMID_T,NO_ATTR);
		switch (lookahead.code) {
		case LPR_T:
			matchToken(LPR_T, NO_ATTR);
			functionArgumentList();
			matchToken(RPR_T, NO_ATTR);
			printf("%s%s\n", STR_LANGNAME, ": Function Call statement parsed");
			break;
		default:
			printf("test\n");
		}
		break;
	default:
		printError();
	}
	matchToken(EOS_T, NO_ATTR);
	//printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

arrow_void functionArgumentList() {
	switch (lookahead.code) {
	case INTLIT_T:
		matchToken(INTLIT_T, NO_ATTR);
		break;
	case FLOATLIT_T:
		matchToken(FLOATLIT_T, NO_ATTR);
		break;
	case BOOL_T:
		matchToken(BOOL_T, NO_ATTR);
		break;
	case LSB_T:
		listExpression();
		break;
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case VoMID_T:
		matchToken(VoMID_T, NO_ATTR);
		if (lookahead.code == LPR_T) {
			matchToken(LPR_T, NO_ATTR);
			functionArgumentList();
			matchToken(RPR_T, NO_ATTR);
			printf("%s%s\n", STR_LANGNAME, ": Function Call expression parsed");
		}
		break;
	default:
		return;
	}
	if (lookahead.code == COMMA_T) {
		matchToken(COMMA_T, NO_ATTR);
		functionArgumentList();
	}
}

arrow_void listExpression() {
	matchToken(LSB_T, NO_ATTR);
	functionArgumentList();
	matchToken(RSB_T, NO_ATTR);
}

arrow_void typeName() {
	switch (lookahead.attribute.codeType) {
	case KW_int:
		matchToken(KW_T, KW_int);
		break;
	case KW_float:
		matchToken(KW_T, KW_float);
		break;
	case KW_bool:
		matchToken(KW_T, KW_bool);
		break;
	case KW_string:
		matchToken(KW_T, KW_string);
		break;
	case KW_list:
		matchToken(KW_T, KW_list);
		break;
	default:
		printError();
	}
}

arrow_void functionParameterList() {
	if (lookahead.code == KW_T) {
		typeName();
		matchToken(VoMID_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Function Parameter parsed");
		if (lookahead.code == COMMA_T) {
			matchToken(COMMA_T, NO_ATTR);
			functionParameterList();
		}
	}
}

arrow_void functionDeclarationStatement() {
	matchToken(KW_T, KW_function);
	typeName();
	matchToken(VoMID_T,NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	functionParameterList();
	matchToken(RPR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Function Declaration parsed");
	matchToken(LBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Function body start");
	while (lookahead.code != RBR_T) {
		statements(ARROW_TRUE);
	}
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Function body end");
}

arrow_void constantDeclarationStatement() {
	matchToken(KW_T, KW_const);
	typeName();
	assignmentStatement();
	printf("%s%s\n", STR_LANGNAME, ": Constant Declaration statement parsed");
}

arrow_void declarationStatement() {
	matchToken(KW_T, KW_let);
	declarationExpression();
	printf("%s%s\n", STR_LANGNAME, ": Declaration expression parsed");
}

arrow_void declarationExpression() {
	typeName();
	matchToken(VoMID_T, NO_ATTR);
	if (lookahead.code == RELOP_T) assignmentExpression();
}

arrow_void assignmentStatement() {
	if (lookahead.code == ARITHOP_T) {
		if (lookahead.attribute.arithmeticOperator == OP_INCR) {
			matchToken(ARITHOP_T,OP_INCR);
			matchToken(VoMID_T, NO_ATTR);
			//if(lookahead.attribute.relationalOperator == OP_) assignmentExpression();
			return;
		}
		else if (lookahead.attribute.arithmeticOperator == OP_DECR) {
			matchToken(ARITHOP_T, OP_DECR);
			matchToken(VoMID_T, NO_ATTR);
			//assignmentExpression();
			return;
		}
	}
	matchToken(VoMID_T, NO_ATTR);
	assignmentExpression();
}

/*
 ************************************************************
 * Assignment Expression
 * BNF: <assignment expression> -> <variable identifier> = <variable identifier>
					| <variable identifier> = <arithmetic expression>
					| <variable identifier> = <assignment expression>
					| <variable identifier> = <arrow function>
 ************************************************************
 */
arrow_void assignmentExpression() {
	matchToken(RELOP_T, OP_ASGN);
	switch (lookahead.code) {
	case VoMID_T:
		matchToken(VoMID_T, NO_ATTR);
		switch (lookahead.code) {
		case EOS_T:	
			matchToken(EOS_T, NO_ATTR);
			break;
		case LBR_T:
			//list();
			break;
		case LPR_T:
			matchToken(LPR_T, NO_ATTR);
			functionArgumentList();
			matchToken(RPR_T, NO_ATTR);
			printf("%s%s\n", STR_LANGNAME, ": Function Call expression parsed");
			break;
		case RELOP_T:
			assignmentExpression();
			break;
		default:
			logicalExpression();
		}
		break;
	case LBR_T:
		//list();
		break;
	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		if (lookahead.code == KW_T) {
			functionParameterList();
			matchToken(RPR_T, NO_ATTR);
			if (lookahead.code == RELOP_T && lookahead.attribute.relationalOperator == OP_ARROW) {
				arrowFunction();
				return;
			}
			return;
		}
		matchToken(RPR_T, NO_ATTR);
		break;
	default:
		logicalExpression();
	}
}

arrow_void arithmeticExpression() {
	additiveArithmeticExpression();
}

arrow_void additiveArithmeticExpression() {
	multiplicativeArithmeticExpression();
	if (lookahead.code == ARITHOP_T) {
		switch (lookahead.attribute.arithmeticOperator) {
		case OP_MUL:
			matchToken(ARITHOP_T, OP_ADD);
			break;
		case OP_DIV:
			matchToken(ARITHOP_T, OP_SUB);
			break;
		default:
			return;
		}
		additiveArithmeticExpression();
		printf("%s%s\n", STR_LANGNAME, ": Additive Arithmetic Expression parsed");
	}
}

arrow_void multiplicativeArithmeticExpression() {
	exponentialArithmeticExpression();
	if (lookahead.code == ARITHOP_T) {
		switch (lookahead.attribute.arithmeticOperator) {
		case OP_MUL:
			matchToken(ARITHOP_T, OP_MUL);
			break;
		case OP_DIV:
			matchToken(ARITHOP_T, OP_MUL);
			break;
		case OP_MOD:
			matchToken(ARITHOP_T, OP_MUL);
			break;
		default:
			return;
		}
		multiplicativeArithmeticExpression();
		printf("%s%s\n", STR_LANGNAME, ": Multiplicative Arithmetic Expression parsed");
	}
}

arrow_void exponentialArithmeticExpression() {
	primaryArithmeticExpression();
	if (lookahead.code == ARITHOP_T && lookahead.attribute.arithmeticOperator == OP_EXP) {
		matchToken(ARITHOP_T, OP_EXP);
		exponentialArithmeticExpression();
		printf("%s%s\n", STR_LANGNAME, ": Exponential Arithmetic Expression parsed");
	}
}

arrow_void primaryArithmeticExpression() {
	switch(lookahead.code){
		case LPR_T: 
			matchToken(LPR_T, NO_ATTR);
			relationalAExpression();
			matchToken(RPR_T, NO_ATTR);
			break;
		case VoMID_T:
			matchToken(VoMID_T, NO_ATTR);
			break;
		case INTLIT_T:
			matchToken(INTLIT_T,NO_ATTR);
			break;
		case FLOATLIT_T:
			matchToken(FLOATLIT_T, NO_ATTR);
			break;
		case BOOL_T:
			matchToken(BOOL_T, NO_ATTR);
			break;
	}
}

arrow_void relationalExpression() {
	relationalAExpression();
}

arrow_void relationalAExpression() {
	primaryARelationalExpression();
	if (lookahead.code == RELOP_T) {
		matchToken(RELOP_T, NO_ATTR);
		relationalAExpression();
		printf("%s%s\n", STR_LANGNAME, ": Arithmetic Relational Expression parsed");
	}
}

arrow_void primaryARelationalExpression() {
	if (lookahead.code == LPR_T) {
		matchToken(LPR_T, NO_ATTR);
		bitwiseExpression();
		matchToken(RPR_T, NO_ATTR);
	}
	else arithmeticExpression();
}

arrow_void bitwiseExpression() {
	bitwiseOrExpression();
}

arrow_void bitwiseOrExpression() {
	bitwiseXOrExpression();
	if (lookahead.code == BITOP_T && lookahead.attribute.bitwiseOperator == OP_BOR) {
		matchToken(BITOP_T, OP_BOR);
		bitwiseOrExpression();
		printf("%s%s\n", STR_LANGNAME, ": Bitwise Or Expression parsed");
	}
}

arrow_void bitwiseXOrExpression() {
	bitwiseAndExpression();
	if (lookahead.code == BITOP_T && lookahead.attribute.bitwiseOperator == OP_BXOR) {
		matchToken(BITOP_T, OP_BXOR);
		bitwiseXOrExpression();
		printf("%s%s\n", STR_LANGNAME, ": Bitwise XOr Expression parsed");
	}
}

arrow_void bitwiseAndExpression() {
	bitwiseNotExpression();
	if (lookahead.code == BITOP_T && lookahead.attribute.bitwiseOperator == OP_BAND) {
		matchToken(BITOP_T, OP_BAND);
		bitwiseAndExpression();
		printf("%s%s\n", STR_LANGNAME, ": Bitwise And Expression parsed");
	}
}

arrow_void bitwiseNotExpression() {
	if (lookahead.code == BITOP_T && lookahead.attribute.bitwiseOperator == OP_BNOT) {
		matchToken(BITOP_T, OP_BNOT);
		bitwiseNotExpression();
		printf("%s%s\n", STR_LANGNAME, ": Bitwise Not Expression parsed");
	}
	else primaryBitwiseExpression();
}

arrow_void primaryBitwiseExpression() {
	if (lookahead.code == LPR_T) {
		matchToken(LPR_T, NO_ATTR);
		logicalExpression();
		matchToken(RPR_T, NO_ATTR);
	}
	else relationalExpression();
}

arrow_void logicalExpression() {
	logicalOrExpression();
}

arrow_void logicalOrExpression() {
	logicalAndExpression();
	if (lookahead.code == LOGOP_T && lookahead.attribute.logicalOperator == OP_OR) {
		matchToken(LOGOP_T, OP_OR);
		logicalOrExpression();
		printf("%s%s\n", STR_LANGNAME, ": Logical Or Expression parsed");
	}
}

arrow_void logicalAndExpression() {
	logicalNotExpression();
	if (lookahead.code == LOGOP_T && lookahead.attribute.logicalOperator == OP_AND) {
		matchToken(LOGOP_T, OP_AND);
		logicalAndExpression();
		printf("%s%s\n", STR_LANGNAME, ": Logical And Expression parsed");
	}
}

arrow_void logicalNotExpression() {
	if (lookahead.code == LOGOP_T && lookahead.attribute.logicalOperator == OP_NOT) {
		matchToken(LOGOP_T, OP_NOT);
		logicalNotExpression();
		printf("%s%s\n", STR_LANGNAME, ": Logical Not Expression parsed");
	}
	else primaryLogicalExpression();
}

arrow_void primaryLogicalExpression() {
	if (lookahead.code == LPR_T) {
		matchToken(LPR_T, NO_ATTR);
		logicalExpression();
		matchToken(RPR_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Logical Expression parsed");
	}
	else bitwiseExpression();
}

arrow_void arrowFunction() {
	matchToken(RELOP_T, OP_ARROW);
	matchToken(LBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Arrow Function body start");
	while (lookahead.code != RBR_T) {
		statements(ARROW_TRUE);
	}
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Arrow Function body end");
}
/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
arrow_void outputStatement() {
	matchToken(VoMID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
arrow_void outputVariableList() {
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}
