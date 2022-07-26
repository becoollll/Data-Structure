#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

class Graph {

    private:

        int nodes;
        list<int> *adjlist;
        vector<bool> visited;

    public:

        Graph() {
        }

        Graph (int nodes) { // Allocate resources 
            adjlist = new list<int> [nodes];
            visited.resize(nodes, false);
            this->nodes = nodes;
        }

        void AddEdge (int src, int dst) {
            adjlist[src].push_back(dst);
            adjlist[dst].push_back(src);
        }

        // DFS recursive
        void DFS(int node)
        {
            visited[node] = true;
            cout << node << " ";

            for (list<int>::iterator it = adjlist[node].begin(); it != adjlist[node].end(); it++) {
                //for(int n : adjlist[node])
            {
                    if(!visited[*it])
                        DFS(*it);
                }
            }
        }
};



int main()
{
    int c;
    cin >> c;

    Graph g(c);
    int temp[c][2]; 
    vector<int> t;
    for(int i = 0; i < c; i++){
        int a, b;
        cin >> a >> b;
        temp[i][1] = a;
        temp[i][2] = b;
        t.push_back(a);
        t.push_back(b);
        g.AddEdge(a,b);
    }
    int start;
    cin >> start;
    g.DFS(start);
    cout << endl;

    vector<int> tt;
    sort(t.begin(), t.end());
    if(t[0] != t[1]){
        t.push_back(t[0]);
    }
    for(int i = 1; i < (int)t.size(); i++){
        if(i != (int)t.size()-1){
            if(t[i] != t[i+1] && t[i] != t[i-1]){
                tt.push_back(t[i]);
            }
        }
        else{
            if(t[i] != t[i-1]){
                tt.push_back(t[i]);
            }
        }
    }

    vector<int> ap;
    for(int i = 0; i < (int)tt.size(); i++){
        for(int j = 0; j < c; j++){
            if(tt[i] == temp[j][1]){
                ap.push_back(temp[j][2]);
            }
            if(tt[i] == temp[j][2]){
                ap.push_back(temp[j][1]);
            }

        }
    }
    sort(ap.begin(), ap.end());
    for(int i = 1; i < (int)ap.size(); i++){
        if(ap[i] == ap[i-1]){
            ap.erase(ap.begin()+i);
        }
    }
    cout << "AP: ";
    for(int i = 0; i < (int)ap.size(); i++){
        cout << ap[i] << " ";
    }
    
    return 0;
}