//#include <iostream>
//#include "TestExtins.h"
//#include "TestScurt.h"
//#include <chrono>
//#include "MD.h"
//
//using namespace std;
//
//int main() {
//
//		MD m;
//		m.adauga(1, 100);
//		m.adauga(1, 100);
//		m.adauga(2, 200);
//		m.adauga(3, 300);
//		m.adauga(1, 500);
//		m.adauga(2, 600);
//		m.adauga(4, 800);
//		m.adauga(6, 800);
//		m.adauga(6, 800);
//		m.adauga(6, 800);
//		m.adauga(6, 100);
//		//std::cout<<m.ceaMaiFrecventa();
//
//		std::chrono::time_point<std::chrono::system_clock> start, end;
//
//		start = std::chrono::system_clock::now();
//
//		testAll();
//		testAllExtins();
//
//		cout << "End ";
//		end = std::chrono::system_clock::now();
//
//		std::chrono::duration<double> elapsed_seconds = end - start;
//		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//
//		std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
//
//	//cout << "End";
//
//}