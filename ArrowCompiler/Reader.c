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
* Purpose: This file is the main code for Reader (.c)
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
#include "Reader.h"
#endif

#ifndef memcpy
#include "string.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

ReaderPointer readerCreate(arrow_int size, arrow_int increment, arrow_int mode) {
	ReaderPointer readerPointer;
	int i;
	
	if(size<1) size = READER_DEFAULT_SIZE;
	if(increment<1) increment = READER_DEFAULT_INCREMENT;
	if(!mode) mode = MODE_FIXED;

	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	if (!readerPointer) return NULL;

	readerPointer->content = (arrow_char*)malloc(size);
	if (!readerPointer->content) return NULL;

	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	/* Initialize flags */
	readerPointer->flags = READER_DEFAULT_FLAG | READER_EMP;
	/* Initialize the histogram */
	for(i=0; i<NCHAR; i++) readerPointer->histogram[i] = 0;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, arrow_char ch) {
	arrow_char* tempReader = NULL;
	arrow_int newSize = 0L;
	/* check buffer and valid char (increment numReaderErrors) */
	if(!readerPointer) return NULL;
	if(!readerPointer->content || ch>NCHAR-1){
		readerPointer->numReaderErrors++;
		return NULL;
	}
	/* TO_DO: Reset Realocation */
	/* TO_DO: Test the inclusion of chars */
	readerPointer->flags &= ~READER_REL;
	if (readerPointer->position.wrte * (arrow_int)sizeof(arrow_char) < readerPointer->size - (arrow_int)sizeof(arrow_char)) {
		/* TO_DO: This buffer is NOT full */
		readerPointer->flags &= ~READER_FUL;
	} else {
		/* Full flag */
		readerPointer->flags &= ~READER_FUL;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			readerPointer->flags |= READER_FUL;
			if (ch == READER_TERMINATOR) {
				readerPointer->content[readerPointer->position.wrte++] = ch;
				return readerPointer;
			}
			return NULL;
		case MODE_ADDIT:
			newSize = readerPointer->size + readerPointer->increment;
			break;
		case MODE_MULTI:
			newSize = readerPointer->size * readerPointer->increment;
			break;
		default:
			return NULL;
		}
		if (newSize < 0L || newSize < readerPointer->size) return NULL;
		/* New reader allocation */
		tempReader = realloc(readerPointer->content, newSize);
		if (!tempReader) return NULL;
		if (memcmp(tempReader, readerPointer->content, readerPointer->size) != 0) {
			free(tempReader);
			return readerPointer;
		}
		readerPointer->size = newSize;
		if (readerPointer->content != tempReader) {
			//if(readerPointer->content) free(readerPointer->content);
			readerPointer->content = tempReader;
		}
		readerPointer->flags |= READER_REL;
	}
	/* Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* Update histogram */
	readerPointer->flags &= ~READER_EMP;
	readerPointer->histogram[ch]++;
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_bool readerClear(ReaderPointer const readerPointer) {
	int i;
	if(!readerPointer) return ARROW_FALSE;

	for(i=0; i<readerPointer->size; i++) readerPointer->content[i] = 0;

	/* Adjust flags original */
	readerPointer->flags = READER_DEFAULT_FLAG | READER_EMP;
	return ARROW_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_bool readerFree(ReaderPointer const readerPointer) {
	if (!readerPointer) return ARROW_FALSE;
	
	/* Free pointers */
	if(readerPointer->content) free(readerPointer->content);
	free(readerPointer);

	return ARROW_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_bool readerIsFull(ReaderPointer const readerPointer) {
	if(!readerPointer) return ARROW_FALSE;
	/* Check flag if buffer is FUL */
	if(readerPointer->flags & READER_FUL) return ARROW_TRUE;
	return ARROW_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_bool readerIsEmpty(ReaderPointer const readerPointer) {
	if(!readerPointer) return ARROW_FALSE;
	/* Check flag if buffer is EMP */
	if(readerPointer->flags & READER_EMP) return ARROW_TRUE;
	return ARROW_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_bool readerSetMark(ReaderPointer const readerPointer, arrow_int mark) {
	if (!readerPointer || mark<0L || mark > readerPointer->position.wrte) return ARROW_FALSE;
	/* Adjust mark */
	readerPointer->position.mark = mark;
	return ARROW_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_int readerPrint(ReaderPointer const readerPointer) {
	arrow_int cont = 0L;
	arrow_char c;
	if(!readerPointer || readerIsEmpty(readerPointer)) return cont;

	c = readerGetChar(readerPointer);
	while (cont < readerPointer->position.wrte) {
		if(readerPointer->flags & READER_END) break;
		if(c>=NCHAR) continue; /* Invalid Char */
		cont++;
		/* Valid Char */
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	a specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_int readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	arrow_int size = 0L;
	arrow_char c;
	
	if(!readerPointer || !fileDescriptor) return READER_ERROR;
	c = (arrow_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			fseek(fileDescriptor, 2, SEEK_CUR);
			//return READER_ERROR;
		}else size++;
		c = (arrow_char)fgetc(fileDescriptor);
	}
	/* TO_DO: Defensive programming */
	//if (size < 0) return READER_ERROR;
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_bool readerRecover(ReaderPointer const readerPointer) {
	if(!readerPointer || !readerPointer->content) return ARROW_FALSE;
	/* Recover positions */
	readerPointer->position.mark = 0;
	readerPointer->position.read = 0;
	//readerPointer->position.wrte = 0;
	return ARROW_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_bool readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return ARROW_FALSE;
	if(!readerPointer->content) return ARROW_FALSE;
	/* TO_DO: Retract (return 1 pos read) */
	readerPointer->position.read--;
	return ARROW_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_bool readerRestore(ReaderPointer const readerPointer) {
	if(!readerPointer || !readerPointer->content) return ARROW_FALSE;
	/* Restore positions (read -> mark) */
	readerPointer->position.read = readerPointer->position.mark;
	return ARROW_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_char readerGetChar(ReaderPointer const readerPointer) {
	if(!readerPointer || !readerPointer->content) return READER_ERROR;
	/* Check condition to read/wrte */
	//if(readerPointer->flags & READER_END) return EOF;
	/* Set EOB flag */
	if(readerPointer->position.read+1 == readerPointer->size-1) readerPointer->flags |= READER_END;
	
	return readerPointer->content[readerPointer->position.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_char* readerGetContent(ReaderPointer const readerPointer, arrow_int pos) {
	if(!readerPointer || !readerPointer->content) return NULL;
	/* Return content (string) */
	return readerPointer->content + pos;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_int readerGetPosRead(ReaderPointer const readerPointer) {
	if(!readerPointer) return READER_ERROR;
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_int readerGetPosWrte(ReaderPointer const readerPointer) {
	if(!readerPointer) return READER_ERROR;
	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_int readerGetPosMark(ReaderPointer const readerPointer) {
	if(!readerPointer) return READER_ERROR;
	return readerPointer->position.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_int readerGetSize(ReaderPointer const readerPointer) {
	if(!readerPointer) return READER_ERROR;
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_int readerGetInc(ReaderPointer const readerPointer) {
	if (!readerPointer) return READER_ERROR;
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_int readerGetMode(ReaderPointer const readerPointer) {
	if(!readerPointer) return READER_ERROR;
	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_byte readerGetFlags(ReaderPointer const readerPointer) {
	if(!readerPointer) return READER_ERROR;
	return readerPointer->flags;
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_int readerShowStat(ReaderPointer const readerPointer) {
	int numDiffChars = 0;
	int i;
	if(!readerPointer) return READER_ERROR;
	/* Count number of unique chars*/
	for(i=0; i<NCHAR; i++) if(readerPointer->histogram[i] != 0) numDiffChars++;
	return numDiffChars;
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
arrow_int readerNumErrors(ReaderPointer const readerPointer) {
	if(!readerPointer) return READER_ERROR;
	return readerPointer->numReaderErrors;
}
