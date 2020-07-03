#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define Vertices 20

int pathMatrix[Vertices][Vertices];

//алгоритм Флойда-Уоршелла
void Floyd(int Distance [][Vertices], int Path [][Vertices])
{
	for (int k = 0; k < Vertices; k++)
	{
		for (int i = 0; i < Vertices; i++)
		{
			for (int j = 0; j < Vertices; j++)
			{
				if ((Distance[i][k] && Distance[k][j] && i != j) && ((Distance[i][k] + Distance[k][j] < Distance[i][j] || Distance[i][j] == 0)))
				{
					Distance[i][j] = Distance[i][k] + Distance[k][j];
					Path[i][j] = k + 1;
				}					
			}				
		}			
	}	
}

// Вывод пути
void printPath(int i, int j)
{
	int k = pathMatrix[i][j];
	if (k == 0)
		return;
	printPath(i, k - 1);
	cout << k << " ";
	printPath(k, j);
}

int main()
{
	ifstream input("in.txt");
	ofstream output("out.txt");
	ofstream p("p.txt");

	int Graph[Vertices][Vertices];
	for (int i = 0; i < Vertices; ++i)
	{
		for (int j = 0; j < Vertices; ++j)
		{
			Graph[i][j] = 0;		
		}			
	}

	/*for (int i = 0; i < Vertices; ++i)
	{
		for (int j = 0; j < Vertices; ++j)
			cout << Graph[i][j] << " ";
		cout << endl;
	}*/

	// Подсчитываем кол-во рёбер
	int Edges = 0;
	string line;
	while (getline(input, line))
		++Edges;

	input.close();

	// Считываем веса рёбер из файла
	input.open("in.txt");	
	for (int i = 0; i < Edges; ++i)
	{
		int start, finish, price;
		input >> start >> finish >> price;
		Graph[start - 1][finish - 1] = price;
	}
	input.close();
	/*for (int i = 0; i < Vertices; ++i)
	{
		for (int j = 0; j < Vertices; ++j)
			cout << Graph[i][j] << " ";
		cout << endl;
	}
*/
	Floyd(Graph, pathMatrix);

	int PointA, PointB;
	cout << "A: " ;
	cin >> PointA;
	cout << "B: " ;
	cin >> PointB;

	if (Graph[PointA - 1][PointB - 1] == 0)
		cout << "Path doesn't exist" << endl;
	else
	{
		cout << "Min price from A to B = " << Graph[PointA - 1][PointB - 1] << endl
			 << "Path from A to B: " << PointA << " ";

		printPath(PointA - 1, PointB - 1);

		cout << PointB << endl;
	}
		
		
	for (int i = 0; i < Vertices; i++)
	{
		for (int j = 0; j < Vertices; j++)
			output << Graph[i][j] << "\t";
		output << endl;
	}
	output.close();

	for (int i = 0; i < Vertices; i++)
	{
		for (int j = 0; j < Vertices; j++)
			p << pathMatrix[i][j] << "\t";
		p << endl;
	}
	p.close();
	

	return 0;
}