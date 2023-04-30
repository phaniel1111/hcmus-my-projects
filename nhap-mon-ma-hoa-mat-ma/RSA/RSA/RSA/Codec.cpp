#include"Codec.h"
#include"BigNum.h"
#include"Func.h"
//----
bool readScript(string P, string& data)
{
	fstream f;
	f.open(P, ios::in);


	while (!f.eof())
	{
		string n;
		getline(f, n);
		data += n + "\\n";
	}

	f.close();
	return true;
}
bool writeScript(string P, string data)
{
	vector<string> result;
	string::size_type pos = 0;
	string::size_type prev = 0;
	string separator = "\\n";
	while ((pos = data.find(separator, prev)) != string::npos) {
		result.push_back(data.substr(prev, pos - prev));
		prev = pos + separator.length();
	}
	// Add the last token
	result.push_back(data.substr(prev));

	fstream f;
	f.open(P, ios::out);

	for (const string& str : result) {
		f << str << endl;
	}

	f.close();
	return true;
}
BigInt intStrToVector(string str)
{
	BigInt i;
	for (char c : str) {
		if (c >= '0' && c <= '9') {
			i.push_back(c - '0');
		}
	}
	reverse(i.begin(), i.end());
	return i;
}
string vectorToIntStr(BigInt v)
{
	reverse(v.begin(), v.end());
	string ss;
	for (size_t i = 0; i < v.size(); ++i) {
		ss += to_string(v[i]);
	}
	return ss;
}


string strToAsciiNumber(string data)
{
	string i;

	for (char c : data) {
		c -= 31;
		if (c < 10) i += '0';
		i += to_string(static_cast<int>(c));
	}
	return i;
}

string asciiNumberToStr(string data)
{
	string result;
	int i = 0;
	while(i < data.size())
	{
		string temp = data.substr(i, 2);
		int num = stoi(temp) + 31;
		result += char(num);
		i += 2;
	}
	return result;
}

//---
void encrypt(string P, string C, BigInt rPK, BigInt N)
{
	string pt1;
	
	if(readScript(P, pt1)) cout << "Doc file thanh cong!\n";
	//cout << pt1 << endl;
	cout << "Dang tien hanh ma hoa...\n";
	string pt2 = strToAsciiNumber(pt1);
	//cout << pt2 << endl;
	//cout << endl;
	string data = encode(pt2, rPK, N);
	cout << "Ma hoa thanh cong.\n";
	if (writeScript(C, data)) cout << "Da ghi vao file theo duong dan: " << C << endl;
}

string encode(string pt2, BigInt rPK, BigInt N)
{
	string result;
	int n = N.size() - 2;
	int i = 0;
	while (i < pt2.size()) 
	{
		string temp = pt2.substr(i, n);
		BigInt temp2 = intStrToVector(temp);

		BigInt cblock = powerMod(temp2, rPK, N);

		while(cblock.size() < n + 2)
			cblock.push_back(0);

		string temp3 = vectorToIntStr(cblock);
		result += temp3 ;
		i += n;
	}
	//cout << result;

	return result;
}

void decrypt(string C, string P, BigInt rPK, BigInt N)
{
	string pt1;

	if (readScript(C, pt1)) cout << "Doc file thanh cong!\n";
	//cout << pt1 << endl;
	cout << "Dang tien hanh giai ma...\n";
	string data = decode(pt1, rPK, N);
	cout << "Giai ma thanh cong.\n";
	if (writeScript(P, data)) cout << "Da ghi vao file theo duong dan: " << P << endl;
}

string decode(string data, BigInt rPK, BigInt N)
{
	string result;
	int n = N.size();
	int i = 0;
	while (i +n < data.size())
	{
		string temp = data.substr(i, n);

		BigInt temp2 = intStrToVector(temp);
		//cout << "Tach chuoi: \n";
		//printInt(temp2);
		//cout << endl;

		BigInt cblock = powerMod(temp2, rPK, N);
		if(cblock.size() % 2 == 1)
			cblock.push_back(0);
		string temp3 = vectorToIntStr(cblock);
		//cout << "decode: \n" << temp3 << endl;
		string temp4 = asciiNumberToStr(temp3);
		result += temp4;
		i += n;
	}

	//cout << result;
	return result;
}