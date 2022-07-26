#include<iostream>
#include<cstdlib>
#include<stack>
#include<queue>
#include<ctime>

using namespace std;

class Tree{
public:
	Tree(){
		int j;
		for(j = 0;j < 2000;j ++)
			root[j] = -1;
	}
	int insert(int node){
		int index = 0;
		while(index < 2000 && root[index] != -1){
			if(root[index] < node)
				index = index * 2 + 2;//right
			else
				index = index * 2 + 1;//left
		}
		root[index] = node;
	}
    void print(){
        for(int i = 0; i < 50; i++){
            if(root[i] != -1){
                cout << endl;
            }
            cout << root[i] << " ";
        }
    }
	void inorder(){
        cout << endl << "inorder" << endl;
        if(root[0] != -1){
            inorder_rec(0);
        }
	}
	void preorder(){
        cout << endl << "preorder" << endl;
        if(root[0] != -1){
            preorder_rec(0);
        }
	}
	void postorder(){
        cout << endl << "postorder" << endl;
        if(root[0] != -1){
            postorder_rec(0);
        }
	}
	void levelorder(){
        cout << endl << "levelorder" << endl;
        for(int i = 0; i < 2000; i++){
            if(root[i] != -1){
                cout << root[i] << " ";
            }
        }
	}
private:
	int root[2000];
    void inorder_rec(int i){
        if(root[i*2+1] != -1){
            inorder_rec(i*2+1);
        }
        cout << root[i] << " ";
        if(root[i*2+2] != -1){
            inorder_rec(i*2+2);
        }
    }
    void preorder_rec(int i){
        cout << root[i] << " ";
        if(root[i*2+1] != -1){
            preorder_rec(i*2+1);
        }
        if(root[i*2+2] != -1){
            preorder_rec(i*2+2);
        }
    }
    void postorder_rec(int i){
        if(root[i*2+1] != -1){
            postorder_rec(i*2+1);
        }
        if(root[i*2+2] != -1){
            postorder_rec(i*2+2);
        }
        cout << root[i] << " ";
    }
};

int main(){
	Tree *tree = new Tree();
	int j, node;
	srand(time(NULL));
	for(j = 0;j < 10;j ++){
		node = rand();
		tree->insert(node);
	}
    tree->print();
	tree->inorder();
	printf("\n");
	tree->preorder();
	printf("\n");
	tree->postorder();
	printf("\n");
	tree->levelorder();
	printf("\n");
}
