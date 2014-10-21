#include "bibliotecas.h"
#include "md5.h"

int LeerDB(string NomDatabse,vector<user> &DB){


  ifstream file;
  file.open(NomDatabse.c_str());
  string  palabra;
  user aux;
  int i=0,cont = 0;
  while(!file.eof()){
    file >> palabra;
    //cout << palabra;
    if(palabra.compare("INSERT")==0){
      //cout << palabra;
      file >> palabra;
      if(palabra.compare("INTO")==0)
      {
        //cout << "lo leyo";
        //aux.name = palabra;
        //DB.push_back(aux);
        //cout<<DB[i].name<<endl;
        //i++;
        getline(file,palabra);
        //cout << palabra<<endl;

        char c;
        string name;
        string pass;
        c = file.get();
        while(c != ';'){
          c = file.get();      
          if(c == '\''){
            
            for (int j = 0;j<3;j++){  // separa name y pass de una linea
            
              while (c != '\''){
                c = file.get();
              }

              if (c == '\'' && j == 0){
                c = file.get();
                while (c != '\''){
                
                  name.push_back(c);
                  c = file.get();
                }
              }
              else if (c == '\'' && j == 1){
                c = file.get();
                while (c != '\''){
                  c = file.get();
                }
              }
              else if (c == '\'' && j == 2){
                c = file.get();
                while (c != '\''){
                  pass.push_back(c);
                  c = file.get();
                }
              }
              
              c = file.get();
                
              
            }
            //cout<< name<< "     "<<pass<<endl;
            aux.name = name;

            aux.pass = pass;
            pass.clear();
            name.clear();
            DB.push_back(aux);
            cont++;
          } 
        }  
      }
    }
  }
  //cout << " HAY "<<cont << "usuarios"<<endl;
  //cout<< DB[cont-1].name<<"    "<<DB[cont-1].pass<<endl;
return cont;
}


