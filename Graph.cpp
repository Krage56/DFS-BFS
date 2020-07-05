#include "Graph.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <tuple>
#include <algorithm>
#include <string>
#include <unordered_map>
#include "GraphNode.h"
using namespace std;
void Graph::getData(char*argv[]) {
	vector<vector<long long>> adjacency_matrix;
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

bool Graph::processing(fstream *file) {
	if (!file->is_open()) return false;
	return_in_pos(file, true);//Вернуться к началу файла
	//посчитать количество столбцов в матрице = количеству строк = количеству вершин
	string buf;
	getline(*file, buf);
	long long num_items = count(buf.begin(), buf.end(), ' ');
	num_items += 1;
	return_in_pos(file, true);

	//читаем матрицу
	for (long long i = 0; i < num_items; ++i) {
		GraphNode* node = new GraphNode(i);
		_data.insert(std::make_pair(i, node));
	}
	for (long long i = 0; i < num_items; ++i) {
		for (long long j = 0; j < num_items; ++j) {
			buf.clear();
			getline(*file, buf, j < num_items - 1 ? ' ' : '\n');
			if (buf == "-" || buf == "0") {
				continue;
			}
			else {
				_data[i]->addNeighbour(j, stoll(buf));
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
