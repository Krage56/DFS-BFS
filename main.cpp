#include <iostream>
#include <tuple>
#include <vector>
#include <map>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;
class GraphNode{
    std::map<long long, long long> _ways;
public:
    GraphNode(long long num);
    //Порядковы номер вершины и расстояние до неё
    const std::map<long long, long long>& getWays() const;
    long long _number;
    long long getNum()const { return _number; };
    long long getWay(long long node)const;
    void addNeighbour(long long node_num, long long way);
    ~GraphNode();
};
GraphNode::GraphNode(long long num){
    _number = num;
}

const std::map<long long, long long>& GraphNode::getWays() const
{
    return _ways;
}


long long GraphNode::getWay(long long node) const{
    auto way = _ways.find(node);
    if (way != _ways.end()) {
        return way->second;
    }
    else {
        return -1;
    }
}

void GraphNode::addNeighbour(long long node_num, long long way){
    _ways.insert(std::make_pair(node_num, way));
}

GraphNode::~GraphNode()
{
}
class Graph{
    std::map<long long, GraphNode*>_data;
public:
    Graph();
    auto getData();
    void showData()const;
    std::tuple<bool, std::vector<long long>> DFS(long long num, long long origin = 0)const;
    auto BFS(long long num, long long origin = 0)const;
    std::vector<long long> getPath(std::vector<long long>& prior, long long dest, long long origin = 0)const;
    ~Graph();
protected:
    void return_in_pos(std::fstream *file, bool pos)const;
    bool is_empty_file(std::fstream *file)const;
    auto processing(std::fstream *file);
};

auto Graph::processing(fstream *file) {
    if (!file->is_open()) return make_tuple(false, (long long)0, (long long)0);
    return_in_pos(file, true);//Вернуться к началу файла
    //Посчитать кол-во стобцов в матрице = кол-ву строк = кол-ву вершин
    string buf;
    getline(*file, buf);
    long long num_items = stoll(buf);

    //Читаем матрицу
    for (long long i = 0; i < num_items; ++i) {
        GraphNode* node = new GraphNode(i);
        _data.insert(std::make_pair(i, node));
    }
    for (long long i = 0; i < num_items; ++i) {
        for (long long j = 0; j < num_items; ++j) {
            buf.clear();
            getline(*file, buf, j < num_items - 1 ? ' ' : '\n');
            if (buf == "0") {
                continue;
            }
            else {
                _data[i]->addNeighbour(j, stoll(buf));
            }
        }
    }
    long long dest = 0, origin = 0;
    buf.clear();
    getline(*file, buf,' ');
    origin = stoll(buf);
    buf.clear();
    getline(*file, buf,' ');
    dest = stoll(buf);
    return make_tuple(true, origin, dest);
}
auto Graph::getData() {
    vector<vector<long long>> adjacency_matrix;
    string full_path = "./INPUT.TXT";
    fstream file;
    file.open(full_path, ios_base::out | ios_base::in);
    long long origin, dest;
    bool success;
    tie(success, origin, dest) = processing(&file);
    file.close();
    return make_tuple(origin, dest);
}

void Graph::showData() const{
    for (auto it = _data.begin(); it != _data.end(); ++it) {
        cout << it->first << " : " << endl;
        for (auto iter = it->second->getWays().begin(); iter != it->second->getWays().end(); ++iter) {
            cout << "    " << iter->first << " : " << iter->second << endl;
        }
    }
}


Graph::Graph(){
    for (auto it = _data.begin(); it != _data.end(); ++it) {
        delete it->second;
    }
}


std::vector<long long> Graph::getPath(std::vector<long long>& prior, long long dest, long long origin) const
{
    vector<long long> ans;
    for (int v = dest; v != origin; v = prior[v])  // Проходим по пути из конца в начало
    {
        ans.push_back(v);  // Запоминаем вершину
    }
    ans.push_back(origin);
    reverse(ans.begin(), ans.end());  // Переворачиваем путь
    return ans;
}

Graph::~Graph()
{
}


void Graph::return_in_pos(fstream *file, bool pos)const {
    file->clear();
    pos ? file->seekg(0, ios_base::beg) : file->seekg(0, ios_base::end);
}
bool Graph::is_empty_file(fstream *file)const{
    long file_size;
    file->seekg(0, ios::end);
    file_size = file->tellg();
    return (file_size == 0);
}
auto Graph::BFS(long long num, long long origin) const {
    queue<long long> queue;
    if (_data.find(num) == _data.end()) {
        vector<long long> empty;
        return make_tuple(false, empty, empty);
    }
    queue.push(origin);
    vector<bool> visited(_data.size());
    vector<long long>prior(_data.size());
    vector<long long>prices(_data.size());
    for (long long i = 0; i < _data.size(); ++i) {
        prior[i] = -1;
        prices[i] = -1;
    }
    long long current = origin;
    prior[origin] = origin;
    prices[origin] = /*_data.at(origin)->getWay(origin) == -1?0:1*/0;//сразу определяем, сколько от элемента до себя же
    while (!queue.empty() /*&& num != current*/) {
        current = queue.front();
        if (!visited[current]) {
            visited[current] = true;
            for (const auto iter : _data.at(current)->getWays()) {
                queue.push(iter.first);
//                if(prices[current] == 0){
//                    if(!visited[iter.first] || prices[iter.first] > 1){
//                        prices[iter.first] = 1;
//                    }
//                }
//                if(!visited[iter.first] || prices[iter.first] > prices[current] + 1){
//                    prices[iter.first] = prices[current] + 1;
//                }
                if(iter.first != origin && !visited[iter.first]){
                    prices[iter.first] = prices[current] + 1;
                }
                prior[iter.first] = !visited[iter.first] ? current : prior[iter.first];

            }
        }
        else {
            queue.pop();
        }
    }
    return make_tuple(static_cast<bool>(visited[num]), prior, prices);
}

int main(int args, char*argv[]) {
	Graph g;
	long long origin, dest;
	tie(origin, dest) = g.getData();
	bool isExist;
	vector<long long> way, price;
	std::tie(isExist, way, price) = g.BFS(dest-1, origin-1);
	cout << price[dest - 1] << endl;
	return 0;
}