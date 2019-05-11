#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // all ASCII values
    char randChar = rand() % 127 + 1;
    return randChar;
}

char *inputString()
{
    char r = 'r';
    char e = 'e';
    char s = 's';
    char t = 't';
    int stringLength = 5;
    char *inputS = malloc(sizeof(char) * (stringLength + 1));
    memset(inputS, '\0', stringLength);
    for(int i = 0; i < stringLength; i++) {
      //25 since a is 0 in this scenario
      int charAscii = rand() % 4 + 1;
      if(charAscii == 1) {
        inputS[i] = r;
      }
      else if(charAscii == 2) {
        inputS[i] = e;
      }
      else if(charAscii == 3) {
        inputS[i] = s;
      }
      else if(charAscii == 4) {
        inputS[i] = t;
      }
    }
    return inputS;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
