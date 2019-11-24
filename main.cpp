#include "Derivada.hpp"
#include <iostream>
#include <fstream>

int main(){
  string cadena;
  ifstream fe("/Users/alesa/ProyectoAlgoritmos/Funcion.txt");
  fe>>cadena;
  // cout>>cadena;
  Tree prueba(cadena);
  prueba.displayTree();
  cout << endl;
  Tree b = prueba.Derivacion();
  b.displayTree();
  cout << endl;
  string hola = b.treetostring();
  cout << hola << endl;
  fe.close();

  ofstream file;
  file.open("/Users/alesa/ProyectoAlgoritmos/Derivada.txt");
  file << hola;
  file.close();
  system("pause");
  // while (!fe.eof()) {
  //   fe >> cadena;
  //   cout << cadena << endl;
  // }
  return 0;
}
