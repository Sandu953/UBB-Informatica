#include <iostream>
#include "testExtins.h"
#include "testScurt.h"
#include "multime.h"
#include "iterator.h"
#include <chrono>
using namespace std;



int main() {
	/*Multime a;
	a.adauga(1);
	a.adauga(2);
	a.adauga(3);

	Multime b;
	b.adauga(2);
	b.adauga(6);
	b.adauga(7);
	b.adauga(8);

	a.reuniune(b);

	IteratorMultime i = a.iterator();
	while (i.valid()) {
		cout << i.element() << " ";
		i.urmator();
	}*/

	std::chrono::time_point<std::chrono::system_clock> start, end;

	start = std::chrono::system_clock::now();

	cout << "Start \n";
	testAll();
	cout << "Test scurt gata!\n";
	testAllExtins();

	cout << "End ";
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

}
