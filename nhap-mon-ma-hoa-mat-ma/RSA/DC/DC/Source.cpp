#include<iostream>
#include <utility>
using namespace std;

int y[16] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 }; //output S-box
int c[16] = { 8,2,11,7,4,9,13,14,5,12,0,10,3,15,6,1 }; //ciphertext 
pair<int, int> find_ab()
{
	//khai báo bảng đếm delta
	int delta_xy[16][16];
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			delta_xy[i][j] = 0;
		}
	}

	//tính giá trị bảng delta
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			int xorX = i ^ j; //xor x và delta_x
			int y_x = y[i];  //lấy giá trị	y tương ứng với x	
			int y_xorX = y[xorX]; // lấy giá trị y tương ứng với kết quả của x xor delta_x
			int delta_y = y_x ^ y_xorX; //xor 2 y với nhau => delta_y
			delta_xy[j][delta_y]++;    //cập nhật bẳng giá trị delta[delta_x][delta_y] tương ứng
		}
	}
	// Ve bang
	cout << "Bang phan phoi xac suat cua (delta X, delta Y)" << endl;
	for (int i = 0; i < 16; i++) {
		cout << "\t " << i;
	}
	cout << endl;
	for (int i = 0; i < 16; i++) {
		cout << i << "\t";
		for (int j = 0; j < 16; j++) {
			cout << delta_xy[i][j] << "\t ";
		}

		cout << endl;
	}
	cout << endl;

	//khai báo max tìm ra cặp delta_x, delta_y lớn nhất trong bảng
	int max = -1;
	pair<int, int> ab;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			if (i != 0 && j != 0) {//loại trừ trường hợp delta_x = delta_y = 0	
				if (delta_xy[i][j] > max) {
					max = delta_xy[i][j];
					ab.first = i; //cập nhật a
					ab.second = j;//cập nhật b
				}
			}
	cout << "Ta tim duoc cap (a,b) = (" << ab.first << "," << ab.second << ") voi xac suat xuat hien cao nhat la: " << max << endl << endl;
	return ab;
}

void findKey(int a, int b)
{
	int x[16]; //input
	for (int i = 0; i < 16; i++)
	{
		x[i] = i;
	}

	int Ppair[16][2]; //bảng chọn P - P'
	for (int i = 0; i < 16; i++)
	{
		Ppair[i][0] = x[i];
		Ppair[i][1] = x[i] ^ a;
	}

	int Cpair[16][2]; //bảng chọn C - C'
	for (int i = 0; i < 16; i++)
	{
		Cpair[i][0] = c[Ppair[i][0]];
		Cpair[i][1] = c[Ppair[i][1]];
	}

	for (int i = 0; i < 16; i++)
	{
		if (Cpair[i][0] ^ Cpair[i][1] == b) //điều kiện C' = C xor b
		{
			int c1 = Cpair[i][0]; //C
			int c2 = Cpair[i][1]; //C'
			int p1 = Ppair[i][0]; //P
			int p2 = Ppair[i][1]; //P'
			int k1 = c1 ^ y[p1]; //K = C xor Sbox(P)
			int k2 = c2 ^ y[p2]; //K = C xor Sbox(P')
			if (k1 == k2) {
				cout << "Ta chon cap (P,P') = (" << p1 << "," << p2 << ") "<< endl;
				cout << "Thong qua thuat toan ta duoc (C,C') = (" << c1 << "," << c2 << ") " << endl << endl;
				cout << "Ta tim duoc khoa la: " << k1 << endl; //kết luận
				system("pause");
				break;
			}
		}
	}
}
void printTable(int x[])
{
	
	cout << "In: \t";
	for (int i = 0; i < 16; i++)
		cout << i << "\t ";
	cout << endl;
	cout << "Out: \t";
	for (int i = 0; i < 16; i++)
		cout << x[i] << "\t ";
	cout << endl;
}
int main()
{

	cout << "Gia su ta tim duoc bang ma cua Sbox: \n";
	printTable(y);
	cout << "\nGia su ta tim duoc bang ma cua thuat toan: \n";
	printTable(c);
	cout << endl;

	pair<int, int> ab;
	ab = find_ab();
	
	findKey(ab.first, ab.second);
	return 0;
}


