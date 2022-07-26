#include <iostream>
#include <cstdlib>
#include <stack>
#include <queue>
#include <ctime>

using namespace std;

class Tree
{
public:
	Tree()
	{
		int j, k;
		for(j = 0;j < 20;j ++)
			for(k = 0;k < 4;k ++)
				root[j][k] = -1;
	}
	int insert(int node)
	{
		int f = 0, index = 0;
		while(root[index][0] != -1)
			index ++;
		if(index >= 20)
			return -1;
		if(index == 0)
		{
			root[0][0] = 1;
			root[0][1] = node;
			return 1;
		}
		else
		{
			root[index][0] = 1;
			root[index][1] = node;
			while(1)
			{
				if(root[f][1] < node)
				{
					if(root[f][3] == -1)
					{
						root[f][3] = index;
						return 1;
					}
					else
					{
						f = root[f][3];
					}
				}
				else
				{
					if(root[f][2] == -1)
					{
						root[f][2] = index;
						return 1;
					}
					else
					{
						f = root[f][2];
					}
				}
			}
		}
	}
	void inorder()//左中右
	{
        cout << "inorder" << endl;
        if(root[0][0] == 1){
            inorder_rec(root[0]);
        }
	}
	void preorder()//中左右
	{
        cout << endl << "preorder" << endl;
        int *temp;
        stack<int *> *s = new stack<int *>;
        if(root[0][0] == 1){
            s->push(root[0]);
        }
        while(!s->empty()){
            temp = s->top(); //取出中間的值
            s->pop();
            if(temp[3] != -1){//right
                s->push(root[temp[3]]);
            }
            cout << temp[1] << " ";
            if(temp[2] != -1){//left
                s->push(root[temp[2]]);
            }
        }
	}
	void postorder()//左右中
	{
        cout << endl << "postorder" << endl;
        if(root[0][0] != -1){
            postorder_rec(root[0]);
        }
	}
	void levelorder()
	{
        cout << endl << "levelorder" << endl;
        if(root[0][0] != 1){
            return;
        }
        int *temp;
        queue<int *> *s = new queue<int *>;
        s->push(root[0]);
        while(!s->empty()){
            temp = s->front();
            s->pop();
            if(temp[2] != -1){//left
                s->push(root[temp[2]]);
            }
            cout << temp[1] << " ";
            if(temp[3] != -1){
                s->push(root[temp[3]]);
            }
        }
	}
private:
	int root[20][4];
    void inorder_rec(int *node){
        if(node[2] != -1){
            inorder_rec(root[node[2]]);
        }
        cout << node[1] << " ";
        if(node[3] != -1){
            inorder_rec(root[node[3]]);
        }
    }
    void postorder_rec(int *node){
        //cout << endl << "node:" << "0_" <<  node[0] << "1_" << node[1] << "2_" << node[2] << "3_" << node[3] << endl;
        if(node[2] != -1){
            postorder_rec(root[node[2]]);
        }
        if(node[3] != -1){
            postorder_rec(root[node[3]]);
        }
        cout << node[1] << " ";
    }
};

int main()
{
	Tree *tree = new Tree();
	int j, node;
	srand(time(NULL));
	for(j = 0;j < 10;j ++)
	{
		node = rand();
		tree->insert(node);
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
