#include <iostream>
#include <sstream>
#include <map>
#include <errno.h>

using namespace std;
//max number for uint64_t has been predetermined to be 93;
//it is calculatable for n-bits (where φ = (1 + √5)/2)
//n < 64*(log 2 / log φ) + 1/2*(log 5 / log φ) ≈ 92.19 + 1.67 ≈ 93.86
#define MAX_INDEX (93)	/* or the first 94 fibonacci #'s */

/* here we are using a recursive solution (iterative is acutally 
 * more optimal), just because I wanted to entertain a memoize function.
 */
int 
fibo_memoize(unsigned n, uint64_t &fn) {
	/* NB: for large requests of n, this can consume memory
	 * (although fibonacci goes exponential quickly, see MAX_INDEX)
	 * and why an iterative solution would be optimal for both
	 * space & time consumptions.
	 */
	int err;
	static map<unsigned,uint64_t> memo;

	if (n <= 1) {
		fn = n;
		return 0;
	} else if (n > MAX_INDEX) {
		cout << "too big" << endl;
		return E2BIG;
	}
	if (memo.count(n) > 0) {
		fn = memo[n];
		return 0;
	}
	// otherwise
	uint64_t ret;
	if (0 == (err = fibo_memoize(n-1, ret))) {
		memo[n] = ret;
	} else
		return err;
	if (0 == (err = fibo_memoize(n-2, ret))) {
		memo[n] += ret;
		fn = memo[n];
	} else
		return err;

	return 0;
}

