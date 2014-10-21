#include "bibliotecas.h"
#include "md5.h"

vector<user> DB;
bool LaEncontre = false;

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

    //string md5t = "!$0$c3l3$";
    //md5t = md5(md5t);
    //cout << "Nom MD5: "<<md5t<<endl;

    int NumUsuarios = LeerDB(NomDatabase,DB);

    //cout << " HAY "<<cont << "usuarios"<<endl;
    //cout<< DB[NumUsuarios-1].name<<"    "<<DB[NumUsuarios-1].pass<<endl;

    // Dividir diccionario

    ifstream file;
    file.open(NomDicionario.c_str());
    vector<string> Diccionario;
    string palabra;
    while(!file.eof()){

      file >> palabra;
      Diccionario.push_back(palabra);
      //cout<<palabra<<endl;
    }

    int NumPalabras = Diccionario.size();
    int NumPartes = Diccionario.size()/NumHebras;
    int Resto = Diccionario.size()%NumHebras;

    cout<<Diccionario[Diccionario.size()-1]<<endl;
    
    vector <vector<string> > BloquePalabras;    // tiene un vector de palabras del diccionario por cada hebra a crear

    for (int i = 0;i<NumHebras;i++){
      vector <string> aux;
      for(int j = 0 ; j < NumPartes;j++){
        aux.push_back(Diccionario[(i+1)*j]);
      }
      BloquePalabras.push_back(aux);
      aux.clear();
    }

      
    if (Resto != 0){
      for (int i = 0; i<Resto;i++){
        BloquePalabras[i].push_back(Diccionario[NumHebras*NumPartes+i]);
      }
    }
    
    pthread_t tid[NumHebras];
    pthread_attr_t attr; 
    int status;

    pthread_attr_init(&attr);

    for (int i = 0;i<NumHebras;i++)
    {
      pthread_create(&tid[i], &attr, Buscar, NULL);
    }
    for (int i = 0;i<NumHebras;i++)
    {
      pthread_join(tid[i], (void **)&status);
    }
  }
  else
  {
    cout << "Error Banderas"<< endl;
  }
  return 0;
}


void *Buscar()
{
  cout << "Hola"<<endl;
}