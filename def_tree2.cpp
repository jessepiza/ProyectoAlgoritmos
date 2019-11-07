#include<iostream>
#include <algorithm>
#include<string>
#include<vector>
using namespace std;


bool in_conectivos (char ch){
  vector<char> conectivos = {'+', '-', '/', '*', '^'};
  for (unsigned int q = 0; q < conectivos.size(); q++){
    if (conectivos[q] == ch)
      return true;
  }
  return false;
}

bool in_conectivos2 (string str){
  for (unsigned int q = 0; q < str.size(); q++){
    if (in_conectivos(str[q]))
      return true;
  }
  return false;
}

int index(string str){
  int count1 = 0;
  int count2 = 0;
  for (unsigned int q = 0; q < str.size(); q++){
    if (str[q] == '[')
      count1++;
    else if (str[q] == ']')
      count2++;
    if (count1 == count2)
      return q;
  }
  return -1;
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
      signo = "";        // cout << t->left->signo << endl;
        // cout << t->right->signo << endl;
    }
    void stringtotree(string str){
      if (!in_conectivos2(str)){
        this -> signo = str;
        this -> right = nullptr;
        this -> left = nullptr;
        cout<<str<<endl;
      }
      else{
        this -> signo = str[str.size()-1];
        int idx = index(str);
        this -> right = new Derivada(str.substr(1, idx-1));
        this -> left = new Derivada(str.substr(idx+1, str.size()-3));
      }
    }
    void displayTree(){
  		Derivada* prueba = this;
  		displayTree(prueba);
  	}
    void displayTree(Derivada *t) {
      if (t->left != nullptr){
        displayTree(t->left);
        cout << t->signo << endl;
        displayTree(t->right);
        // cout << t->left->signo << endl;
        // cout << t->right->signo << endl;
      }
    }
};
int main(){
    Derivada prueba("[[[33][x]+][3]*][[2][[[2][x]+][[22][x]^]+]^]+");
    //prueba.displayTree();
    // prueba.stringtotree("23x^+");


    return 0;
}
