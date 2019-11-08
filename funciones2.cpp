
#include<iostream>
#include<string>
#include<vector>
//#include "def_tree.cpp"

using namespace std;

bool in_operadores_char (char ch){
  vector<char> operadores = {'+', '-', '/', '*', '^'};
  for (unsigned int q = 0; q < operadores.size(); q++){
    if (operadores[q] == ch)
      return true;
  }
  return false;
}

bool in_operadores_str (string str){
  for (unsigned int q = 0; q < str.size(); q++){
    if (in_operadores_char(str[q]))
      return true;
  }
  return false;
}

int operador(string str){
  int level = 0;
  unsigned int operador = 0;
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
        operador = i;
        val = level;
      }
    }
  }
  return operador;
}

bool conver_num(string str){
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

int main(){
    string str = "[[x+3]^2]+8";
    cout<< polaca_inv(str) <<endl;
    return 0;
}
