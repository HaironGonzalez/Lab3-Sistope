#include "bibliotecas.h"
#include "md5.h"

vector<user> DB;
vector<string> Cache;
bool LaEncontre = false;
int indice = 0;
pthread_mutex_t mutexsum;
ofstream Resultado("./Resultado");
 
void * Buscar(void * param)
{
  vector <string> BloqueDic;
  BloqueDic = *(vector<string>*) param;
  int LargoBloque= BloqueDic.size();
  
  cout << " Primero: "<<BloqueDic[0]<<"         ultimo: "<<BloqueDic[LargoBloque-1]<<endl;

  string PalabraDB = DB[indice].pass;
  
  string Criptograma;
  for(int i = 0;i<LargoBloque;i++){
    Criptograma = md5(BloqueDic[i]);
    if(Criptograma.compare(PalabraDB)==0){
      cout << "LA ENCONTRE y es: "<<BloqueDic[i]<<endl;
      Resultado << DB[indice].name <<" "<<BloqueDic[i]<<endl;
      break; 
    }
  }


  pthread_mutex_lock (&mutexsum);
  
  pthread_mutex_unlock (&mutexsum);


  pthread_exit(NULL);
}

int main (int argc, char **argv)
{
  int NumHebras;
  int TamCache;

  string NomDicionario;
  char * NomDatabase = NULL;

  pthread_mutex_init(&mutexsum, NULL);
 
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

    string md5t = "b0ar!$h";
    md5t = md5(md5t);
    cout << "Nom MD5: "<<md5t<<endl;

    int NumUsuarios = LeerDB(NomDatabase,DB);

    //cout << " HAY "<<cont << "usuarios"<<endl;
    //cout<< DB[NumUsuarios-1].name<<"    "<<DB[NumUsuarios-1].pass<<endl;

    // Dividir diccionario

    ifstream file;
    file.open(NomDicionario.c_str());
    vector<string> Diccionario;
    string palabra;
    file >> palabra;
    while(!file.eof()){

      
      Diccionario.push_back(palabra);
      file >> palabra;
      //cout<<palabra<<endl;
    }

    int NumPalabras = Diccionario.size();
    int NumPartes = Diccionario.size()/NumHebras;
    int Resto = Diccionario.size()%NumHebras;

    cout<< "NumPalabras = "<< NumPalabras << "\n NumPartes = "<<NumPartes<<"\n Resto = "<<Resto<<endl;

    //cout<<Diccionario[Diccionario.size()-1]<<endl;
    //for (int k=0;k<NumPalabras;k++)cout << Diccionario[k]<<"  ";
    
    vector <vector<string> > BloquePalabras;    // tiene un vector de palabras del diccionario por cada hebra a crear

    for (int i = 0;i<NumHebras;i++){
      vector <string> aux;
      for(int j = 0 ; j < NumPartes;j++){
        aux.push_back(Diccionario[(NumPartes * i)+j]);
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
      pthread_create(&tid[i], &attr, Buscar, (void *)&BloquePalabras[i]);
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


  pthread_mutex_destroy(&mutexsum);
  return 0;
}

