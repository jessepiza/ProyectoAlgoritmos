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

bool conver(string str){
  for (unsigned int q = 0; q < str.size(); q++){
    if (!isalnum(str[q])){
      return false;
    }
  }
  return true;
}

string reverse(string str){
  if (str.size() <= 1)
    return str;
  else
    return str[str.size()-1] + reverse(str.substr(0, str.size()-1));
}
int signo(string str){
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

string polaca(string str){
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

string polaca_inv(string str){
  string fin;
  string str2 = polaca(str);
  for (unsigned int q = str2.size(); q > 0; q--){
    fin += str2[q-1];
  }
  return fin;
}


class Derivada{
public:
  string signo;
  Derivada *left, *right;

  Derivada(){
    left = nullptr;
    right = nullptr;
    signo = "";

  }
  Derivada(string str){
      stringtotree(str);
  }
  void stringtotree(string str){
    if (!in_conectivos2(str)){
      this -> signo = str;
      this -> right = nullptr;
      this -> left = nullptr;
    }
    else{
      this -> signo = str[str.size()-1];
      int idx = index(str);
      this -> right = new Derivada(str.substr(1, idx-1));
      this -> left = new Derivada(str.substr(idx+2, str.size()-idx-4));
    }
  }
  void displayTree(){
      Derivada* prueba = this;
      displayTree(prueba);
  }
  void displayTree(Derivada *t) {
    if (t->left == nullptr){
      cout << t->signo << endl;
    }
    else{
      displayTree(t->left);
      cout << t->signo << endl;
      displayTree(t->right);
    }
  }

};

struct Tree {
    string signo;
    Tree *left, *right;

    Tree(string str){
        stringtotree(str);
    }

    Tree(){
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
      }
      else{
        this -> signo = str[str.size()-1];
        int idx = index(str);
        this -> right = new Tree(str.substr(1, idx-1));
        this -> left = new Tree(str.substr(idx+2, str.size()-idx-4));
      }
    }
    void displayTree(){
  		Tree* prueba = this;
  		displayTree(prueba);
  	}
    void displayTree(Tree *t) {
      if (t->left == nullptr){
        cout << t->signo << endl;
      }
      else{
        displayTree(t->left);
        cout << t->signo << endl;
        displayTree(t->right);
      }
    }

    Derivada regla(){
      Derivada* nuev = new Derivada();

      if(!in_conectivos2(this->signo)){
          for (unsigned int i = 0; i<this->signo.size();i++){
              if(isdigit((this->signo)[i]))
                nuev->signo = "0";//si es constante la derivada es 0
              else if (isalpha((this->signo)[i]))
                nuev->signo = "1";
          }
          
      }else{
          if ((this->signo == "+")||(this->signo == "-")){//regla de suma o resta
              nuev->left = new Derivada((this->left)->regla());
              nuev->right = new Derivada((this->right)->regla());
              if(this->signo == "+")
                nuev->signo = "+";
              else if(this->signo == "-")
                nuev->signo = "-";
           }else if(this->signo == "*"){//regla multiplicacion
             nuev->signo = "+";
             nuev->left = copyT(this);
             nuev->left->left = new Derivada((this->left)->regla());
             nuev->right = copyT(this);
             nuev->right->right = new Derivada((this->right)->regla());
           }else if(this->signo == "^"){
             nuev->signo = "^";
             nuev->left = copyT(this);
             nuev->left->signo = "*";
             nuev->left->left = new Derivada((this->left)->regla());
             
             nuev->right->signo = this->right->signo+"-1";           
           }
      }
      return *nuev;
    }
  Derivada* copyT(Tree *der){
    Derivada* nuevo = nullptr;
    if (der){
      nuevo = new Derivada();
      nuevo->signo = der->signo;
      nuevo->left = copyT(der->left);
      nuevo->right = copyT(der->right);
    }
    return nuevo;
  }

};

int main(){
  string func =  "[x+4]^3";
  string pol = polaca_inv(func);
  Tree der(pol);
  cout<<"inicial: ";
  der.displayTree();
  Derivada sol = der.regla();
  cout<<"deriv: ";
  sol.displayTree();


  return 0;
}
