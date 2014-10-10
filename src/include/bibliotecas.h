
#ifndef __Laboratorio2__
#define __Laboratorio2__

#include <iostream>
#include <sstream>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include <time.h>
#include <vector>



using namespace std;

typedef struct structurauser
{
  string name;
  string pass;
}user;


void LeerDB(string NomDatabse,vector<user> &DB);



#endif /* defined(__Laboratorio2__) */