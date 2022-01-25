#include <iostream>	
#include <vector>	
#include <fstream>

using namespace std;
// 6-8 создание псевдонимов для вектора типов char, int и bool
typedef vector <char>	cvec;		
typedef vector <int>	ivec;
typedef vector <bool>	bvec;

ivec dfs(vector<vector<int>> v, int s, int e, bvec visited)
{
	ivec ex;
	ivec k;
	ivec b;
	//отмечаем вершину, от которой был запущен DFS, как посещенную
	visited.at(s) = true;						
	if (s == e) {		
		//база рекурсии
		b.push_back(e);
		return b;
	}
	//копирование списка смежности вершины под номером s в вектор T
	ivec T(v[s]);		
	//запуск DFS для всех вершин смежных с вершиной s
	for (size_t i = 0; i < T.size(); i++)		
	{
		//проверка посещали ли мы вершину
		if (!visited[T[i]])						
		{
			k = dfs(v, T[i], e, visited);
			if (k != ex) {
				ivec line(k);
				line.push_back(s);
				return line;
			}

		}
	}
	return ex;
}

int bfs(vector<vector<int>> v, int s, int e, bvec visited)
{
	visited.at(s) = true;
	//создание очереди
	ivec queue;										
	int k;
	//помещаем первый элемент в очередь
	queue.push_back(s);	
	//пока размер вектора > 0
	while (queue.size() > 0)						
	{
		//k = первому элементу в очереди
		k = queue.at(0);	
		//k - освобождает место
		queue.erase(queue.begin());					
		ivec T(v.at(k));	
		//T - все вершины смежные с к
		for (size_t i = 0; i < T.size(); i++)
		{
			//если вершина не посещена, то поместить вершину в очередь
			if (visited[T[i]] == false)				
			{
				visited[T[i]] = true;
				queue.push_back(T[i]);
			}
			if (T[i] == e)
				return true;
		}
	}
	return false;
}


int main()
{
	setlocale(LC_ALL, "RUS");
	ifstream fin;
	fin.open("D:/C++/DFS_BFS/input.txt");
	//объявление высоты и ширины
	int w, h, num;						
	ivec k;
	bool flag;
	//инициализация start и finish
	int start = 0, finish = 0;		
	//Ввод размера схемы
	fin >> w >> h;					
	cvec vvod(w * h);
	//список вершин, которых посетила DFS и BFS
	bvec visited(w * h);				
	ivec line;
	//вектор cc,который будет выступать в роли списка вершин смежных с x вершиной
	ivec cc; 
	//вектор векторов
	vector<vector<int>> v;	
	//заполнение булевого вектора значением "false"
	for (size_t i = 0; i < h; i++)  
	{
		for (size_t j = 0; j < w; j++)
		{
			visited[i * w + j] = false;
		}
	}
	for (size_t i = 0; i < h; i++) 
		//84-95 ввод схемы из файла и нахождение его старта и финиша
	{
		for (size_t j = 0; j < w; j++)
		{
			fin >> vvod.at(i * w + j);
			if (vvod.at(i * w + j) == 's')
				start = i * w + j;
			if (vvod.at(i * w + j) == 'f')
				finish = i * w + j;
		}
	}
	for (size_t i = 0; i < h; i++)			
		//116-125 вывод в консоль исходной схемы 
	{
		for (size_t j = 0; j < w; j++)
		{
			cout << vvod.at(i * w + j);
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < h; i++)			   
		//127-166 создание графа и представление его как список смежности 
	{
		for (int j = 0; j < w; j++)
		{
			num = i * w + j;
			cc.clear();//отчистка вектора сс 
			if (vvod.at(i * w + j) != '#')
			{
				//сдвиг влево
				if (j - 1 >= 0)
					if (vvod.at(i * w + (j - 1)) != '#')
						cc.push_back(i * w + (j - 1));
				//сдвиг право
				if (j + 1 < w)
					if (vvod.at(i * w + (j + 1)) != '#')
						cc.push_back(i * w + (j + 1));
				//сдвиг вверх
				if (i - 1 >= 0)
					if (vvod.at((i - 1) * w + j) != '#')
						cc.push_back((i - 1) * w + j);
				//сдвиг вниз
				if (i + 1 < h)
					if (vvod.at((i + 1) * w + j) != '#')
						cc.push_back((i + 1) * w + j);
			}
			//129-137 вывод вершин смежных с вершиной i*w+j
			cout << num << " = [";
			for (size_t i = 0; i < cc.size(); i++)
			{
				if (i != cc.size() - 1)
					cout << cc.at(i) << " ";
				else
					cout << cc.at(i);
			}
			cout << ']' << endl;
			//заполнение матрицы 
			v.push_back(cc); 
			num = 0;
		}
	}
	cout << "__________________________________________________________________________________________________________________" << endl;
	//вызов bfs для start и finish
	flag = bfs(v, start, finish, visited);
	cout << "Можно ли довести груз ";
	//171-175 вывод работы функции
	if (flag == 0)
		cout << "FALSE";
	else {
		cout << "TRUE";
		//вызов dfs для start и finish
		k = dfs(v, start, finish, visited);  
		cout << endl;
		//вывод пути
		for (int i = k.size() - 1; i >= 0; i--) 
		{
			cout << k.at(i) << " ";
		}
		//184-197 вывод пути в графе
		for (size_t i = 1; i < k.size() - 1; i++) 
		{
			vvod.at(k.at(i)) = 'O';
		}
		cout << endl;
		for (size_t i = 0; i < h; i++)
		{
			for (size_t j = 0; j < w; j++)
			{
				cout << vvod.at(i * w + j);
			}
			cout << endl;
		}
	}
	//закрытие файлового потока
	fin.close();
	//201-205 очищение динамической памяти от векторов
	cc.clear();			
	v.clear();
	vvod.clear();
	visited.clear();
}