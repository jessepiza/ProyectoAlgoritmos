#include<iostream>
#include <algorithm>
#include<string>
#include<vector>
using namespace std;
vector<char> conectivos = {'+', '-', '/', '*', '^', 'b'};
bool found_element (char str){
    vector<char>::iterator it = find(conectivos.begin(), conectivos.end(), str);
    if (it != conectivos.end())
      return true;
    else
      return false;
}
struct Derivada {
    string signo;
    Derivada *left, *right;

    Derivada(string str){
        stringtotree(str);
    }

    Derivada(){
      left = nullptr;
      right = nullptr;
      signo = "";
    }
    Derivada stringtotree(string str){
      vector<Derivada> pila;
      for (unsigned int q = 0; q < str.size(); q++){
        if (found_element(str[q])){
          Derivada t;
          t.signo = str[q];
          cout << t.signo << endl;
          *t.right = pila[pila.size()-2];
          *t.left = pila[pila.size()-2];
          pila.erase(pila.end()-1);
          pila.erase(pila.end()-1);
          pila.push_back(t);

        }
        else{
          Derivada aux;
          aux.signo = str[q];
          aux.right = nullptr;
          aux.left = nullptr;
          cout << aux.signo << endl;
        }
      }
      return pila[pila.size()-1];
    }
    void displayTree(){
      Derivada* prueba = this;
      displayTree(prueba);
    }
    void displayTree(Derivada *t) {
      if(t->left == nullptr)
      cout<<t->signo;
      else{
        displayTree(t->left);
        cout << t->signo;
        displayTree(t->right);
      }
      cout<<'\n';
    }
};
int main(){
    Derivada prueba("23x^+");
    prueba.displayTree();
    // prueba.stringtotree("23x^+");


    return 0;
}
