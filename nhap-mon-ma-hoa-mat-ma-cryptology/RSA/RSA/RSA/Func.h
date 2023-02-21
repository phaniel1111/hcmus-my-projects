#include "Header.h"
#include "BigNum.h"


//Buoc 1
bool isPrime(BigInt n, int k, int bits);
BigInt powerMod(BigInt x, BigInt y, BigInt p);
BigInt GCD(BigInt a, BigInt b);
//Buoc 2
BigInt generateN(BigInt p, BigInt q);
//Buoc 3
BigInt generatePhi(BigInt p, BigInt q);
//Buoc 4
BigInt generateEKey(BigInt phi, int bits);
//Buoc 5
BigInt generateDKey(BigInt e, BigInt phi);
BigInt gcdExtended(BigInt a, BigInt b);
