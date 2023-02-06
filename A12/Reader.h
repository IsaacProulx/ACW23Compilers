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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Jan 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
#define READER_FUL 0x80 /* BIT 7: FUL = Full */
#define READER_EMP 0x40 /* BIT 6: EMP: Empty */
#define READER_REL 0x20 /* BIT 5: REL = Relocation */
#define READER_END 0x10 /* BIT 4: END = EndOfBuffer */

#define NCHAR				128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME .................................. */

/* Offset declaration */
typedef struct position {
	arrow_int mark;			/* the offset to the mark position (in chars) */
	arrow_int read;			/* the offset to the get a char position (in chars) */
	arrow_int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	arrow_char*		content;			/* pointer to the beginning of character array (character buffer) */
	arrow_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	arrow_int		increment;			/* character array increment factor */
	arrow_int		mode;				/* operational mode indicator */
	arrow_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;			/* Offset / position field */
	arrow_int		histogram[NCHAR];	/* Statistics of chars */
	arrow_int		numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
//intellisense doesn't understand that this is a prototype
ReaderPointer	readerCreate		(arrow_int, arrow_int, arrow_int);
ReaderPointer	readerAddChar		(ReaderPointer const, arrow_char);
arrow_bool		readerClear		    (ReaderPointer const);
arrow_bool		readerFree		    (ReaderPointer const);
arrow_bool		readerIsFull		(ReaderPointer const);
arrow_bool		readerIsEmpty		(ReaderPointer const);
arrow_bool		readerSetMark		(ReaderPointer const, arrow_int);
arrow_int		readerPrint		    (ReaderPointer const);
arrow_int		readerLoad			(ReaderPointer const, FILE* const);
arrow_bool		readerRecover		(ReaderPointer const);
arrow_bool		readerRetract		(ReaderPointer const);
arrow_bool		readerRestore		(ReaderPointer const);
/* Getters */
arrow_char		readerGetChar		(ReaderPointer const);
arrow_char*		readerGetContent	(ReaderPointer const, arrow_int);
arrow_int		readerGetPosRead	(ReaderPointer const);
arrow_int		readerGetPosWrte	(ReaderPointer const);
arrow_int		readerGetPosMark	(ReaderPointer const);
arrow_int		readerGetSize		(ReaderPointer const);
arrow_int		readerGetInc		(ReaderPointer const);
arrow_int		readerGetMode		(ReaderPointer const);
arrow_byte		readerGetFlags		(ReaderPointer const);
arrow_int		readerShowStat		(ReaderPointer const);
arrow_int		readerNumErrors		(ReaderPointer const);

#endif
