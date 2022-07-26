#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;

const int Num = 26; //每個節點需要儲存26個字母

class Node{
public:
    bool isWord; //判斷是否是字
    Node *next[Num];
    Node(){
        isWord = false;
        for(int i = 0; i < Num; i++){
            next[i] = 0;
        }
    }
};

class Trie{
public:
    Trie(){ 
        root = new Node(); 
    }
    void insert(string word){
        Node *location = root;
        for (int i = 0; i < word.length(); i++){
            if (location->next[word[i] - 'a'] == NULL){ // 第一個字母
                Node *temp = new Node();
                location->next[word[i] - 'a'] = temp;
                //next[0] = a, next[1] = b...
            }
            location = location->next[word[i] - 'a'];
        }
        location->isWord = true; //這個字的最後一個字母
    }
    bool search(string word){
        Node *location = root;
        for (int i = 0; i < word.length() && location; i++){ // visit
            location = location->next[word[i] - 'a'];
        }
        return (location != NULL && location->isWord);
    }

private:
    Node *root;
};

int main(){
    Trie tree;
    int n, m;
    cin >> n >> m;
    while(n--){
        string s;
        cin >> s;
        tree.insert(s);
    }
    while(m--){
        string input;
        cin >> input;
        cout << tree.search(input) << endl;
    }

}
