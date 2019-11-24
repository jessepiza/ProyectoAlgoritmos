#include "Derivada.hpp"
#include <iostream>
#include <fstream>

int main(){
  string cadena;
  ifstream fe("Funcion.txt");
  fe>>cadena;
  Tree funcion(cadena);
  Tree funcion_der = funcion.Derivacion();
  string der_str = funcion_der.treetostring();
  der_str.erase(der_str.begin());
  der_str.pop_back();
  fe.close();

  ofstream file;
  file.open("Derivada.txt");
  file << der_str;
  file.close();
  return 0;
}
