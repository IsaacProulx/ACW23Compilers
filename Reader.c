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

ReaderPointer readerCreate(julius_intg size, julius_intg increment, julius_intg mode) {
	ReaderPointer readerPointer;
	int i;
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust the values according to parameters */
	if(size<1) size = READER_DEFAULT_SIZE;
	if(increment<1) increment = READER_DEFAULT_INCREMENT;
	if(!mode) mode = MODE_FIXED;
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	if (!readerPointer) return NULL;
	readerPointer->content = (julius_char*)malloc(size);
	/* TO_DO: Defensive programming */
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	/* Initialize flags */
	/* The created flag must be signalized as EMP */
	readerPointer->flags = READER_DEFAULT_FLAG | READER_EMP;
	/* Initialize the histogram */
	for(i=0; i<NCHAR; i++){
		readerPointer->histogram[i] = 0;
	}
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

ReaderPointer readerAddChar(ReaderPointer const readerPointer, julius_char ch) {
	julius_char* tempReader = NULL;
	julius_intg newSize = 0;
	/* TO_DO: Defensive programming: check buffer and valid char (increment numReaderErrors) */
	/* TODO: Validate Buffer */
	if(!readerPointer) return NULL;
	if(!readerPointer->content) return NULL;
	if(ch>=NCHAR){
		/* Invalid Char */
		readerPointer->numReaderErrors++;
		return NULL;
	}
	/* TO_DO: Reset Realocation */
	/* x^0 = x, x^1 = !x*/
	//if(readerPointer->flags & READER_REL) readerPointer->flags ^= READER_REL;
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (julius_intg)sizeof(julius_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
		readerPointer->flags &= ~(READER_FUL|READER_REL);
	} else {
		/* TO_DO: Reset Full flag */
		/* x^0 = x, x^1 = !x*/
		if(readerPointer->flags & READER_FUL) readerPointer->flags ^= READER_FUL;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			/* TO_DO: Defensive programming */
			/* Hopefully this is correct */
			newSize = readerPointer->size + readerPointer->increment;
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			/* TO_DO: Defensive programming */
			/* Hopefully this is correct */
			newSize = readerPointer->size * readerPointer->increment;
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		/* TO_DO: Defensive programming */
		/* TO_DO: Check Relocation */
		/* Hopefully this is correct (Maybe just use realloc?)*/
		//tempReader = readerPointer->content;
		//readerPointer->content = malloc(newSize);
		//memcpy(readerPointer->content,tempReader,newSize - readerPointer->increment);
		//free(tempReader);
		tempReader = realloc(readerPointer->content, newSize);
		if (!tempReader) return NULL;
		if (memcmp(tempReader, readerPointer->content, readerPointer->size) != 0) {
			if (readerPointer->content != tempReader) free(tempReader);
			return readerPointer;
		}
		readerPointer->size = newSize;
		if (readerPointer->content != tempReader) {
			if(readerPointer->content) free(readerPointer->content);
			readerPointer->content = tempReader;
		}
		readerPointer->flags |= READER_REL;
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
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
julius_boln readerClear(ReaderPointer const readerPointer) {
	int i;
	/* TO_DO: Defensive programming */
	if(!readerPointer) return JULIUS_FALSE;

	for(i=0; i<readerPointer->size; i++) readerPointer->content[i] = 0;

	/* TO_DO: Adjust flags original */
	readerPointer->flags = READER_DEFAULT_FLAG | READER_EMP;
	return JULIUS_TRUE;
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
julius_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) return JULIUS_FALSE;
	
	/* TO_DO: Free pointers */
	if(readerPointer->content) free(readerPointer->content);
	free(readerPointer);

	return JULIUS_TRUE;
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
julius_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* Should this be false? */
	if(!readerPointer) return JULIUS_FALSE;
	/* TO_DO: Check flag if buffer is FUL */
	if(readerPointer->flags & READER_FUL) return JULIUS_TRUE;
	return JULIUS_FALSE;
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
julius_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* Should this be false? */
	if(!readerPointer) return JULIUS_FALSE;
	/* TO_DO: Check flag if buffer is EMP */
	if(readerPointer->flags & READER_EMP) return JULIUS_TRUE;
	return JULIUS_FALSE;
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
julius_boln readerSetMark(ReaderPointer const readerPointer, julius_intg mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark<0 || mark > readerPointer->position.wrte)
		return JULIUS_FALSE;
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return JULIUS_TRUE;
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
julius_intg readerPrint(ReaderPointer const readerPointer) {
	julius_intg cont = 0;
	julius_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	if(!readerPointer) return 0;
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (cont < readerPointer->position.wrte) {
		cont++;
		if(readerPointer->flags & READER_END) break;
		/* Invalid Char */
		if(c>=NCHAR) continue;
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
julius_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	julius_intg size = 0;
	julius_char c;
	/* TO_DO: Defensive programming */
	if(!readerPointer) return READER_ERROR;
	if(!fileDescriptor) return READER_ERROR;
	c = (julius_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (julius_char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
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
julius_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return JULIUS_FALSE;
	if(!readerPointer->content) return JULIUS_FALSE;
	/* TO_DO: Recover positions */
	readerPointer->position.wrte--;
	return JULIUS_TRUE;
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
julius_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return JULIUS_FALSE;
	if(!readerPointer->content) return JULIUS_FALSE;
	/* TO_DO: Retract (return 1 pos read) */
	readerPointer->position.read--;
	return JULIUS_TRUE;
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
julius_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return JULIUS_FALSE;
	if(!readerPointer->content) return JULIUS_FALSE;
	/* TO_DO: Restore positions (read/mark) */
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;
	return JULIUS_TRUE;
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
julius_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return READER_ERROR;
	if(!readerPointer->content) return READER_ERROR;
	/* TO_DO: Check condition to read/wrte */
	if(readerPointer->flags & READER_END) return 0;
	/* TO_DO: Set EOB flag */
	if(readerPointer->position.read+1 == readerPointer->size-1) readerPointer->flags |= READER_END;
	/* TO_DO: Reset EOB flag */
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
julius_char* readerGetContent(ReaderPointer const readerPointer, julius_intg pos) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return NULL;
	if(!readerPointer->content) return NULL;
	/* TO_DO: Return content (string) */
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
julius_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return READER_ERROR;
	/* TO_DO: Return read */
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
julius_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return READER_ERROR;
	/* TO_DO: Return wrte */
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
julius_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return READER_ERROR;
	/* TO_DO: Return mark */
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
julius_intg readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return READER_ERROR;
	/* TO_DO: Return size */
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
julius_intg readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return READER_ERROR;
	/* TO_DO: Return increment */
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
julius_intg readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return READER_ERROR;
	/* TO_DO: Return mode */
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
julius_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return READER_ERROR;
	/* TO_DO: Return flags */
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
julius_intg readerShowStat(ReaderPointer const readerPointer) {
	int numDiffChars = 0;
	int i;
	/* TO_DO: Defensive programming */
	if(!readerPointer) return READER_ERROR;
	/* TO_DO: Updates the histogram */
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
julius_intg readerNumErrors(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if(!readerPointer) return READER_ERROR;
	/* TO_DO: Updates the histogram */
	return readerPointer->numReaderErrors;
}
