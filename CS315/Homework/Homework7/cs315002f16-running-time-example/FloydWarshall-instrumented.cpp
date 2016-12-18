//prepared for CS315-002 Fall 2016: basic solution implemented by CS315002 Fall 2016 student (WS)
//instrumented for experiments: JWJ
//time measure (chrono)  added: JWJ
/*testing on an input matrix with teh format
 * n -- size of the matrix
 * 0   a_12  ... a_1n
a_21 0    ... a_2n
 * ...
 * a_n1 a_n2 ...  0
 * 
 * a_ij -- edge weight
 * The main diagonal - 0s
 * Missing diagonals - 0s
 * 
 * In this experiment just one matrix M of size 100 x 100 is used.
 * To test for sizes m = 10, 12, ..., we use the initial m rows and columns of M.
 * Each next size is the previous size times 1.2. With O(n^3) algorithm, we are  expecting
 * the running  time to multiply by (1.2)^3,  which is yet another comparison/verification method.  
 * Size of the instance, and times, as well as the number of min operations, are written to stdout.
 * They can be redirected to a file that later can be used by gnuplot or Excel for charting run-time relevant quantities.
 * 
 * In this example we plot time and fit it with a*x^3 function (gnuplot can find the coefficient a).
*/



#include <iostream>
#include <cstring>
#include <chrono>
#include <ctime>
#define oo 100000

using namespace std;

int main() {
	int N;
	int count = 0;
    std::chrono::time_point<std::chrono::system_clock> start, end;
	scanf("%d", &N);
	int M[N][N] = {{0}};
	int D[N][N] = {{0}};
	// Set matrix to all 0 at first
	// oo will be read in
	memset(M, 0, sizeof(M[0][0]) * N * N);
	memset(D, 0, sizeof(D[0][0]) * N * N);
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			scanf("%d", &M[i][j]);
			if (M[i][j] == 0 && i != j) M[i][j] = oo;
                        D[i][j] = M[i][j];
	}}

for(int m = 10; m <=N; m=(int)m*1.2){ //this loop is to compute consecutive test sizes 
		printf("%3d ", m);
		count = 0;
    start = std::chrono::system_clock::now();
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < m; j++) D[i][j] = M[i][j];} //copy M to D since D changed
	for(int k = 0; k < m; k++) {
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < m; j++) {
				// If either one of those cells are oo, then we know that this
				// cannot be a valid distance, so we skip forward to avoid overflow
				count++;
				if(D[i][k] == oo || D[k][j] == oo)
					continue;
				// If statement from Wikipedia
				if(D[i][j] > D[i][k] + D[k][j])
					D[i][j] = D[i][k] + D[k][j];
	}}}
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

/*    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
*/
              std::cout  << elapsed_seconds.count()<< "   " <<  count  << "   " << elapsed_seconds.count()/count <<  "\n";

	}
/*
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			printf("%3d ", D[i][j]);
		}
		printf("\n");
	}
*/
	return 0;
}
