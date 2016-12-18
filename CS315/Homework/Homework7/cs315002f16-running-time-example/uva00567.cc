//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=508
//https://github.com/s4chin/UVa-Solutions/blob/master/00567.cpp
//minor changes JWJ 11/19/2016
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <chrono>
#include <ctime>
using namespace std;
#define oo 10000
//this size is specified in the problem description. For larger input sizes adjustments are needed.
		//for example, a loop that makes SIZE a variable and changes it from 10 to 100 with 10 increments


int main() {
	int count = 0, mincount = 0, n, c, t, a, b;
	int SIZE;
	cin >> SIZE;
	int fw[SIZE][SIZE];
	cout << SIZE-5 << "   ";
	std::chrono::time_point<std::chrono::system_clock> start, end;
	while(cin>>n) {
		mincount = 0;
		for(int i=0; i<SIZE; i++) for(int j=0; j<SIZE; j++) fw[i][j] = oo;
		for(int i=0; i<SIZE; i++) fw[i][i] = 0;
		for(int i=0; i<n; i++) {
			scanf("%d", &c);
			fw[0][c-1] = 1;
			fw[c-1][0] = 1;
		}
		for(int i=1; i<=SIZE-7; i++) {
			scanf("%d", &n);
			for(int j=0; j<n; j++) {
				scanf("%d", &c);
				fw[i][c-1] = 1;
				fw[c-1][i] = 1;
			}
		}
		
		start = std::chrono::system_clock::now();
		for(int k=0; k<SIZE-5; k++)
			for(int i=0; i<SIZE-5; i++)
				for(int j=0; j<SIZE-5; j++) {
					fw[i][j] = min(fw[i][j], fw[i][k] + fw[k][j]);
					++mincount;
				}
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end-start;
    		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		std::cout  << elapsed_seconds.count()<< "   " <<  mincount  << "   " << elapsed_seconds.count()/mincount <<  "\n";
		
		/*	
		scanf("%d", &t);
		printf("Test Set #%d:\n", count++);
		while(t--) {
			scanf("%d%d", &a, &b);
			printf("%d to %d: %d\n", a, b, fw[a-1][b-1]);
		}
		printf("\n");
		*/
	}
	return 0;
}
