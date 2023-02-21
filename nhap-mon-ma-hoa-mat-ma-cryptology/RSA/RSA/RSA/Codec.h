#include "Header.h"

bool readScript(string P, string& data);
bool writeScript(string P, string data);
BigInt intStrToVector(string s);
string vectorToIntStr(BigInt v);
string strToAsciiNumber(string data);
string asciiNumberToStr(string data);
void encrypt(string P, string C, BigInt rPK, BigInt N);
string encode(string pt2, BigInt rPK, BigInt N);

void decrypt(string C, string P, BigInt rPK, BigInt N);
string decode(string data, BigInt rPK, BigInt N);