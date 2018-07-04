// (heditor.cc)
// ****************************************************************************
//  Module: heditor
//  Version: 1.0
// ****************************************************************************

#include <cstdarg> 
#include <cstring> 
#include <iostream> 
#include "heditor.h"


using namespace std;


// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


//*-- Author : Witold Przygoda (przygoda@if.uj.edu.pl)
//*-- Modified : 2010/05/13 by Witold Przygoda


//----------------------------------------------------------------------------
unsigned strnextchar(const char* namein, unsigned pos, char x) {

// It returns position of next appearance of character x in string namein
// starting counting from position pos.

 if (namein == 0) return 0;
 unsigned i = pos + 1;
 if (x == ' ') {
  while (namein[i] && (namein[i] != ' ' && namein[i] != '\t' && namein[i] != ',')) { ++i; };
 } else {
  while (namein[i] && namein[i] != x) { ++i; };
 }
return (i - pos);
}
//============================================================================


//----------------------------------------------------------------------------
char* strreplace(char* nameout, const char* namein, char x) {

// Internally used by ErrorMsg.
// It copies string namein to nameout replacing all x characters with ' '. 

 int i = -1, j = 0;
 do {
  i++;
  if (namein[i] != x) nameout[j++] = namein[i];
   else nameout[j++] = ' ';
 } while (namein[i]);
return nameout;
}
//============================================================================


//----------------------------------------------------------------------------
void strskipwhite(char* nameout, const char* namein, char x) {

// Internal function used by ErrorMsg. It rewrites namein to nameout
// but after encountering a character of break line 'x' it skips
// all white spaces until the next character non-white occurs.

 int i = 0, j = 0;
 bool skip = false;

 while (namein[i]) {
  if (namein[i] == x) skip = true;
   else if (namein[i] != ' ' && namein[i] != '\t') skip = false;
  if (skip && (namein[i] == ' ' || namein[i] == '\t')) ++i;
   else nameout[j++] = namein[i++];
 }
 nameout[j] = '\0';
}
//============================================================================


//----------------------------------------------------------------------------
char* strtrunc(char* nameout, const char* namein, char x) {

// It copies string namein to nameout but truncating all x characters. If x not specified
// by default all white spaces (spaces and tabulations) will be omitted.

 if (namein == 0) return nameout;
 int i = -1, j = 0;
 do {
  i++;
  if (x == ' ') {
   if (namein[i] != ' ' && namein[i] != '\t') nameout[j++] = namein[i];
  } else {
   if (namein[i] != x) nameout[j++] = namein[i];
  }
 } while (namein[i]);
return nameout;
}
//============================================================================


//----------------------------------------------------------------------------
void ErrorMsg(ErrorValues status, const char* name, unsigned arg, ...) {

// Basic function for printing info / warning / error messages. 
// Text is automatically formatted.
// status: INFO, WARNING, ERROR; 
// name: location of the news (eg class::function name); 
// arg: number of arguments; 
// all arguments _must_ be of const char* type

char buf[4096];
char buffer[4096];
char buffer2[4096];
char buffer3[4096];
int breakline[40];
unsigned filler, underliner, precounter, counter, pos, posenter, stop, i,j,k,l,m;

for (i=0; i<40; i++) breakline[i] = 0;
buf[0] = '\0';
buffer[0] = '\0';
buffer2[0] = '\0';
buffer3[0] = '\0';

va_list ap;
va_start(ap,arg);
for (i = 0; i < arg; i++) {
 strcat(buf, va_arg(ap,char*));
}
va_end(ap);

strtrunc(buffer,buf,'\n');
buf[0] = '\0';
strcpy(buf,buffer);
buffer[0] = '\0';
strtrunc(buffer,buf,'\r');
buf[0] = '\0';
strcpy(buf,buffer);
buffer[0] = '\0';
strskipwhite(buffer,buf,'$');
buf[0] = '\0';
strcpy(buf,buffer);
buffer[0] = '\0';

switch (status) {
 case 0: strcpy(buffer2, " | INFO: ");
         break;
 case 1: strcpy(buffer2, " | WARNING: ");
         break;
 case 2: strcpy(buffer2, " | ERROR: ");
         break;
 default: strcpy(buffer2, " | ");
}
strcat(buffer2,name);
strcat(buffer2," |");

underliner = strlen(buffer2) - 2;
filler = 75 - underliner;
while (underliner > 0) {
 strcat(buffer,"-");
 underliner--;
}
strcat(buffer,"-'");
while (filler > 0) {
 strcat(buffer2," ");
 strcat(buffer," ");
 filler--;
}
strcat(buffer2," |");
strcat(buffer," |");
buffer[0] = ' ';
buffer[1] = '|';

i = 0;
j = strlen(buf);
precounter = counter = 0;
while (counter < j) {
 pos = strnextchar(buf, counter);
 posenter = strnextchar(buf, counter, '$');
 if (posenter < pos) pos = posenter;
 if (pos < 74) {
  if (counter + pos <= precounter + 74) {
   counter += pos;
   if (counter == j || posenter==pos) breakline[i++] = precounter = counter;
  } else {
   breakline[i] = precounter = counter;
   counter += pos;
   i++;
  }
 } else {
  breakline[i] = precounter = counter;
  counter += pos;
  i++;
 }
}

strreplace(buffer3,buf,'$');
buf[0] = '\0';
strcpy(buf,buffer3);
buffer3[0] = '\0';

i = k = 0;
cout << "\n .----------------------------------------------------------------------------.\n";
cout << buffer2 << endl;
cout << buffer << endl;
do {
 stop = (i == 0) ? 0 : breakline[i-1];
 for (j = 0; j < breakline[i]-stop; j++) {
  buffer[j] = buf[k];
  k++;
 }
 buffer[j] = '\0';
 l = m = 0;
 while (buffer[l] == ' ' || buffer[l] == '\t') l++;
 while ((buffer2[m++] = buffer[l++]));
 buffer[0] = '\0';
 strcat(buffer, " | ");
 strcat(buffer, buffer2);

 filler = 77 - strlen(buffer);
 while (filler > 0) {
  strcat(buffer," ");
  filler--;
 }
 strcat(buffer," |");

 cout << buffer << endl;
 i++;
} while (breakline[i] != 0);
cout << " `----------------------------------------------------------------------------'\n\n";
}
//============================================================================


