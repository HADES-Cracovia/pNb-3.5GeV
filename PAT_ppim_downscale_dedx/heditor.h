// (editor.h)
// ****************************************************************************
//  Module: editor
//  Files: editor.h, editor.cc - source
//  Version: 1.0
//  Last changes: 13 May 2010
//  Author: Witold Przygoda (przygoda@if.uj.edu.pl)
//  ---------------------------------------------------------------------------
//  Description: some utilities related to string (const char*) manipulation.
//  ---------------------------------------------------------------------------
// ****************************************************************************

#ifndef EDITOR_H
#define EDITOR_H

 unsigned strnextchar(const char* namein, unsigned pos = 0, char x = ' ');
 char* strreplace(char* nameout, const char* namein, char x);
 void strskipwhite(char* nameout, const char* namein, char x);
 char* strtrunc(char* nameout, const char* namein, char x = ' ');

 enum ErrorValues { INFO, WARNING, ERROR };
 void ErrorMsg(ErrorValues status, const char* name, unsigned arg, ...);
   // message printed in case of an warning or error, 
   // just before exception is thrown

#endif /* EDITOR_H */
