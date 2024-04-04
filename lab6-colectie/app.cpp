#include <iostream>
#include "colectie.h"
#include "iterator.h"
#include "testExtins.h"
#include "testScurt.h"
#include <chrono>
using namespace std;


int main() {
		/*testAll();
		testAllExtins();
	cout << "End";*/
	std::chrono::time_point<std::chrono::system_clock> start, end;

	start = std::chrono::system_clock::now();

	testAll();
	cout << "Test scurt gata!\n";
	testAllExtins();
	cout << "Test extins gata!\n";
	cout << "End \n";
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
