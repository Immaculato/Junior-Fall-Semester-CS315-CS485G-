//http://en.cppreference.com/w/cpp/chrono
//g++ -std=c++11
//modified with calculating number of divisors: linear and sqrt methods
#include <iostream>
#include <chrono>
#include <ctime>
 
int divisors_count_n(unsigned n)
{
	int number = 0;
	for (int i = 1; i <= n; i++)
		if (n%i == 0) number +=1;
         return number;
}
int divisors_count_sqrt(unsigned n)
{
	int i;
	int number = 0;
	for (i = 1; i * i < n; i++)
		if (n%i ==0) number +=2;
	if (i * i == n) number++;
        return number;
}
 
int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::cout << "# for 3628800 = " << divisors_count_n(3628800) << '\n';
    end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::system_clock::now();
    std::cout << "# for 3628800 = " << divisors_count_sqrt(3628800) << '\n';
    end = std::chrono::system_clock::now();
 
//    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	elapsed_seconds = end-start;
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
