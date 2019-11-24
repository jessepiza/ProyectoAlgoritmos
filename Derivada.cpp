#include "Derivada.hpp"


/*
  Class Tree.
*/

Tree::Tree(){
  // Constructor.
  left = nullptr;
  right = nullptr;
  signo = "";
}

Tree::Tree(string func){
  // Constructor copia.
  // Convierte la función ingresada en un árbol.
  for (unsigned int i = 0; i < func.size(); i++){
    if (func[i] == '(' || func[i] == '{'){
      func[i] = '[';
    }
    else if (func[i] == ')' || func[i] == '}'){
      func[i] = ']';
    }
  }
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
  // Retorna True si el string ingresado se puede o no convertir a un número o es una sola letra.
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

bool Tree::conver_num2(string str){
  // Retorna True si el string ingresado se puede convertir a un número.
  // De lo contrario retorna False.
  // Parámetos:
  // str - String.
  try{
    stoi(str);
    return true;
  }
  catch (invalid_argument& ia){
    return false;
  }
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
    else if (in_funciones_char(str[i])){
      if (val > level){
        idx_operador = i;
        val = level;
      }
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

bool Tree::in_funciones_char(char ch){
  vector<char> operadores = {'s', 'c', 't', 'a', 'l'};
  for (unsigned int q = 0; q < operadores.size(); q++){
    if (operadores[q] == ch)
      return true;
  }
  return false;
}
bool Tree::in_funciones_str(string str){
  // Retorna True si el str ingresado es una función.
  // De lo contrario retorna False.
  // Parámetos:
  // str - string.
  vector<string> funciones = {"sin", "sen", "cos", "tan", "cot", "csc","sec", "arc", "ln"};
  for (unsigned int q = 0; q < funciones.size(); q++){
    if (funciones[q] == str)
      return true;
  }
  return false;
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
    if (count1 == count2 && count1 != 0)
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
  // Retorna un string con el parámetro ingresado en polaca.
  // Parámetros:
  // str - String.
  // Parámetros
  string total;
  int s = operador(str);
  if (in_funciones_char(str[s])){
    return reverse(str);
  }
  if (str.size() <= 1){
    return str;
  }
  if (conver_num(str)){
    return reverse(str);
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
  // Retorna un string con el parámetro ingresado en polaca inversa.
  // Parámetros:
  // str - String.
  string fin;
  string str2 = polaca(str);
  for (unsigned int q = str2.size(); q > 0; q--){
    fin += str2[q-1];
  }
  return fin;
}

void Tree::stringtotree(string str){
  // Convierte el string ingresado en un árbol.
  // Parámetros:
  // str - String: Tiene que estar en polaca inversa para poder hacer la conversión.
  if (!in_operadores_str(str)){
    this -> signo = str;
    this -> right = nullptr;
    this -> left = nullptr;
  }
  else if (in_funciones_str(str.substr(0,3))){
    this -> signo = str;
    this -> right = nullptr;
    this -> left = nullptr;
  }
  else if (in_funciones_str(str.substr(0,2))){
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
  // Utiliza displayTree(Tree *t) para imprimir el árbol sin parámetos.
  Tree* prueba = this;
  displayTree(prueba);
}

void Tree::displayTree(Tree *t){
  // Imprime el arbol.
  // Parámetros:
  // t - Tree.
  if (t->left == nullptr){
    cout << t->signo;
  }
  else{
    displayTree(t->left);
    cout << t->signo;
    displayTree(t->right);
  }
}

Tree *Tree::copyT(Tree *t){
  Tree* nuevo = nullptr;
  if (t){
    nuevo = new Tree();
    nuevo->signo = t->signo;
    nuevo->left = copyT(t->left);
    nuevo->right = copyT(t->right);
  }
  return nuevo;
}

bool Tree::in_operadores_char(char ch){
  // Retorna True si el char ingresdo es un operador.
  // De lo contrario retorna False.
  // Parámetos:
  // ch - char.
  vector<char> operadores = {'+', '-', '/', '*', '^'};
  for (unsigned int q = 0; q < operadores.size(); q++){
    if (operadores[q] == ch)
      return true;
  }
  return false;
}

bool Tree::is_polaca_inv(string str){
  // Retorna True si el string ingresado está en polaca inversa.
  // De lo contrario retorna False.
  // Parámetos:
  // str - String.
  return in_operadores_char(str[str.size()-1]) || in_funciones_char(str[0]);
}

Tree Tree::Derivacion(){
  Tree* prueba = this;
  return Derivacion(prueba);
}

Tree Tree::Derivacion(Tree *t){
  // Retorna un arbol con la expresión ingresada derivada.
  // Parámetos:
  // t - Tree
  Tree* nuev = new Tree();
  if (in_funciones_str(t->signo.substr(0, 2))){
    int idx = index_balanced(t->signo);
    string atributo = t->signo.substr(3, idx-3);
    Tree* aux = new Tree(atributo);
    nuev->signo = "*";
    nuev->right = new Tree(Derivacion(aux));
    nuev->left = new Tree();
    nuev->left->signo = "/";
    nuev->left->left = new Tree();
    nuev->left->left->signo = "1";
    nuev->left->right = copyT(aux);
  }
  else if(in_funciones_str(t->signo.substr(0, 3))){
    string func = t->signo.substr(0,3);
    if (func != "arc"){
      int idx = index_balanced(t->signo);
      string atributo = t->signo.substr(4, idx-4);
      Tree* aux = new Tree(atributo);
      if (func == "sin" || func == "sen"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "cos";
        nuev->left->signo += '[' + atributo + ']';
      }
      else if (func == "cos"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "-sin";
        nuev->left->signo += '[' + atributo + ']';
      }
      else if (func == "tan"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "^";
        nuev->left->right = new Tree();
        nuev->left->right->signo = '2';
        nuev->left->left = new Tree();
        nuev->left->left->signo = "sec";
        nuev->left->left->signo += '[' + atributo + ']';
      }
      else if (func == "cot"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "^";
        nuev->left->right = new Tree();
        nuev->left->right->signo = '2';
        nuev->left->left = new Tree();
        nuev->left->left->signo = "csc";
        nuev->left->left->signo += '[' + atributo + ']';
      }
      else if (func == "sec"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "*";
        nuev->left->right = new Tree();
        nuev->left->right->signo = "sec";
        nuev->left->right->signo += '[' + atributo + ']';
        nuev->left->left = new Tree();
        nuev->left->left->signo = "tan";
        nuev->left->left->signo += '[' + atributo + ']';
      }
      else if (func == "csc"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "*";
        nuev->left->right = new Tree();
        nuev->left->right->signo = "-csc";
        nuev->left->right->signo += '[' + atributo + ']';
        nuev->left->left = new Tree();
        nuev->left->left->signo = "cot";
        nuev->left->left->signo += '[' + atributo + ']';
      }
    }
    else{
      string func2 = t->signo.substr(3,3);
      int idx = index_balanced(t->signo);
      string atributo = t->signo.substr(7, idx-7);
      Tree* aux = new Tree(atributo);
      if (func2 == "sen" || func2 == "sin"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "/";
        nuev->left->left = new Tree();
        nuev->left->left->signo = "1";
        nuev->left->right = new Tree();
        nuev->left->right->signo = '^';
        nuev->left->right->right = new Tree();
        nuev->left->right->right->signo = "1/2";
        nuev->left->right->left = new Tree();
        nuev->left->right->left->signo = "[1-";
        nuev->left->right->left->signo += '[' + atributo + ']'+ "^2]";
      }
      else if (func2 == "cos"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "/";
        nuev->left->left = new Tree();
        nuev->left->left->signo = "-1";
        nuev->left->right = new Tree();
        nuev->left->right->signo = '^';
        nuev->left->right->right = new Tree();
        nuev->left->right->right->signo = "1/2";
        nuev->left->right->left = new Tree();
        nuev->left->right->left->signo = "[1-";
        nuev->left->right->left->signo += '[' + atributo + ']'+ "^2]";
      }
      else if (func2 == "tan"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "/";
        nuev->left->left = new Tree();
        nuev->left->left->signo = "1";
        nuev->left->right = new Tree();
        nuev->left->right->signo = "[1+";
        nuev->left->right->signo += '[' + atributo + ']' + "^2]";
      }
      else if (func2 == "cot"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "/";
        nuev->left->left = new Tree();
        nuev->left->left->signo = "-1";
        nuev->left->right = new Tree();
        nuev->left->right->signo = "[1+";
        nuev->left->right->signo += '[' + atributo + ']' + "^2]";
      }
      else if (func2 == "sec"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "/";
        nuev->left->left = new Tree();
        nuev->left->left->signo = "1";
        nuev->left->right = new Tree();
        nuev->left->right->signo = '*';
        nuev->left->right->left = new Tree();
        nuev->left->right->left->signo = '|' + atributo + '|';
        nuev->left->right->right = new Tree();
        nuev->left->right->right->signo = '^';
        nuev->left->right->right->right = new Tree();
        nuev->left->right->right->right->signo = "1/2";
        nuev->left->right->right->left = new Tree();
        nuev->left->right->right->left->signo = "[[[" + atributo + ']'+ "^2]";
        nuev->left->right->right->left->signo += "-1]";
      }
      else if (func2 == "csc"){
        nuev->signo = "*";
        nuev->right = new Tree(Derivacion(aux));
        nuev->left = new Tree();
        nuev->left->signo = "/";
        nuev->left->left = new Tree();
        nuev->left->left->signo = "-1";
        nuev->left->right = new Tree();
        nuev->left->right->signo = '*';
        nuev->left->right->left = new Tree();
        nuev->left->right->left->signo = '|' + atributo + '|';
        nuev->left->right->right = new Tree();
        nuev->left->right->right->signo = '^';
        nuev->left->right->right->right = new Tree();
        nuev->left->right->right->right->signo = "1/2";
        nuev->left->right->right->left = new Tree();
        nuev->left->right->right->left->signo = "[[[" + atributo + ']'+ "^2]";
        nuev->left->right->right->left->signo += "-1]";
      }
    }
  }
  else if(!in_operadores_str(t->signo)){
    for (unsigned int i = 0; i < t->signo.size();i++){
        if(isdigit((t->signo)[i]))
          nuev->signo = "0";//si es constante la derivada es 0
        else if (isalpha((t->signo)[i]))
          nuev->signo = "1";
    }
  }
  else{
    // Regla de la resta.
    if(t->signo == "-"){
      nuev->signo = "-";
      nuev->left = new Tree(Derivacion(t->left));
      nuev->right = new Tree(Derivacion(t->right));
    }
    // Regla de la suma.
    else if (t->signo == "+"){
      nuev->signo = "+";
      nuev->left = new Tree(Derivacion(t->left));
      nuev->right = new Tree(Derivacion(t->right));
    }
    // Regla de la multiplicación.
    else if(t->signo == "*"){
      nuev->signo = "+";
      nuev->left = copyT(t);
      nuev->left->left = new Tree(Derivacion(t->left));
      nuev->right = copyT(t);
      nuev->right->right = new Tree(Derivacion(t->right));
    }
    // Regla del exponente.
    else if(t->signo == "^"){
      if (conver_num2(t->right->signo)){
        // Caso: El exponente es un número.
        if (!in_operadores_str(t->left->signo)){
          // La variable está sola.
          nuev->signo = "*";
          nuev->right = copyT(t);
          nuev->left = copyT(t->right);
          if (conver_num2(nuev->left->right->signo)){
            int num = stoi(nuev->left->right->signo);
            num -=1;
            string str_num = to_string(num);
            nuev->left->right->signo = str_num;
          }
        }
        else{
          // Regla de la cadena.
          nuev->signo = "*";
          nuev->right = new Tree(Derivacion(t->left));
          nuev->left = new Tree();
          nuev->left->signo = "*";
          nuev->left->right = copyT(t);
          nuev->left->left = copyT(t->right);
          if (conver_num2(nuev->left->right->signo)){
            int num = stoi(nuev->left->right->signo);
            num -=1;
            string str_num = to_string(num);
            nuev->left->right->signo = str_num;
          }
        }
      }
      // Caso: El exponente es una variable.
      else{
        if (t->left->signo == "e"){
          nuev->signo = "*";
          nuev->right = new Tree(Derivacion(t->right));
          nuev->left = new Tree();
          nuev->left->signo = "e^" + treetostring(t->right);
        }
        else{
          nuev->signo = "*";
          nuev->right = new Tree(Derivacion(t->right));
          nuev->left = new Tree();
          nuev->left->signo = "*";
          nuev->left->left = new Tree();
          nuev->left->left->signo = "ln[" + t->left->signo + "]";
          nuev->left->right = copyT(t);
        }
      }
    }
    // Regla de la división
    else if (t->signo == "/"){
      nuev->signo = "/";
      nuev->right = new Tree();
      nuev->right->signo = "^";
      nuev->right->left = copyT(t->right);
      nuev->right->right = new Tree("2");
      nuev->left = new Tree();
      nuev->left->signo = "-";
      nuev->left->left = copyT(t);
      nuev->left->left->signo = "*";
      nuev->left->left->left = new Tree(Derivacion(t->left));
      nuev->left->right = copyT(t);
      nuev->left->right->signo = "*";
      nuev->left->right->right = new Tree(Derivacion(t->right));

    }
  }
  return *nuev;
}

string Tree::treetostring(){
  Tree *prueba = this;
  return treetostring (prueba);
}


string Tree::treetostring(Tree *t){
  Derivada(t);
  string str = "";
  if (t != nullptr){
    if (t->left == nullptr){
      str += t->signo ;
    }
    else{
      str += "[" + treetostring(t->left);
      str +=  t->signo;
      str += treetostring(t->right) + "]";
    }
  }
  return str;
}


Tree & Tree::Derivada (Tree *t){
  if (t->signo == "+"){
    if (t->right->signo == "0" || t->left->signo == "0"){
      if (t->right->signo == "0" && t->left->signo != "0"){
        t->signo = t->left->signo;
        Tree *ant_right = copyT(t->left->right);
        t->left = copyT(t->left->left);
        t->right = ant_right;
        Derivada(t);
      }
      else{
        t->signo = t->right->signo;
        Tree *ant_left = copyT(t->right->left);
        t->right = copyT(t->right->right);
        t->left = ant_left;
        Derivada(t);
      }
    }
  }
  if (t->signo == "*"){
    if ((t->right->signo == "+" || t->right->signo == "-") && (t->right->right->signo == "0" || t->right->left->signo == "0")){
      if (t->right->right->signo == "0" && t->right->left->signo != "0"){
        t->right->signo = t->right->left->signo;
        t->right->left = copyT(t->right->left->left);
        t->right->right = copyT(t->right->right->right);
        Derivada(t->right);
      }
      else{
        t->right->signo = t->right->right->signo;
        t->right->left = copyT(t->right->left->left);
        t->right->right = copyT(t->right->right->right);
        Derivada(t->left);
      }
    }
    else if ((t->right->signo == "+" || t->right->signo == "-") && (t->left->right->signo == "0" || t->left->left->signo == "0")){
      if (t->left->right->signo == "0" && t->left->left->signo != "0"){
        t->left->signo = t->left->left->signo;
        t->left->left = copyT(t->left->left->left);
        t->left->right = copyT(t->left->right->right);
        Derivada(t->left);
      }
      else{
        t->left->signo = t->left->right->signo;
        t->left->left = copyT(t->left->left->left);
        t->left->right = copyT(t->left->right->right);
        Derivada(t->right);
      }
    }
    if (t->right->signo == "1" || t->left->signo == "1"){
      if (t->right->signo == "1" && t->left->signo != "1"){
        t->signo = t->left->signo;
        Tree *ant_right = copyT(t->left->right);
        t->left = copyT(t->left->left);
        t->right = ant_right;
        Derivada(t);
      }
      else{
        t->signo = t->right->signo;
        Tree *ant_left = copyT(t->right->left);
        t->right = copyT(t->right->right);
        t->left = ant_left;
        Derivada(t);
      }
    }
    else if (t->right->signo == "0" || t->left->signo == "0"){
      t->signo = "0";
      if (t->right->signo == "0" && t->left->signo != "0"){
        Tree *ant_left = copyT(t->right->left);
        t->right = copyT(t->right->right);
        t->left = ant_left;
        Derivada(t);
      }
      else{
        Tree *ant_right = copyT(t->left->right);
        t->left = copyT(t->left->left);
        t->right = ant_right;
        Derivada(t);
      }
    }
  }
  return *t;
}
