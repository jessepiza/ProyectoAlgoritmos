#include "Derivada.hpp"
#include <string>

Tree::Tree(){
  left = nullptr;
  right = nullptr;
  signo = "";
}

Tree::Tree(string func){
  if (!is_polaca_inv(func)){
    stringtotree(polaca_inv(func));
  }
  else{
    stringtotree(func);
  }
}

bool Tree::in_operadores_str(string str){
  // Retorna True si en el string ingresado se encuentra algún operador
  // De lo contrario retorna False
  // Parámetros:
  // str - String
  for (unsigned int q = 0; q < str.size(); q++){
    if (in_operadores_char(str[q]))
      return true;
  }
  return false;
}

bool Tree::conver_num(string str){
  // Retorna True si el string ingresado se puede o no convertir a un número.
  // De lo contrario retorna False.
  // Parámetros:
  // str - String
  for (unsigned int q = 0; q < str.size(); q++){
    if (!isalnum(str[q])){
      return false;
    }
  }
  return true;
}

int Tree::operador (string str){
  // Recorre el string ingresado, busca los operadores.
  // Y retorna la posición donde se encuentra el operador.
  // Parámetros:
  // str - String
  int level = 0;
  unsigned int idx_operador = 0;
  int val = 1e6;
  for (unsigned int i = 0; i < str.size(); i++){
    if (str[i] == '['){
      level++;
    }
    else if (str[i] == ']'){
      level--;
    }
    else if (in_operadores_char(str[i])){
      if (val > level){
        idx_operador = i;
        val = level;
      }
    }
  }
  return idx_operador;
}

int Tree::index_balanced(string str){
  // Retorna el índice en str donde están balanceados los paréntesis.
  // Parámetros:
  // str - String
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

string Tree::reverse(string str){
  // Retorna el string str invertido.
  // Parámetros:
  // str - String
  if (str.size() <= 1)
    return str;
  else
    return str[str.size()-1] + reverse(str.substr(0, str.size()-1));
}

string Tree::polaca(string str){
  if ((str.find('[') == string::npos) and (str.find('(') != string::npos)){
    for (unsigned int q = 0; q < str.size(); q++){
      if (str[q] == '(')
        str[q] = '[';
      else if (str[q] == ')')
        str[q] = ']';
    }
  }
  string total;
  int s = operador(str);
  if (conver_num(str)){
    return reverse(str);
  }
  if (str.size() <= 1){
    return str;
  }
  else{
    total += str[s];
    string parte1 = str.substr(0, s);
    string parte2 = str.substr(s+1, str.size());
    if ((parte1[0] == '[') and (parte2[0] != '[')){
      total += "]" + polaca(str.substr(1, s-2)) + "[" + "]" + polaca(str.substr(s+1, parte2.size())) + "[";}
    else if ((parte2[0] == '[') and (parte1[0] != '[')){
        if (str.find(']') != string::npos)
            str.erase(str.find(']'));
      total += "]" + polaca(str.substr(0, s)) + "[" + "]" + polaca(str.substr(s+2, parte2.size()-2)) + "[";}
    else if ((parte2[0] == '[') and (parte1[0] == '[')){
      total += "]" + polaca(str.substr(1, s-2)) + "[" + "]" + polaca(str.substr(s+2, parte2.size()-2)) + "[";}
    else {
      if (str.find('[') != string::npos)
        str.erase(str.find('['));
      if (str.find(']') != string::npos)
        str.erase(str.find(']'));
      total += "]" + polaca(parte1) +"[" +"]" + polaca(parte2) + "[";
    }
  }
  return total;
}

string Tree::polaca_inv(string str){
  string fin;
  string str2 = polaca(str);
  for (unsigned int q = str2.size(); q > 0; q--){
    fin += str2[q-1];
  }
  return fin;
}

void Tree::stringtotree(string str){
  if (!in_operadores_str(str)){
    this -> signo = str;
    this -> right = nullptr;
    this -> left = nullptr;
  }
  else{
    this -> signo = str[str.size()-1];
    int idx = index_balanced(str);
    this -> right = new Tree(str.substr(1, idx-1));
    this -> left = new Tree(str.substr(idx+2, str.size()-idx-4));
  }
}

void Tree::displayTree(){
  Tree* prueba = this;
  displayTree(prueba);
}

void Tree::displayTree(Tree *t){
  if (t->left == nullptr){
    cout << t->signo << endl;
  }
  else{
    displayTree(t->left);
    cout << t->signo << endl;
    displayTree(t->right);
  }
}

bool Tree::in_operadores_char(char ch){
  vector<char> operadores = {'+', '-', '/', '*', '^'};
  for (unsigned int q = 0; q < operadores.size(); q++){
    if (operadores[q] == ch)
      return true;
  }
  return false;
}

bool Tree::is_polaca_inv(string str){
  return in_operadores_char(str[str.size()-1]);
}
