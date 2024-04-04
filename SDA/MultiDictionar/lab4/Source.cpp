//#include <iostream>
//#include <new>
//
//using namespace std;
//
//int* urm;
//int* prec;
//
//
//
//int main() {
//	int cp = 10;
//	urm = new int[cp];
//	prec = new int[cp];
//	for (int i = 0;i < cp -1;i++)
//	{
//		urm[i] = i + 1;
//		prec[i] = i - 1;
//		cout << urm[i] << " " << prec[i] << '\n';
//	}
//	urm[cp - 1] = -1;
//	prec[cp - 1] = cp - 2;
//	cout << urm[cp-1] << " " << prec[cp-1] << '\n';
//	int* urmNou = new int[2 * cp];
//
//	int* precNou = new int[2 * cp];
//
//	//copiem vechile valori in noua zona
//	for (int i = 0; i < cp; i++)
//	{
//		//eNou[i] = e[i];
//		urmNou[i] = urm[i];
//		precNou[i] = prec[i];
//	}
//
//	
//
//
//	//dublam capacitatea
//	cp = 2 * cp;
//
//for (int i = cp/2 - 1;i < cp - 1;i++)
//	{
//		urmNou[i] = i + 1;
//		precNou[i] = i - 1;
//		//cout << urm[i] << " " << prec[i] << '\n';
//	}
//	urmNou[cp - 1] = -1;
//	precNou[cp - 1] = cp - 2;
//	//eliberam vechea zona
//	//delete[] e;
//	delete[] urm;
//	delete[] prec;
//
//	//vectorul indica spre noua zona
//	//e = eNou;
//	urm = urmNou;
//	prec = precNou;
//
//	cout << cp;
//	for (int i = 0;i < cp ;i++)
//	{
//	//	urm[i] = i + 1;
//		//prec[i] = i - 1;
//		cout << urm[i] << " " << prec[i] << '\n';
//	}
//}
//
//#include <iostream>
//#include <vector>
//#include <queue>
//#include <limits>
//
//#define INF std::numeric_limits<int>::max()
//
//// Structura pentru a reprezenta o muchie în graf
//struct Edge {
//    int destination;
//    int weight;
//};
//
//// Funcția pentru a implementa algoritmul lui Dijkstra
//void Dijkstra(std::vector<std::vector<Edge>>& graph, int startNode) {
//    int numNodes = graph.size();
//
//    // Inițializează vectorul de distanțe cu infinit
//    std::vector<int> dist(numNodes, INF);
//
//    // Coada de priorități pentru a selecta nodurile cu cea mai mică distanță
//    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
//
//    // Setează distanța nodului de start la 0 și îl adaugă în coadă
//    dist[startNode] = 0;
//    pq.push(std::make_pair(dist[startNode], startNode));
//
//    while (!pq.empty()) {
//        int u = pq.top().second;
//        pq.pop();
//
//        // Parcurge toate muchiile nodului u
//        for (const auto& edge : graph[u]) {
//            int v = edge.destination;
//            int weight = edge.weight;
//
//            // Verifică dacă există o cale mai scurtă către v prin u
//            if (dist[u] != INF && dist[u] + weight < dist[v]) {
//                // Actualizează distanța minimă
//                dist[v] = dist[u] + weight;
//                pq.push(std::make_pair(dist[v], v));
//            }
//        }
//    }
//
//    // Afișează rezultatele
//    std::cout << "Distanțele minime de la nodul de start la fiecare nod:\n";
//    for (int i = 0; i < numNodes; ++i) {
//        std::cout << "Nod " << i << ": " << dist[i] << '\n';
//    }
//}
//
//int main() {
//    int numNodes = 5; // Numărul de noduri în graf
//
//    // Inițializarea grafului cu numNodes noduri
//    std::vector<std::vector<Edge>> graph(numNodes);
//
//    // Adăugarea muchiilor în graf
//    graph[0].push_back({ 1, 4 }); // Adăugă o muchie de la nodul 0 la nodul 1 cu costul 4
//    graph[0].push_back({ 2, 1 });
//    graph[1].push_back({ 3, 1 });
//    graph[2].push_back({ 1, 2 });
//    graph[2].push_back({ 3, 5 });
//    graph[3].push_back({ 4, 3 });
//
//    int startNode = 0; // Nodul de start
//
//    // Apelul funcției Dijkstra
//    Dijkstra(graph, startNode);
//
//    return 0;
//}

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream f("sursa.txt");
ofstream g("fisier.out");
int n, m, mat[100][100], x, y, i, j;
vector<int> v[100];
int main() {
	f >> n;
	while (f >> x) {
		f >> y;
		mat[x][y] = 1;
		mat[y][x] = 1;


	}
	//mat.adc->lista
	for (i = 1; i <= n; i++, g << endl)
		for (j = 1; j <= n; j++)
		{
			g << mat[i][j] << " ";
			if (mat[i][j] == 1)
				v[i].push_back(j);
		}
	g << endl;
	for (i = 1; i <= n; i++)
	{
		g << i << ":";
		for (j = 0; j < v[i].size(); j++)
			g << v[i][j] << " ";
		g << '\n';
	}
	//lista adc->mat.adc
	int m[100][100] = {};
	for (i = 1;i <= n;i++)
		while (v[i].size() > 0) {
			int j = v[i].back();
			v[i].pop_back();
			m[i][j] = 1;

		}

	for (i = 1; i <= n; i++, g << endl)
		for (j = 1; j <= n; j++)

			g << m[i][j] << " ", m[i][j] = 0;
	g << endl;
	//mat.adc->mat.inc
	int nr = 0;
	for (j = 1;j <= n;j++)
		for (i = 1; i <= n; i++)
		{
			if (mat[i][j] == 1)
			{
				nr++;
				m[i][nr] = 1;
				m[j][nr] = 1;
				mat[j][i] = 0;
				mat[i][j] = 0;

			}

		}
	for (i = 1; i <= n; i++, g << endl)
		for (j = 1; j <= nr; j++)

			g << m[i][j] << " ";
	//mat.inc->mat.adc
	for (j = 1; j <= nr; j++)
	{
		int x1 = 0;
		int x2 = 0;
		for (i = 1; i <= n; i++)
		{
			if (m[i][j] == 1)
				if (x1 == 0)x1 = i;
				else x2 = i;


		}
		mat[x1][x2] = 1;
		mat[x2][x1] = 1;
	}
	g << endl;
	for (i = 1; i <= n; i++, g << endl)
		for (j = 1; j <= n; j++)

			g << mat[i][j] << " ";

	//mat incidenta(m)->lista adiacenta
	for (j = 1; j <= nr; j++)
	{
		int	x1 = 0;
		int x2 = 0;
		for (i = 1; i <= n; i++)
		{

			if (m[i][j] == 1)
				if (x1 == 0)x1 = i;
				else x2 = i;



		}
		v[x1].push_back(x2);
		v[x2].push_back(x1);
	}


	for (i = 1; i <= n; i++)
	{
		g << i << ":";
		for (j = 0; j < v[i].size(); j++)
			g << v[i][j] << " ";
		g << '\n';
	}

	//lista adc->mat.inc
	for (i = 1; i <= n; i++)
		for (j = 1; j <= nr; j++)

			m[i][j] = 0;
	nr = 0;
	for (i = 1;i <= n;i++)
		while (v[i].size() > 0) {
			nr++;
			int x1 = v[i].back();
			v[i].pop_back();
			for (j = 0; j < v[x1].size(); j++) {
				if (v[x1][j] == i)
					v[x1][j] = v[x1].back();
				v[x1].pop_back();
			}
			m[i][nr] = 1;
			m[x1][nr] = 1;

		}
	g << endl;
	for (i = 1; i <= n; i++, std::cout << endl)
		for (j = 1; j <= nr; j++)
			std::cout << m[i][j] << " ";
}