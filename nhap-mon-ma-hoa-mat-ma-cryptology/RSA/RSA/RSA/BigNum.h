#include "Header.h"

// Van dang code tu tu. Can ham gi lien quan den big number thi noi toi code them

BigBin generateBin(int bits); //Tao so nguyen le n bit
BigInt binToInt(BigBin bin); //Chuyen so nhi phan sang thap phan


BigInt sumBI(BigInt a, BigInt b); //tinh tog hai vector 
BigInt subBI(BigInt a, BigInt b);
BigInt mulBI(BigInt a, BigInt b); // nhan hai vector
BigInt divBI(BigInt a, BigInt b);
BigInt divBasic(BigInt a, BigInt b);

BigInt subExtended(BigInt a, BigInt b); //mo rong cho so am
BigInt mulExtended(BigInt a, BigInt b); // mo rong cho so am
BigInt divExtended(BigInt a, BigInt b); // mo rong cho so am

void printBin(BigBin a); // in so nhi phan
void printInt(BigInt a); // in so thap phan
bool isPgreaterQ(BigInt& p, BigInt& q);
void swapBI(BigInt& a, BigInt& b);
BigInt remainderBI(BigInt num, BigInt m);
BigInt remainderBasic(BigInt a, BigInt b);
int compare(BigInt a, BigInt b);

