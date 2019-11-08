#include "Derivada.hpp"

Derivada::Derivada(){
  left = nullptr;
  right = nullptr;
  signo = "";
}

Derivada::Derivada(string func){
  stringtotree(func);
}

void Derivada::stringtotree(string str){
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

void Derivada::displayTree(){
  Derivada* prueba = this;
  displayTree(prueba);
}
void Derivada::displayTree(Derivada *t) {
  if (t->left != nullptr){
    displayTree(t->left);
    cout << t->signo << endl;
    displayTree(t->right);
  }
}

bool Derivada::in_conectivos (char ch){
  vector<char> conectivos = {'+', '-', '/', '*', '^'};
  for (unsigned int q = 0; q < conectivos.size(); q++){
    if (conectivos[q] == ch)
      return true;
  }
  return false;
}

bool Derivada::in_conectivos2 (string str){
  for (unsigned int q = 0; q < str.size(); q++){
    if (in_conectivos(str[q]))
      return true;
  }
  return false;
}

bool Derivada::conver(string str){
  for (unsigned int q = 0; q < str.size(); q++){
    if (!isalnum(str[q])){
      return false;
    }
  }
  return true;
}

int Derivada::signo(string str){
  int level = 0;
  unsigned int signo = 0;
  int val = 1e6;
  for (unsigned int i = 0; i < str.size(); i++){
    if (str[i] == '['){
      level++;
    }
    else if (str[i] == ']'){
      level--;
    }
    else if (in_conectivos(str[i])){
      if (val > level){
        signo = i;
        val = level;
      }
    }
  }
  return signo;
}

int Derivada::index(string str){
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

string Derivada::reverse(string str){
  if (str.size() <= 1)
    return str;
  else
    return str[str.size()-1] + reverse(str.substr(0, str.size()-1));
}

string Derivada::polaca(string str){
  if ((str.find('[') == string::npos) and (str.find('(') != string::npos)){
    for (unsigned int q = 0; q < str.size(); q++){
      if (str[q] == '(')
        str[q] = '[';
      else if (str[q] == ')')
        str[q] = ']';
    }
  }
  string total;
  int s = signo(str);
  if (conver(str)){
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
      total += "]" + polaca(parte1) +"[" +"]" + polaca(parte2) + "[";}
    }
  return total;
}

string Derivada::polaca_inv(string str){
  string fin;
  string str2 = polaca(str);
  for (unsigned int q = str2.size(); q > 0; q--){
    fin += str2[q-1];
  }
  return fin;
}
