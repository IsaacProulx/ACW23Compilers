#..............................................................
# CMakeList.txt : CMake project for Compilers, W23.
#..............................................................
#
#
# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# @@@@                                                               @@@@
# @@          /       ==============================        /          @@
# @         ////           @@       @@ #@                  ////         @
# @         ////*          @@ @%  @ @@    @@  @ #@#       /////         @
# @     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @
# @     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @
# @     (((((/)))((    ------------------------------    ((((./////*    @
# @    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @
# @    ///// / /////   ==============================  * ////* / ////   @
# @     ///// ///// ((                               (( ///// /////     @
# @    ((((   / , (((((                             (((((  //   /(((    @
# @    (((((((/ . (((((                          (((((* / (((((((       @
# @      (((((( //((((/((((                    *((((/((((/( (((((/      @
# @       .//,   * /   (((((                   (((((  ///    .//.       @
# @     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @
# @         //////// ,// ((( /////,     ////// ((( //  /////// *        @
# @            (((((((((,// * /////     /////   (//(((((((((            @
# @            ((((((((((((/////         //.///  (((((((((((.           @
# @                   (///////// //(   (//.//////////                   @
# @                  (/////////             //////////                  @
# @                                                                     @
# @@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@
# @@@@                                                               @@@@
# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#

cmake_minimum_required (VERSION 3.8)

project ("ArrowCompiler")

#set(COMPILE_OPTIONS "${COMPILE_OPTIONS} -std=gnu89 -ansi")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu89 -pedantic-errors")
# Add source to this project's executable: check name and dependences
add_executable (ArrowCompiler
	"Compilers.h"	"Compilers.c"
	"Reader.h"		"Reader.c"		"MainReader.c"
#"		"Scanner.c"		"MainScanner.c"
#	"Parser.h"		"Parser.c"		"MainParser.c"
)

# TO_DO: Add tests and install targets if needed.
set_property(TARGET ArrowCompiler PROPERTY C_STANDARD 90)
set_property(TARGET ArrowCompiler PROPERTY C_STANDARD_REQUIRED ON)
#set_property(TARGET JuliusCompiler PROPERTY CXX_STANDARD 90)
#set_property(TARGET JuliusCompiler PROPERTY CXX_STANDARD_REQUIRED ON)