#include<iostream>
#include<string>
using namespace std;

struct Derivada
{
    string signo;
    Derivada *left, *right;

    Derivada() {
        left = nullptr;
        right = nullptr;
        signo = "";
    }
    Derivada(string str){
        stringtotree(str);
    }
    void stringtotree(string str){
        if (str.size() == 1){
            left = nullptr;
            right = nullptr;
            signo = str;
            
        }else{
            if (str.find('[') == string::npos){
                if (str.find('+') == string::npos && str.find('-') == string::npos){
                        signo = '^';
                        left = new Derivada();
                        left->signo = str.substr(0, str.find('^'));
                        right = new Derivada();
                        right->signo = str.substr(str.find('^')+1, str.size()-1);
                        stringtotree(left->signo);
                        stringtotree(right->signo);
                }
                else {
                    if(str.find('-')== string::npos)
                        {signo = str[str.find('+')];
                        left = new Derivada();
                        left->signo = str.substr(0, str.find('+'));
                        right = new Derivada();
                        right->signo = str.substr(str.find('+')+1, str.size()-1);
                        stringtotree(left->signo);
                        stringtotree(right->signo);}

                    else    
                        {signo = str[str.find('-')]; 
                        left = new Derivada();
                        left->signo = str.substr(0, str.find('-'));
                        right = new Derivada();
                        right->signo = str.substr(str.find('-')+1, str.size()-1);
                        stringtotree(left->signo);
                        stringtotree(right->signo);}   
                }
            }
            else{
                for (unsigned int i = 1; i < str.size();i++){
                    if (str[i] == ']'){
                        signo = str[i+1];
                        //left = new Derivada(str.substr(0, i));
                        //right = new Derivada(str.substr(i+2, str.size()-1));
                        cout << "Entré" << endl;
                        left = new Derivada();
                        left->signo = str.substr(0, i);
                        right = new Derivada();
                        right->signo = str.substr(i+2, str.size()-1);
                        stringtotree(left->signo);
                        stringtotree(right->signo);
                        break;
                    }else if(str[i] == '['){
                        signo = str[i-1];
                        left = new Derivada();
                        left->signo = str.substr(0, i-2);
                        right = new Derivada();
                        right->signo = str.substr(i, str.size()-1);
                        stringtotree(left->signo);
                        stringtotree(right->signo);
                    }
                }

            }
        }
        
    }
    void displayTree(){
        Derivada* prueba = this;
        displayTree(prueba);
    }
    void displayTree(Derivada *t) {
        if(t->left == nullptr)
            cout<<t->signo;
        else{
            displayTree(t->left);
            cout << t->signo;
            displayTree(t->right);
        }
        cout<<'\n';
    }

};

int main(){
    Derivada prueba("x^3+2");
    prueba.displayTree();


    return 0;
}
