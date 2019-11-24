#ifndef _Derivada_hpp_
#define _Derivada_hpp_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Tree{
public:
  Tree();
  Tree(string func);

  bool in_operadores_str (string str);
  bool in_funciones_str(string str);
  bool conver_num(string str);
  int operador(string str);
  int index_balanced(string str);
  string reverse(string str);
  string polaca(string str);
  string polaca_inv(string str);
  void stringtotree(string str);
  void displayTree();
  Tree *copyT(Tree *t);
  Tree Derivacion();
  string treetostring();
private:
  string signo; // Operador o variable libre de la función
  Tree *left, *right; // Operandos que separa el operador

  Tree Derivacion(Tree *t);
  void displayTree(Tree *t);
  bool in_operadores_char (char ch);
  bool in_funciones_char (char ch);
  bool is_polaca_inv(string str);
  bool conver_num2(string str);
  string treetostring(Tree *t);
  Tree & Derivada (Tree *t);
};

#endif
