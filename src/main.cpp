#include "bibliotecas.h"
#include "md5.h"



int main (int argc, char **argv)
{
  int NumHebras;
  int TamCache;

  string NomDicionario;
  char * NomDatabase = NULL;
 
  bool rflag = false;
  bool dflag = false;
  bool cflag = false;
  bool hflag = false;
  char *aux = NULL;
  int c;
  int cont =0;
  opterr = 0;

  while ((c = getopt (argc, argv, "h:c:d:r:")) != -1)
  {
    switch (c)
    {
      case 'h':
        hflag = true;
        aux = optarg;
        cont++;
        NumHebras = atoi(aux);
        break;
      case 'd':
        dflag = true;
        cont++;
        NomDicionario = optarg;
        break;
      case 'r':
        rflag = true;
        cont++;
        NomDatabase = optarg;
        break;
      case 'c':
        cflag = true;
        aux = optarg;
        cont++;
        TamCache = atoi(aux);
        break;
      case '?':
        if (optopt == 'c') cout << "Error de parámetros\n";
        else if (isprint (optopt)) cout << "Error banderas\n";
        else cout << "Error banderas\n";
        return 1;
      default:
        abort ();
    } 
  }




if (rflag && cflag  && dflag  && hflag && cont == 4)
{
  cout << "diccionario es: "<<NomDicionario<<endl;
  cout << "Numero Hebras es: "<<NumHebras<<endl;
  cout << "Nombre DB es: "<<NomDatabase<<endl;
  cout << "Tamaño Cache es: "<<TamCache<<endl;

  string md5t = "!$0$c3l3$";
  md5t = md5(md5t);
  cout << "Nom MD5: "<<md5t<<endl;

  vector<user> DB;

  LeerDB(NomDatabase,DB);



}
else
{
cout << "Error Banderas"<< endl;
}


return 0;
}