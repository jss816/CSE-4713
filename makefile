###############################################################################
# purpose: makefile for Project Part 2
# author:  Joe Crumpton
#
# 'make'        build executable file
# 'make clean'  removes all intermediate (lex.yy.c and *.o) and executable files
#
# This makefile purposely avoids macros to make the rules more clear.
# For more information about makefiles:
#      http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#      http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#      http://www.gnu.org/software/make/manual/make.html
#
###############################################################################

# variables used in the following rules
LEX      = flex
CXX      = g++
CC       = gcc
RM       = rm
# generate debug information for gdb
CXXFLAGS = -g
CCFLAGS  = -g


parse.exe: lex.yy.o driver.o
	$(CXX) $(CXXFLAGS) -o parse.exe lex.yy.o driver.o

#     -o flag specifies the output file
#
#     The above rule could be written with macros as
#        $(CXX) $(CXXFLAGS) -o $@ $^

#can make a productions.o line
driver.o: driver.cpp productions.h lexer.h
	$(CXX) $(CXXFLAGS) -o driver.o -c driver.cpp

#      -c flag specifies stop after compiling, do not link

lex.yy.o: lex.yy.c lexer.h
	$(CC) $(CCFLAGS) -o lex.yy.o -c lex.yy.c

lex.yy.c: rules.l lexer.h
	$(LEX) -o lex.yy.c rules.l

clean: 
	$(RM) *.o lex.yy.c parse.exe

