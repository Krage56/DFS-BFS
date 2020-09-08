#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <string>
#include <tuple>
using namespace std;

void return_in_pos(ifstream *file, bool pos){
    file->clear();
    pos ? file->seekg(0, ios_base::beg) : file->seekg(0, ios_base::end);
}
auto processing(ifstream *file) {
    return_in_pos(file, true);//Вернуться к началу файла
    //Посчитать кол-во стобцов в матрице = кол-ву строк = кол-ву вершин
    string buf;
    getline(*file, buf);
    long long num_items = stoll(buf);

    //Читаем матрицу
    vector<vector<long long>>adjacency_matrix(num_items);//матрица смежности - не мудрствуя лукаво
    for (long long i = 0; i < num_items; ++i) {
        for(long long j = 0; j < num_items; ++j)
            adjacency_matrix[i].push_back(0);
    }
    for (long long i = 0; i < num_items; ++i) {
        for (long long j = 0; j < num_items; ++j) {
            buf.clear();
            getline(*file, buf, j < num_items - 1 ? ' ' : '\n');
            adjacency_matrix[i][j] = stoll(buf);
        }
    }
    long long dest = 0, origin = 0;
    buf.clear();
    getline(*file, buf,' ');
    origin = stoll(buf);
    buf.clear();
    getline(*file, buf,' ');
    dest = stoll(buf);
    return make_tuple(origin, dest, adjacency_matrix);
}


auto BFS(vector<vector<long long>>_data, long long origin, long long dest){
    queue<long long> queue;
    queue.push(origin);
    vector<long long>prices(_data.size(), -1);
    long long current;
    prices[origin] = 0;//сразу определяем, сколько от элемента до себя же
    while(!queue.empty()){
        current = queue.front();
        queue.pop();
        for(int i = 0; i < _data.size(); ++i){
            if(_data[current][i] == 1){
                if(prices[i] == -1 && i != current) {
                    prices[i] = prices[current] + 1;
                    queue.push(i);
                }
            }
        }
    }
    return prices;
}

int main(int args, char*argv[]) {

	long long origin, dest;
    vector<vector<long long>>adjacency_matrix;
    ifstream file;
    file.open("./INPUT.TXT", ios_base::in);
    tie(origin, dest, adjacency_matrix) = processing(&file);
    vector<long long>prices = std::move(BFS(adjacency_matrix, origin-1, dest-1));
    cout << prices[dest - 1] << endl;
    file.close();
	return 0;
}