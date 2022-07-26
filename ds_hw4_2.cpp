/*#include <iostream>
#include <queue>
using namespace std;
class Client {
public:
    int id; // personal identifier
    unsigned int start; // the time to make the order
    unsigned int enter; // the time to enter the shop
    unsigned int dur; // the needed service time
    unsigned int leave;
};

int main(){
     // clock
    int n, m;
    cin >> n >> m;
    queue<Client> q[m]; //櫃台
    queue<int> t;
    queue<int> table;
    int input_id[n], input_enter[n], input_dur[n];
    for(int i = 0; i < n; i++){
        cin >> input_id[i] >> input_enter[i] >> input_dur[i];
    }
    unsigned int time = 0;
    int c = 0;
    int k = 0;
    while(1){
        if(c == n){
            break;
        }
        //cout << endl;
        int flagg = 0;
        for(int i = 0; i < n; i++){ // 進門
            if(input_enter[i] == (int)time){
                Client temp; //建構一個客人物件
                temp.id = input_id[i];
                temp.enter = input_enter[i];
                temp.dur = input_dur[i];
                if(flagg == 0){
                    if(k == 0){
                        cout << "Time " << time << ": ";
                        k = 1;
                        flagg = 1;
                    }
                    else {
                        cout << endl << "Time " << time << ": ";
                        flagg = 1;
                    }
                }
                cout << "C" << temp.id << ">>>(D:" << temp.dur << ")|";
                int min_j = 0;
                queue<Client> min = q[0];
                for(int j = 1; j < m; j++){ //找最短櫃臺隊列
                    if(min.size() > q[j].size()){ 
                        min = q[j];
                        min_j = j;
                    }
                }
                int wait_time;
                if(q[min_j].size() == 0){
                    wait_time = 0;
                }
                else{
                    wait_time = q[min_j].front().start;
                }
                temp.start = time + wait_time;
                q[min_j].push(temp); //加入排隊
                if(flagg == 0){
                    cout << endl << "Time " << time << ": ";
                    flagg = 1;
                }
                cout << "C" << temp.id << "-->Q" << min_j+1 << "|";
            }
        }
        for(int i = 0; i < m; i++){ // 找有沒有要點餐的
            if(q[i].front().start == time && q[i].front().id != 0){
                if(flagg == 0){
                    cout << endl << "Time " << time << ": ";
                    flagg = 1;
                }
                cout << "C" << q[i].front().id << "@Q" << i+1 << " (ETL:" << time+q[i].front().dur << ")|"; // 
                q[i].front().leave = time+q[i].front().dur;
            }
        }
        for(int i = 0; i < m; i++){
            if(q[i].front().leave == time && q[i].front().id != 0){
                if(flagg == 0){
                    cout << endl << "Time " << time << ": ";
                    flagg = 1;
                }
                cout << "C" << q[i].front().id << "<--Q" << i+1 << "|";
                q[i].pop();
                c++;
                if(q[i].size() != 0 && q[i].front().id != 0){
                    cout << "C" << q[i].front().id << "@Q" << i+1 << " (ETL:" << time+q[i].front().dur << ")|"; // 
                    q[i].front().leave = time+q[i].front().dur;
                }
            }
        }
        //cout << endl;
        time++;
        
    }
}
*/
#include <iostream>
#include <queue>
using namespace std;
class Client {
public:
    int id; // personal identifier
    unsigned int start; // the time to make the order
    unsigned int enter; // the time to enter the shop
    unsigned int dur; // the needed service time
    unsigned int leave;
};

int main(){
     // clock
    int n, m;
    cin >> n >> m;
    queue<Client> q[m]; //櫃台
    queue<int> t;
    vector<int> num;
    int input_id[n], input_enter[n], input_dur[n];
    for(int i = 0; i < n; i++){
        cin >> input_id[i] >> input_enter[i] >> input_dur[i];
    }
    unsigned int time = 0;
    int c = 0;
    int k = 0;
    while(1){
        if(c == n){
            break;
        }
        //cout << endl;
        int flagg = 0;
        for(int i = 0; i < n; i++){ // 進門
            if(input_enter[i] == (int)time){
                Client temp; //建構一個客人物件
                temp.id = input_id[i];
                temp.enter = input_enter[i];
                temp.dur = input_dur[i];
                if(flagg == 0){
                    if(k == 0){
                        cout << "Time " << time << ": ";
                        k = 1;
                        flagg = 1;
                    }
                    else {
                        cout << endl << "Time " << time << ": ";
                        flagg = 1;
                    }
                }
                cout << "C" << temp.id << ">>>(D:" << temp.dur << ")|";
                int min_j = 0;
                queue<Client> min = q[0];
                for(int j = 1; j < m; j++){ //找最短櫃臺隊列
                    if(min.size() > q[j].size()){ 
                        min = q[j];
                        min_j = j;
                    }
                }
                int wait_time;
                if(q[min_j].size() == 0){
                    wait_time = 0;
                }
                else{
                    wait_time = q[min_j].front().start;
                }
                temp.start = time + wait_time;
                q[min_j].push(temp); //加入排隊
                if(flagg == 0){
                    cout << endl << "Time " << time << ": ";
                    flagg = 1;
                }
                cout << "C" << temp.id << "-->Q" << min_j+1 << "|";
            }
        }
        for(int i = 0; i < m; i++){ // 找有沒有要點餐的
            if(q[i].front().start == time && q[i].front().id != 0){
                int yo = 0;
                for(int ii = 0; ii < (int)num.size(); ii++){
                    if(num[ii] == q[i].front().id){
                        yo = 1;
                    }
                }
                if(flagg == 0 && yo == 0){
                    cout << endl << "Time " << time << ": ";
                    flagg = 1;
                }
                if(yo == 0){
                    cout << "C" << q[i].front().id << "@Q" << i+1 << " (ETL:" << time+q[i].front().dur << ")|"; // 
                    q[i].front().leave = time+q[i].front().dur;
                }
            }
        }
        for(int i = 0; i < m; i++){
            if(q[i].front().leave == time && q[i].front().id != 0){
                if(flagg == 0){
                    cout << endl << "Time " << time << ": ";
                    flagg = 1;
                }
                cout << "C" << q[i].front().id << "<--Q" << i+1 << "|";
                q[i].pop();
                c++;
                if(q[i].size() != 0 && q[i].front().id != 0){
                    cout << "C" << q[i].front().id << "@Q" << i+1 << " (ETL:" << time+q[i].front().dur << ")|"; // 
                    q[i].front().leave = time+q[i].front().dur;
                    num.push_back(q[i].front().id);
                }
            }
        }
        //cout << endl;
        time++;
        
    }
}
