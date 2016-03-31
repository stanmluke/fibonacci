#include <iostream>
#include <map>
using namespace std;
//max number for uint64_t has been predetermined to be 93;
//it is calculatable for n-bits (where φ = (1 + √5)/2)
//n < 64*(log 2 / log φ) + 1/2*(log 5 / log φ) ≈ 92.19 + 1.67 ≈ 93.86
#define MAX_INDEX (93)

/* we use a recursive (iterative is more optimal) solution, 
 * just because I wanted to play with a memoize function.
 */
uint64_t 
fibo_memoize(unsigned n) {
	static map<unsigned,uint64_t> memo;

	if (n <= 1) {
		return n;
	}
	if (memo.count(n) > 0) {
		return memo[n];
	}
	// otherwise
	uint64_t ret = fibo_memoize(n-1) + fibo_memoize(n-2);
	memo[n] = ret;

	return ret;
}

/* primitive input handling, but it was non-iteresting.
 * we check for MAX_INDEX since numbers overflow, we could use
 * some kind of bigint handling, if we really cared.
 */
int main(int argc, char*argv[])
{
    int fibo_index = atoi(argv[1]);
    if (fibo_index < 0) {
	cerr << "Invalid request: " << fibo_index << endl;
	return -1;
    } else if (fibo_index > MAX_INDEX) {
        cerr << "Invalid max request: " << fibo_index << endl;
	return -1;
    }
    cout << "Fibonacci numbers for n=" << fibo_index << endl;
    for (int i=0; i<fibo_index; i++) {
	if (i != 0) { //separator after each number, except first and last
		cout << ", ";
	}
        cout << fibo_memoize(i);
    }
    cout << endl;
    return 0;
}
