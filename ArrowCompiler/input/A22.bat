:: COMPILERS COURSE - SCRIPT ---------------------------------------------
:: SCRIPT A22 - CST8152 - Winter 2023

CLS
SET CWD="%~dp0\"
SET COMPILER=%CWD%"..\out\build\x64-Debug\ArrowCompiler.exe"
SET FILE1=%CWD%INPUT1_Hello
SET FILE2=%CWD%INPUT2_Volume
SET FILE3=%CWD%INPUT3_Factorial
SET FILE4=%CWD%INPUT4_Datatypes
SET FILE5=%CWD%INPUT5_General
SET FILE6=%CWD%INPUT6_Err1Reader
SET FILE7=%CWD%INPUT10_Sin

SET ASSIGNMENT=A22
SET EXTENSION=aro
SET OUTPUT=out
SET ERROR=err

SET PARAM=S

:: ---------------------------------------------------------------------
:: Begin of Tests (A22 - W22) ------------------------------------------
:: ---------------------------------------------------------------------

@echo off

ECHO "                                                                       "
ECHO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
ECHO "@@@@                                                               @@@@"
ECHO "@@          /       ==============================        /          @@"
ECHO "@         ////           @@       @@ #@                  ////         @"
ECHO "@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @"
ECHO "@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @"
ECHO "@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @"
ECHO "@     (((((/)))((    ------------------------------    ((((./////*    @"
ECHO "@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @"
ECHO "@    ///// / /////   ==============================  * ////* / ////   @"
ECHO "@     ///// ///// ((                               (( ///// /////     @"
ECHO "@    ((((   / , (((((                             (((((  //   /(((    @"
ECHO "@    (((((((/ . (((((                          (((((* / (((((((       @"
ECHO "@      (((((( //((((/((((                    *((((/((((/( (((((/      @"
ECHO "@       .//,   * /   (((((                   (((((  ///    .//.       @"
ECHO "@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @"
ECHO "@         //////// ,// ((( /////,     ////// ((( //  /////// *        @"
ECHO "@            (((((((((,// * /////     /////   (//(((((((((            @"
ECHO "@            ((((((((((((/////         //.///  (((((((((((.           @"
ECHO "@                   (///////// //(   (//.//////////                   @"
ECHO "@                  (/////////             //////////                  @"
ECHO "@                                                                     @"
ECHO "@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@"
ECHO "@@@@                                                               @@@@"
ECHO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
ECHO "                                                                       "
ECHO "[SCANNER SCRIPT ......................................................]"
ECHO "                                                                       "

rem ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A22 - W22) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %FILE1%.%EXTENSION%	> %FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE2%.%EXTENSION%	> %FILE2%-%ASSIGNMENT%.%OUTPUT%	2> %FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE3%.%EXTENSION%	> %FILE3%-%ASSIGNMENT%.%OUTPUT%	2> %FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE4%.%EXTENSION%	> %FILE4%-%ASSIGNMENT%.%OUTPUT%	2> %FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE5%.%EXTENSION%	> %FILE5%-%ASSIGNMENT%.%OUTPUT%	2> %FILE5%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> %FILE6%-%ASSIGNMENT%.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE7%.%EXTENSION%	> %FILE7%-%ASSIGNMENT%.%OUTPUT%	2> %FILE7%-%ASSIGNMENT%.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: ---------------------------------------------------------------------
:: End of Tests (A22 - W22) --------------------------------------------
:: ---------------------------------------------------------------------
