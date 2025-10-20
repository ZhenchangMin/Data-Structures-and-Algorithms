#include <iostream>
#include <queue>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<string> operations;// 先把n个指令读入数组，再一一执行，直到达到上限k
    int temp = n;
    while(temp--){
        string op;
        cin >> op;
        if (op[0] == 'e'){
            string input;
            cin >> input;
            operations.push_back("echo " + input);
        }
        else{
            int index;
            cin >> index;
            operations.push_back("cp " + to_string(index)); // 字符串和int不能直接拼接
        }
    }
    int size = n;
    for(int i = 0; i < size; i++){
        if (operations[i][0] == 'e')
        {
            cout << operations[i].substr(5);
        }
        else if(size < k)
        {
            int index;
            index = stoi(operations[i].substr(3));//用子串来获得后面的int值
            for (int j = 0; j < index; j++)
            {
                if(size < k){
                    operations[size] = operations[j];
                    size++;
                }
            }
        }
    }
    return 0;
}