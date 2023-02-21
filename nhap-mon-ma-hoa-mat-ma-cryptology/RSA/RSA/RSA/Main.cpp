#include"Header.h"
#include"BigNum.h"
#include"Func.h"
#include"Codec.h"

bool writeKey(string filename, BigInt p, BigInt q, BigInt n, BigInt phi, BigInt Plkey, BigInt Pvkey);
void generateKeys(BigInt& EKey, BigInt& DKey, BigInt& N, int bits);

int main() {
	srand(time(0));

	BigInt EKey, DKey, N;
	int bits, check;
	string et, dt, nt, pPath,cPath;
	clock_t start, end;


	/*while (1) {
		cout << "Nhap duong dan cua file can ma hoa: ";
		cin >> pPath;
		cout << pPath;
		encript(pPath, ePath, EKey, N);
	}*/

	do {
		cout << "-----MA HOA RSA-----\n";
		cout << "Chon mot trong hai phuong phap nhap khoa sau:\n";
		cout << "Phim 1. Tu nhap khoa ca nhan.\n";
		cout << "Phim 2. Chuong trinh tu tao khoa.\n";
		cout << "Phim 3. Xem khoa.\n";
		cout << "Phim 4. Ma hoa van ban.\n";
		cout << "Phim 5. Giai ma van ban.\n";
		cout << "Phim 0. Thoat chuong trinh.\n";
		do {
			cout << "Nhap phim: ";
			cin >> check;
		} while (check < 0 || check > 5);
		cout << endl;
		switch (check) {
		case 1:
			cout << "Nhap khoa cong khai: ";
			cin >> et;
			cout << "Nhap khoa bi mat: ";
			cin >> dt;
			cout << "Nhap module: ";
			cin >> nt;
			EKey = intStrToVector(et);
			DKey = intStrToVector(dt);
			N = intStrToVector(nt);
			cout << "Nhap thanh cong!\n";
			break;
		case 2:
			cout << "-----TAO KHOA RSA-----\n";
			cout << "Chon do dai khoa: 512, 1024, 2048 bit\n";
			do {
				cout << "Nhap do dai: ";
				cin >> bits;
			} while (bits != 512 && bits != 1024 && bits != 2048);
			generateKeys(EKey, DKey, N, bits);
			break;
		case 3:
			if (EKey.size() == 0 || DKey.size() == 0)
				cout << "Chua tao khoa!";
			else
			{
				cout << "Khoa cong khai = ";
				printInt(EKey);
				cout << endl;
				cout << "Khoa bi mat = ";
				printInt(DKey);
				cout << endl;
				cout << "Modulo = ";
				printInt(N);
				cout << endl;
			}			
			break;
		case 4:
			if (EKey.size() == 0 || DKey.size() == 0)
				cout << "Chua tao khoa!";
			else
			{
				cout << "Nhap duong dan dau vao (plaintext): ";
				cin >> pPath;
				cout << "Nhap duong dan dau ra (ciphertext): ";
				cin >> cPath;
				start = clock();
				encrypt(pPath, cPath, EKey, N);
				end = clock();
				cout << "Thoi gian ma hoa: " << (float)(end - start) / CLOCKS_PER_SEC << "\n\n";
			}
			break;
		case 5:
			if (EKey.size() == 0 || DKey.size() == 0)
				cout << "Chua tao khoa!";
			else
			{
				cout << "Nhap duong dan dau vao (ciphertext): ";
				cin >> cPath;
				cout << "Nhap duong dan dau ra (plaintext): ";
				cin >> pPath;
				start = clock();
				decrypt(cPath, pPath, DKey, N);
				end = clock();
				cout << "Thoi gian giai ma: " << (float)(end - start) / CLOCKS_PER_SEC << "\n\n";
			}
			break;
		case 0:
			break;
		}

		if ( check!=0)
		{
			cout << "\n\nNhap phim 0 de thoat chuong trinh hoac phim bat ki de tiep tuc.\n";
			cout << "Nhap phim: ";
			cin >> check;
		}
		system("cls");
	} while (check);
	system("pause");
	return 0;
}

bool writeKey(string filename, BigInt p, BigInt q, BigInt n, BigInt phi, BigInt Plkey, BigInt Pvkey)
{
	fstream f;
	string temp = "-----BEGIN P PARAMETER------\n";

	for (int i = p.size() - 1; i >= 0; i--)
		temp += to_string(p[i]);
	temp += "\n-----END P PARAMETER------\n-----BEGIN Q PARAMETER------\n";

	for (int i = q.size() - 1; i >= 0; i--)
	{
		temp += to_string(q[i]);
	}
	temp += "\n-----END Q PARAMETER------\n-----BEGIN N PARAMETER------\n";
	for (int i = n.size() - 1; i >= 0; i--)
	{
		temp += to_string(n[i]);
	}
	temp += "\n-----END N PARAMETER------\n-----BEGIN PHI PARAMETER------\n";
	for (int i = phi.size() - 1; i >= 0; i--)
	{
		temp += to_string(phi[i]);
	}
	temp += "\n-----END PHI PARAMETER------\n-----BEGIN PUBLIC KEY------\n";
	for (int i = Plkey.size() - 1; i >= 0; i--)
	{
		temp += to_string(Plkey[i]);
	}
	temp += "\n-----END PUBLIC KEY------\n-----BEGIN PRIVATE KEY------\n";
	for (int i = Pvkey.size() - 1; i >= 0; i--)
	{
		temp += to_string(Pvkey[i]);
	}
	temp += "\n-----END PRIVATE KEY------\n";
	f.open(filename, ios::out | ios::trunc);
	f << temp;
	f.close();
	return 1;
}
void generateKeys(BigInt& EKey, BigInt& DKey, BigInt& N, int bits) {
	BigInt phi, q, p ;

	vector<float> pTimes, qTimes;
	clock_t start, end;

	// Tao va kiem tra so P
	cout << "Dang tao so nguyen to dau tien";
	while (1) {
		//cout << ".";
		do {
			BigBin pB = generateBin(bits / 2);
			p = binToInt(pB);
			cout << ".";
		} while (p[0] == 5);
		if (isPrime(p, 1, bits / 4 + 1))
			break;
	}
	// Tao va kiem tra so Q
	cout << "\nDang tao so nguyen to thu hai";
	while (1) {
		//cout << ".";
		do {
			BigBin qB = generateBin(bits / 2);
			q = binToInt(qB);
			cout << ".";
		} while (q[0] == 5);
		if (isPrime(q, 1, bits / 4 + 1) && q != p)
			break;
		end = clock();
	}
	cout << endl << endl;

	// Xuat P, Q ra man hinh
	cout << "Da tao thanh cong hai so nguyen to:\n";
	cout << "p = ";
	printInt(p);
	cout << "\nq = ";
	printInt(q);
	cout << endl << endl;

	// Tao va xuat N ra man hinh
	N = generateN(p, q);
	cout << "N = ";
	printInt(N);
	cout << endl << endl;

	// Tao xuat phi ra man hinh
	phi = generatePhi(p, q);
	cout << "phi = ";
	printInt(phi);
	cout << endl << endl;

	// Tao khoa thu 1
	EKey = generateEKey(phi, bits - 1);
	// Tao khoa thu 2
	DKey = generateDKey(EKey, phi);

	// Neu khoa 2 am thi cong them phi cho toi khi duong
	while (DKey[DKey.size() - 1] < 0)
	{
		DKey[DKey.size() - 1] *= -1;
		DKey = subExtended(phi, DKey);
	}

	// Chon khoa nho lam khoa cong khai, khoa lon thanh khoa bi mat
	if (compare(EKey, DKey) == 1)
	{
		swapBI(EKey, DKey);
	}

	// Xuat hai khoa ra man hinh
	cout << "Public key =  ";
	printInt(EKey);
	cout << endl << endl;

	cout << "Private key = ";
	printInt(DKey);
	cout << endl << endl;

	string t = "RSA" + to_string(bits) + "Bits.txt";
	writeKey(t, p, q, N, phi, EKey, DKey);
	cout << "Da ghi du lieu vao file " << t;
	cout << endl;
}