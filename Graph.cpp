#include "Graph.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <unordered_map>
#include "GraphNode.h"
using namespace std;
void Graph::getData(char*argv[]) {
	vector<vector<size_t>> adjacency_matrix;
	string path = "matrix.txt";
	string full_path = argv[0];
	int index = full_path.find_last_of('\\');
	std::string pathDir = "";
	if (index > -1)
		pathDir = full_path.substr(0, index);
	full_path = pathDir + '\\' + path;
	fstream file;
	file.open(full_path, ios_base::out | ios_base::in);
	processing(&file);
	file.close();
}

void Graph::showData() const{
	for (auto it = _data.begin(); it != _data.end(); ++it) {
		cout << it->first << " : " << endl;
		for (auto iter = it->second->getWays().begin(); iter != it->second->getWays().end(); ++iter) {
			cout << "    " << iter->first << " : " << iter->second << endl;
		}
	}
}

bool Graph::DFS(size_t num) const{
	stack<size_t> stack;
	if (_data.find(num) == _data.end())
		return (false);
	//кладём в стек первую вершину
	stack.push(0);
	vector<size_t> visited(_data.size());
	for (auto el: visited) {
		el = 0;
	}
	size_t current = 0;
	while (!stack.empty() && current != num) {
		current = stack.top();
		if (!visited[current]) {
			visited[current] = 1;
			cout << current << endl;
			for (const auto iter : _data.at(current)->getWays()) {
				stack.push(iter.first);
			}
		}
		else {
			stack.pop();
		}
	}
	if (current == num) {
		return true;
	}
	return false;
}

Graph::Graph(){
	for (auto it = _data.begin(); it != _data.end(); ++it) {
		delete it->second;
	}
}


Graph::~Graph()
{
}

bool Graph::processing(fstream *file) {
	if (!file->is_open()) return false;
	return_in_pos(file, true);//Вернуться к началу файла
	//посчитать количество столбцов в матрице = количеству строк = количеству вершин
	string buf;
	getline(*file, buf);
	size_t num_items = count(buf.begin(), buf.end(), ' ');
	num_items += 1;
	return_in_pos(file, true);

	//читаем матрицу
	for (size_t i = 0; i < num_items; ++i) {
		GraphNode* node = new GraphNode(i);
		_data.insert(std::make_pair(i, node));
	}
	for (size_t i = 0; i < num_items; ++i) {
		for (size_t j = 0; j < num_items; ++j) {
			buf.clear();
			getline(*file, buf, j < num_items - 1 ? ' ' : '\n');
			if (buf == "-" || buf == "0") {
				continue;
			}
			else {
				_data[i]->addNeighbour(j, (size_t)stoll(buf));
			}
		}
	}
	return true;
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
