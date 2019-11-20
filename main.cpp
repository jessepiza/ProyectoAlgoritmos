#include "Derivada.hpp"

int main(){
  Tree prueba("[x+5]*[[x+5]^23]");
  prueba.displayTree();
  cout << endl;
  Tree b = prueba.Derivacion();
  b.displayTree();
  cout << endl;
  string hola = b.treetostring();
  cout << hola << endl;
  return 0;
}
