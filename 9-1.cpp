#include <iostream>
#include <stack>

using namespace std;
class Nurikabe
{
public:
    /*
    n is the size of the Nurikabe, n >= 5, n <= 20
    game is the result from some player
    here is one example
    n: 5
    game = { {'W', 'W', 'W', '1', 'W'},
             {'W', '.', 'W', 'W', 'W'},
             {'W', '2', 'W', '.', '3'},
             {'3', 'W', 'W', '.', 'W'},
             {'.', '.', 'W', 'W', 'W'} };
    W represent wall
    */
    Nurikabe(char game[20][20], int n)
    {
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                my[i][j] = game[i][j];
            }
        }
        c = n;
    }
    /*
    return 1 if result fit the rule.
    return 0 if result not fit the rule.
    */
    int isCorrect()
    {
        int wall_i, wall_j, flag_wall = 1;
        for(int i = 0; i < c; i++){
            for(int j = 0; j < c; j++){
                if(my[i][j] == 'W'){ // wall
                    if(flag_wall == 1){ // 存第一次碰到牆的位置
                            flag_wall = 0;
                            wall_i = i;
                            wall_j = j;
                    }
                    if(i != c-1 && j != c-1 && (my[i][j+1] == 'W' && my[i+1][j] == 'W' && my[i+1][j+1] == 'W')){ // 2*2
                        return 0;
                    }
                }
                else if((my[i][j] == '.') || isNumber(i, j)){ // 島嶼
                    if(visit(i, j) == 0){
                        return 0;
                    }
                }
                /*
                else if(my[i][j] != '*'){ // 有沒走過的
                    return 0;
                }*/
            }
        }
        for(int i = 0; i < c; i++){
            for(int j = 0; j < c; j++){
                temp[i][j] = my[i][j];
            }
        }
        /*
        for(int i = 0; i < c; i++){
            for(int j = 0; j < c; j++){
                cout << my[i][j] << " ";
            }
            cout << endl;
        }*/
        wall(wall_i, wall_j); // 牆變'a'
        if(island_count() == island){
            cout << "island = " << island << endl;
            island_check = 1;
        }
        /*
        for(int i = 0; i < c; i++){
            for(int j = 0; j < c; j++){
                cout << my[i][j] << " ";
            }
            cout << endl;
        }*/
        //cout << "island_check" << island_check << endl;
        if(my_check() == 1 && island_check == 1){
            return 1;
        }
        else{
            return 0;
        }
        //return my_check() && island_check; //確認是不是都走過了
    }

private:
    //請設計你自己的資料結構來儲存遊戲的結果
    // Please design your own data structure to keet the result
    char my[20][20];
    char temp[20][20];
    int c;
    int island = 0;
    int island_check = 0;
    bool isNumber(int i, int j){
        if(my[i][j] >= '1' && my[i][j] <= '9'){
            return 1;
        }
        else{
            return 0;
        }
    }

    bool visit(int i, int j){
        int num, flag = 0, times = 0;
        stack<int> s;
        s.push(5);
        while(i < c && j < c){
            if(isNumber(i, j)){
                flag = 1;
                num = my[i][j] - '0';
                island++;
            }
            my[i][j] = '*';
            if(j > 0  && (my[i][j - 1] == '.' || isNumber(i, j-1))){ // left
                j--;
                s.push(1);
            }
            else if (i > 0 && (my[i-1][j] == '.' || isNumber(i-1, j))){ // top
                i--;
                s.push(2);
            }
            else if (j < c - 1 && (my[i][j+1] == '.' || isNumber(i, j+1))){ // right
                j++;
                s.push(3);
            }
            else if (i < c - 1 && (my[i+1][j] == '.' || isNumber(i+1, j))){ // bottom
                i++;
                s.push(4);
            }
            else{
                if(num == s.size() + times && flag){ // 數量正確
                    return 1;
                }
                else{ //碰到死路 走回去
                    times++;
                    if(s.top() == 1){ // left
                        j++;
                    }
                    else if(s.top() == 2){ // top
                        i++;
                    }
                    else if(s.top() == 3){ // right
                        j--;
                    }
                    else if(s.top() == 4){ // bottom
                        i--;
                    }
                    else if(s.top() == 5){
                        return 0;
                    }
                    s.pop();
                }
            }

        }
    }
    void wall(int i, int j){
        stack<int> s;
        s.push(5);
        while(i < c && j < c){
            my[i][j] = '|';
            if(j > 0 && my[i][j-1] == 'W'){ // left
                j--;
                s.push(1);
            }
            else if(i > 0 && my[i-1][j] == 'W'){ // top
                i--;
                s.push(2);
            }
            else if(j < c-1 && my[i][j+1] == 'W'){ // right
                j++;
                s.push(3);
            }
            else if(i < c-1 && my[i+1][j] == 'W'){ // bottom
                i++;
                s.push(4);
            }
            else{ // 死路
                if(s.top() == 1){ // left
                    j++;
                }
                else if(s.top() == 2){ // top
                    i++;
                }
                else if(s.top() == 3){ // right
                    j--;
                }
                else if(s.top() == 4){ // bottom
                    i--;
                }
                else if(s.top() == 5){
                    return;
                }
                s.pop();
            }
        }
    }
    int island_count(){
        int res = 0;
        //cout << " ccc = " << c << endl;
        for (int i = 0; i < c; i++){
            for (int j = 0; j < c; j++){
                res += dfs(i, j);
                //cout << "res = " << res << "," << i << "," << j<< endl;
            }
        }
        //cout << "res yoyoyo " << res << endl;
        return res;
    }

    int dfs(int i, int j){
        if (i < 0 || i == c || j < 0 || j == c || temp[i][j] == 'W')
            return 0;
        temp[i][j] = 'W';
        dfs(i - 1, j);
        dfs(i + 1, j);
        dfs(i, j - 1);
        dfs(i, j + 1);
        return 1;
    }
    bool my_check(){
        //cout << "c = " << c << endl;
        int count = 0;
        for (int i = 0; i < c; i++){
            for (int j = 0; j < c; j++){
                //cout << "yo"<<my[i][j] << " "; 
                if (my[i][j] == '|' || my[i][j] == '*'){ //|是走過的牆my[i][j] != '2' && 
                    count++;
                }
            }
            //cout << endl;
        }
        if(count == c*c){
            return 1;
        }
        else{
            return 0;
        }
    }
};
int main() {
    int n, j, l, k;
    char game[20][20] = { {'4', '.', '.', '.', 'W'},
                        {'W', '.', 'W', 'W', 'W'},
                        {'W', '.', 'W', '.', '3'},
                        {'W', '3', 'W', '.', 'W'},
                        {'W', 'W', 'W', 'W', 'W'} };
                        
    std::cin>>n;
    for(j = 0;j < n;j ++)
        for(k = 0;k < n;k ++)
        std::cin>>game[j][k];
    Nurikabe *a = new Nurikabe(game, n);
    std::cout<<a->isCorrect();
    return 0;
}
