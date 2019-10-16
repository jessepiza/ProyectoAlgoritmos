#include<iostream>
#include<string>
//#include "def_tree.cpp"

using namespace std;

string signo(string str){
    string signo = "";
    if (str.find('[') == string::npos){
        if (str.find('+') == string::npos && str.find('-') == string::npos){
                signo = '^';
        }
        else {
            if(str.find('-')== string::npos)
                signo = str[str.find('+')];
            else    
                signo = str[str.find('-')];    
        }
    }
    
    else{
        for (unsigned int i = 1; i < str.size();i++){
                if (str[i] == ']'){
                    signo = str[i+1];
                    cout<<signo<<endl;
                    break;
                }else if(str[i] == '['){
                    signo = str[i-1];
                    cout<<signo<<endl;
                    break;
                    
                }

        }

    }
    

    return signo;
}

int main(){
    string str = "x^2";
    
    cout<<str.substr(str.find('^')+1, str.size()-1)<<endl;
    return 0;
}
