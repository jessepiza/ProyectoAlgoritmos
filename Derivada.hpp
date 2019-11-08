#ifndef _Derivada_hpp_
#define _Derivada_hpp_

#include <iostream>
#include <string>
#include <vector>

class Tree{
public:
  Tree();
  Tree(string func);

  bool in_operadores_str (string str);
  bool conver_num(string str);
  int operador(string str);
  int index_balanced(string str);
  string reverse(string str);
  string polaca(string str);
  string polaca_inv(string str);
  void stringtotree(string str);
  void displayTree();
private:
  string signo; // Operador o variable libre de la función
  Tree *left, *right; // Operandos que separa el operador

  void displayTree(Tree *t);
  bool in_operadores_char (char ch);

};

// class Derivada{
// public:
//   Derivada();
//   Derivada(string func);
//
// private:
//   struct Tree{
//   };
//   Tree Der;
// };

#endif
