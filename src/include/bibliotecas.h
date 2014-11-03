#ifndef __Laboratorio3__
#define __Laboratorio3__

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
#include <pthread.h>
#include <vector>



using namespace std;

typedef struct structurauser
{
  string name;
  string pass;
}user;

struct Tupla {
   string encryptMD5;
   string decryptMD5;
   int frequency;
};




int LeerDB(string NomDatabse,vector<user> &DB);
void *Buscar(void * hola);





#endif /* defined(__Laboratorio3__) */