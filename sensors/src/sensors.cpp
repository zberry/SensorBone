//============================================================================
// Name        : sensors.cpp
// Author      : Zachary Berry
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include <cstring>

int main() {
        setenv("LANG","C",1);
        FILE * fp = popen("/sbin/ifconfig", "r");
        if (fp) {
                char *p=NULL, *e; size_t n;
                while ((getline(&p, &n, fp) > 0) && p) {
                   if (p = strstr(p, "inet ")) {
                        p+=5;
                        if (p = strchr(p, ':')) {
                            ++p;
                            if (e = strchr(p, ' ')) {
                                 *e='\0';
                                 printf("%s\n", p);
                            }
                        }
                   }
              }
        }
        pclose(fp);
        return 0;
}
