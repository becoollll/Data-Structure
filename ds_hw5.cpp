#include <string>
#include <stack>
#include <queue>
#include <map>
#include <iostream>
using namespace std;
enum TOKEN {RIGHT_PAREN, OR, AND, NOT, LEFT_PAREN};

class Node {
public:
	Node(char token) {
		this->token = token;
		left = right = parent = NULL;
		result = -1;
	}
	char token; // the one-char symbol representing either an operator or an operand
	Node* left; // pointer to the left child
	Node* right; // pointer to the right child
	Node* parent; // pointer to the parent node
	bool result; // the evaluated Boolean result for this node/subtree
};

class BTree
{
public:
	Node* root; // pointer to the root node
	BTree(string expr); // constructing a tree from a specified expression (in the string format)
	bool evaluate(Node* p); // evaluate the node/subtree rooted by the specified node
	void setVar(char var, bool val); // instantiate a variable with the specified Boolean value
	void show(); // output the constructed tree
	map<char, Node*> table; // you can use the map class provided by the C++ STL to maintain a table for looking up the the instantiations of all variables.
};

string tree(Node **root, string str){
    if(str[0] == '&' || str[0] == '|'){//如果是 & or | 代表有 left child, right child
        *root = new Node(str[0]);
        str.erase(0,1);
        str = tree(&((*root)->left),str);//operate the left child
        str = tree(&((*root)->right),str);//operate the right chikd
    }
    else if(str[0] == '~'){//如果是 ~ 代表只有 left child
        *root = new Node(str[0]);
        str.erase(0,1);
        str = tree(&((*root)->left),str);//只計算left child
    }
    else{
       *root = new Node(str[0]);//not & | ~
        str.erase(0,1);
    }
    return str;

}



BTree::BTree(string expr)
{
    int l = expr.length();
    string out = "";//for prefix;
    string output = "";//reverse for prefix
    int count2 = 0;
    for(int i = 0;; i++){//infix before first (
        if (expr[i] == '('){
            out = expr[i-1] + out;//把運算元放到第一個
            for (int j = 0; j < i-1; j++){
                out = expr[j] + out;
            }
            count2 = i;//'('的位置
            break;
        }
    }
    int temp = count2;
    for (int i = count2; i < l; i++){ // after the first (
        if (expr[i] == ')' && expr[i + 1] != ')'){ // if is not continue two )
            if (expr[i+1] == 'a' || expr[i+1] == 'b' || expr[i+1] == 'c' || expr[i+1] == 'd' || expr[i+1] == '~' || expr[i+1] == '|' || expr[i+1] == '&'){
                out = expr[i+1] + out;
            }
            for (int j = temp; j < i; j++){
                if (expr[j] == ')' || expr[j] == '('){} //結束這個括號
                else{
                    if (expr[j] == 'a' || expr[j] == 'b' || expr[j] == 'c' || expr[j] == 'd' || expr[j] == '~' || expr[j] == '|' || expr[j] == '&'){
                        out = expr[j] + out;
                    }
                }
                temp = i + 2;
            }
        }
    }
    for(unsigned int i = 0; i < out.length(); i++){//因為從一開始就按順序放入，所以要反轉
            output = out[i] + output;
    }
    //cout << output<< endl;
    tree(&root,output);//prefix 放進tree


}

void findthenode(Node* root, char var, bool val){
    if (root->token == var){//find the node
        root ->result = val;//set the value
    }
    if (root->left != NULL){
        findthenode(root->left, var, val);
    }
    if (root->right != NULL){
        findthenode(root->right, var, val);
    }

}

void printt(Node *root,int in){
    for (int i = 0; i < in; i++){//print tab
        cout << "\t";
    }
    cout << root->token << endl;//the print the token out
    if (root->left != NULL){//left child
        printt(root->left, in+1);
    }
    if (root->right != NULL){//right child
        printt(root->right, in+1);
    }
}
void BTree::setVar(char var, bool val){
    findthenode(root, var, val);

}

void BTree::show(){
    printt(root, 0);
}

bool BTree::evaluate(Node *p){
    if (p->token == '~'){//負, 值會在left child
        p->result = !evaluate(p->left);
    }
    if (p->token=='&'){// left child AND right child
        p->result = ((evaluate(p->left))&&(evaluate(p->right)));
    }
    if (p->token=='|'){
        p->result = ((evaluate(p->left))||(evaluate(p->right)));//left child OR right child
    }
    return p->result;

}


int main(){

    BTree etree = BTree("~a&((~b)|(~c))");
    etree.setVar('a', false);
    etree.setVar('b', false);
    etree.setVar('c', false);
    etree.evaluate(etree.root);
    etree.show();
    cout << "The evaluated result = " << etree.root->result << endl;



}
