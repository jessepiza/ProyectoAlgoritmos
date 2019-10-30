#include<iostream>
#include<string>
//#include "def_tree.cpp"

using namespace std;

string signo(string str){
    string signo = "";
    if (str.find('[') == string::npos){
      if(str.find('*') != string::npos)
        signo = '*';
      else if (str.find('/') != string::npos)
        signo = '/';
      else if (str.find('^') != string::npos)
        signo = '^';
      else if (str.find('+') != string::npos)
        signo = '+';
      else if (str.find('-') != string::npos)
        signo = '-';
    }

    else{
        for (unsigned int i = 1; i < str.size();i++){
                if (str[i] == ']'){
                    signo = str[i+1];
                    break;
                }else if(str[i] == '['){
                    signo = str[i-1];
                    break;
                }

        }

    }


    return signo;
}


string polaca(string str){
  string s = signo(str);
  cout << s << endl;
  cout << "De 0 a S" << str.substr(0, str.find(s)) << endl;
  cout << "De S al final" << str.substr(str.find(s)+1, str.size()) << endl;
  if (str.size() <= 1){
    return str;
  }
  else{
    string parte1 = str.substr(0, str.find(s));
    string parte2 = str.substr(str.find(s)+1, str.size());
    if ((parte1[0] == '[') and (parte2[0] != '['))
      return s + "[" + polaca(str.substr(1, str.find(s)-2)) + "]" + "[" + polaca(str.substr(str.find(s)+1, str.size())) + "]";
    else if ((parte2[0] == '[') and (parte1[0] != '['))
      return s + "[" + polaca(str.substr(0, str.find(s))) + "]" + "[" + polaca(str.substr(str.find(s)+2, str.size()-4)) + "]";
    else if ((parte2[0] == '[') and (parte1[0] == '['))
      return s + "[" + polaca(str.substr(1, str.find(s)-2)) + "]" + "[" + polaca(str.substr(str.find(s)+2, str.size()-2)) + "]";
    else
      return s + "[" + polaca(str.substr(0, str.find(s))) + "]" + "[" + polaca(str.substr(str.find(s)+1, str.size())) + "]";
  }

}

int main(){
    string str = "[x*2]+[x+2]";
    cout<< polaca(str)<<endl;
    return 0;
}
