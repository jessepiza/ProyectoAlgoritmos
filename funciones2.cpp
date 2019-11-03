
#include<iostream>
#include<string>
//#include "def_tree.cpp"

using namespace std;

int signo(string str){
  int signo = 0;
  if (str.find('[') == string::npos){
    if(str.find('*') != string::npos)
      signo = str.find('*');
    else if (str.find('/') != string::npos)
      signo = str.find('/');
    else if (str.find('^') != string::npos)
      signo = str.find('^');
    else if (str.find('+') != string::npos)
      signo = str.find('+');
    else if (str.find('-') != string::npos)
      signo = str.find('-');
  }

  else{
    for (unsigned int i = 1; i < str.size();i++){
      if (str[i] == ']'){
        signo = i+1;
        break;
      }else if(str[i] == '['){
        signo = i-1;
        break;
      }
    }
  }
  return signo;
}

bool conver(string str){
  for (unsigned int q = 0; q < str.size(); q++){
    if (!isalnum(str[q])){
      return false;
    }
  }
  return true;
}

string polaca(string str){
  string total;
  int s = signo(str);
  if (conver(str)){
    return str;
  }
  if (str.size() <= 1){
    return str;
  }
  else{
    total += str[s];
    string parte1 = str.substr(0, s);
    string parte2 = str.substr(s+1, str.size());
    if ((parte1[0] == '[') and (parte2[0] != '[')){
      total += "[" + polaca(str.substr(1, s-2)) + "]" + "[" + polaca(str.substr(s+1, parte2.size())) + "]";}
    else if ((parte2[0] == '[') and (parte1[0] != '[')){
      total += "[" + polaca(str.substr(0, s)) + "]" + "[" + polaca(str.substr(s+2, parte2.size()-2)) + "]";}
    else if ((parte2[0] == '[') and (parte1[0] == '[')){
      total += "[" + polaca(str.substr(1, s-2)) + "]" + "[" + polaca(str.substr(s+2, parte2.size()-2)) + "]";}
    else {
      total += "[" + polaca(parte1) +"]" +"[" + polaca(parte2) + "]";}
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
    string str = "[x+225]+22*x";
    cout<< polaca(str)<<endl;
    return 0;
}
