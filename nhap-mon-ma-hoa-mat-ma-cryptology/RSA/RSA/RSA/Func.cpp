#include "Func.h"

// buoc 1

bool isPrime(BigInt m, int iterations, int bits)
{
	BigInt t;
	if (m == BigInt{ 1 }) {
		return false;
	}
	for (int i = 0; i < iterations; i++) {
		BigBin pB = generateBin(bits);
		t = binToInt(pB);
		if (GCD(m, t) != BigInt{1})
			return false;
		if (powerMod(t, subBI(m, BigInt{ 1 }), m) != BigInt{ 1 }) {
			return false;
		}
	}
	return true;

}

// cac ham khac neu co
BigInt powerMod(BigInt x, BigInt y, BigInt p)
{
	BigInt res = { 1 };      // Initialize result
	x = remainderBI(x, p);  // Update x if it is more than or
	// equal to p
	while (y[y.size() - 1] > 0)
	{
		// If y is odd, multiply x with result
		if (y[0] % 2 == 1)
			res = remainderBI(mulBI(res, x), p);
			//y = subBI(y, { 1 });
		y = divBI(y, { 2 }); // y = y/2
		x = remainderBI(mulBI(x, x), p);
	}
	return res;
}

BigInt GCD(BigInt a, BigInt b) {
	if (a == b || b == BigInt{ 0 })
		return a;
	return GCD(b, remainderBI(a, b));
}
// buoc 2
BigInt generateN(BigInt p, BigInt q)
{
	BigInt N = mulBI(p, q);
	return N;
}

// buoc 3
BigInt generatePhi(BigInt p, BigInt q)
{
	BigInt phi = mulBI(sumBI(p, { -1 }), sumBI(q, { -1 }));
	return phi;
}

// buoc 4
BigInt generateEKey(BigInt phi, int bits)
{
	BigBin EKeyB(bits);
	EKeyB[0] = EKeyB[bits - 1] = 1;

	for (int i = 1; i < bits / 2; i++) {
		EKeyB[i] = 0;
	}

	for (int i = bits / 2; i < bits - 1; i++) {
		EKeyB[i] = rand() % 2;
	}
	BigInt EKey = binToInt(EKeyB);

	while (true)
	{
		if (GCD(phi, EKey) == BigInt{ 1 })
			break;
		EKey = sumBI(EKey, { 2 });
	}
	return EKey;
}

// buoc 5
BigInt generateDKey(BigInt e, BigInt phi)
{
	BigInt DKey = gcdExtended(e, phi);

	return DKey;
}

BigInt gcdExtended(BigInt a, BigInt b) {
	BigInt x = BigInt{ 1 };
	BigInt y = BigInt{ 0 };

	BigInt x1 = BigInt{ 0 };
	BigInt y1 = BigInt{ 1 };

	BigInt a1 = a;
	BigInt b1 = b;
	BigInt q, tmp;

	while (b1 != BigInt{ 0 }) {
		q = divExtended(a1, b1);

		tmp = a1;
		a1 = b1;
		b1 = subExtended(tmp, mulExtended(q, b1));

		tmp = x;
		x = x1;
		x1 = subExtended(tmp, mulExtended(q, x1));

		tmp = y;
		y = y1;
		y1 = subExtended(tmp, mulExtended(q, y1));
	}
	return x;
}