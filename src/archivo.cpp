#include "bibliotecas.h"

void LeerDB(string NomDatabse,vector<user> &DB){


  ifstream file;
  file.open(NomDatabse.c_str());
  string  palabra;
  user aux;
  int i=0;
  while(!file.eof()){
    file >> palabra;
    //cout << palabra;
    if(palabra.compare("INSERT")==0){
      cout << palabra;
      file >> palabra;
      if(palabra.compare("INTO")==0)
      {
        cout << "lo leyo";
        aux.name = palabra;
        DB.push_back(aux);
        cout<<DB[i].name<<endl;
        i++;
        getline(file,palabra);
        cout << palabra<<endl;
        getline(file,palabra);
        cout << palabra<<endl;
      }
    }
  }




}