#ifndef _DERIVADA_H_
#define _DERIVADA_H_

#include string;

class Derivada{
public:
  Derivada();
  Derivada(string func);

private:
  struct Tree{
    string der;
    Tree *left, right;
    Tree();
    Tree(string func);
    void stringtotree(string str);
    void displayTree();
    void displayTree(Derivada *t);
    bool in_conectivos (char ch);
    bool in_conectivos2 (string str);
    bool conver(string str);
    int signo(string str);
    int index(string str)
    string reverse(string str);
    string polaca(string str);
    string polaca_inv(string str);
  };
  Tree Der;
};

#endif
