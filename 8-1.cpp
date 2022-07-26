#include <iostream>
#include <cstdlib>
#include <stack>
#include <queue>
#include <ctime>

using namespace std;

class Node{
public:
	int level, data;
	Node *left, *right;
};

class Tree{
public:
	Tree(){
		root = NULL;
	}
	int insert(Node *n){
		insert(&root, n);
	}
	//盡量往左子節點前進，而途中經過的父節點先存在一個stack裡面
	//等到沒有更多左子節點時，就把stack中的父節點取出並拜訪每個父子節點的右子節點
	void inorder(){ //左中右
		cout << endl << "inorder" << endl;
		stack<Node *> s;
		Node *cur = root;
		if (cur != NULL || !s.empty()){ // tree exist
			while (cur != NULL || !s.empty()){
				if (cur != NULL){ // 非空
					s.push(cur);//存進stack
					cur = cur->left; // left
				}
				else{
					cur = s.top(); // middle
					s.pop(); // remove top
					cout << cur->data << " ";
					cur = cur->right; // right
				}
			}
		}
	}
	//拜訪父節點再拜訪子節點。利用stack，將stack頂端的值取出後，把左右子節點放進stack，直到stack為空。
	void preorder(){ //中左右
		cout << endl << "preorder" << endl;
		stack<Node *> s;
		s.push(root);
		while (s.size() > 0){
			Node *node = s.top(); // middle, 取出stack頂端的值
			s.pop();
			cout << node->data << " ";
			if (node->right != NULL){ // 如果右邊有資料 放進stack
				s.push(node->right);//right
			}
			if (node->left){ // 如果左邊有資料 放進stack
				s.push(node->left);//left
			}
		}
	}
	void postorder(){ // 左右中 用遞迴
        cout << endl << "postorder" << endl;
        postorder_rec(root);
	}

	//level由小到大的順序，由上而下，並在同一個level由左至右
	void levelorder(){
		cout << endl << "levelorder" << endl;
    	queue<Node*> q; // queue先進先出

    	q.push(root); // root推進queue
    	while (!q.empty()){             // 若queue不是空的, 表示還有node沒有visiting
        	Node *cur = q.front();      // 取出先進入queue的node
        	q.pop();                          
        	cout << cur->data << " ";   // visiting
			
        	if (cur->left != NULL){    // 若left有資料, 將其推進queue
            	q.push(cur->left);
        	}
        	if (cur->right != NULL){   // 若right有資料, 將其推進queue
            	q.push(cur->right);
        	}
    	}

	}

private:
	Node *root;
    void postorder_rec(Node* root){
        //base case
        if (root == NULL)
            return;

        // fisrt traverse left sub tree
        postorder_rec(root->left);

        //secondly traverse right sub tree
        postorder_rec(root->right);

        //finally traverse current node
        cout << root->data << " ";
    
    }
	void insert(struct Node **r, struct Node *n){
		if (*r == NULL)
			*r = n;
		else if (n->data > (*r)->data){
			insert(&((*r)->right), n);
		}
		else{
			insert(&((*r)->left), n);
		}
	}
};

int main(){
	Tree *tree = new Tree();
	Node *node;
	int j;
	srand(time(NULL));
	for (j = 0; j < 10; j++){
		node = new Node();
		node->data = rand();
		node->left = NULL;
		node->right = NULL;
		tree->insert(node);
		cout << node->data << endl;
	}
	tree->inorder();
	printf("\n");
	tree->preorder();
	printf("\n");
	tree->postorder();
	printf("\n");
	tree->levelorder();
	printf("\n");
}