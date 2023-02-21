#include "FS.h"

// data: block 18636
int main() {

	char volumeName[] = "MyFS.dat";
	LPCWSTR volumeName1 = L"MyFS.dat";
	int volumeSize;
	int button = 0;
	bool isOK;
	superBlock sb;
	int GETbytePerBlock;
	int GETsuperBlockSize;
	int GETblocksInVolume;
	int GETFATsize;
	char* GETpw = new char[8];
	vector<FAT> fat;
	char* GETfileName = NULL;
	char* GETfileFormat = NULL;
	char* GETpassword = NULL;
	int GETfileSize;
	int GETstartBlock;
	int GETtotalBlocks;
	FAT entry;
	char* systemFile = new char;
	char t[8] = "System";
	char* t2 = new char[8];
	int pos;
	int t1 = 0, s = 0, e = 0;
	BYTE* buffer = new BYTE[512];
	char* pw = new char[8];
	bool check = false;

	// Doc superBloack
	buffer = readBlock(0, volumeName1);
	if (buffer != NULL) {
		sb = blockTosuperBlock(buffer);
		getInfo(sb, GETbytePerBlock, GETsuperBlockSize, GETblocksInVolume, GETFATsize, GETpw);
		if (buffer[11] != NULL) {
			while (1) {
				cout << "Nhap mat khau: ";
				cin >> pw;
				for (int i = 0; i < strlen(pw); i++) {
					if (pw[i] != GETpw[i])
					{
						cout << "Sai mat khau. Hay nhap lai." << endl;
						check = false;
						break;
					}
					check = true;
				}
				if (check == true)
				{
					cout << "Mo khoa thanh cong" << endl;
					break;
				}
			};
		}
		sb = blockTosuperBlock(buffer);
		getInfo(sb, GETbytePerBlock, GETsuperBlockSize, GETblocksInVolume, GETFATsize, GETpw);
	}

	do {
		// Menu
		cout << "-----HE THONG TAP TIN-----" << endl;
		cout << "Phim 1: Tao volume (Kich thuoc 128 MB)" << endl;
		cout << "Phim 2: Dat mat khau cho volume, neu da ton tai thi thay doi mat khau (Toi da 8 ki tu)" << endl;
		cout << "Phim 3: In ra danh sach cac tap tin." << endl;
		cout << "Phim 4: Doi mat khau file" << endl;
		cout << "Phim 5: Import tap tin vao MyFS" << endl;
		cout << "Phim 6: Export tap tin ra MyFS" << endl;
		cout << "Phim 7: Xoa tap tin trong MyFS" << endl;
		cout << "Phim 0: Thoat chuong trinh" << endl;
		cout << "-----------" << endl;
		cout << "Moi ban chon phim: ";
		cin >> button;

		// Cases
		switch (button) {
			case 1:
				fat.clear();
				volumeSize = 128;
				createBlankVolume(volumeName, volumeSize);
				sb = createSupperBlock(volumeSize);
				isOK = isWriteSuperBlock(sb, volumeName1);
				if (!isOK) {
					cout << "Khong the tao super block" << endl;
					return 0;
				}
				buffer = readBlock(0, volumeName1);
				sb = blockTosuperBlock(buffer);
				getInfo(sb, GETbytePerBlock, GETsuperBlockSize, GETblocksInVolume, GETFATsize, GETpw);
				systemFile = t;
				entry = createEntry(systemFile, systemFile, systemFile, 0, 18635, 18635);
				fat.push_back(entry);
				isOK = writeFAT(fat, volumeName1);
				fat.clear();
				if (!isOK) {
					cout << "Khong the ghi vao bang FAT" << endl;
					return 0;
				}
				cout << "Tao volume thanh cong";
				break;
			case 2:
				if (buffer == NULL)
				{
					cout << "Hay tao volume";
					break;
				}
				modifyPassword(sb);
				isOK = isWriteSuperBlock(sb, volumeName1);
				if (!isOK)
					cout << "Khong the tao mat khau" << endl;
				else
					cout << "Tao mat khau thanh cong";
				buffer = readBlock(0, volumeName1);
				sb = blockTosuperBlock(buffer);
				getInfo(sb, GETbytePerBlock, GETsuperBlockSize, GETblocksInVolume, GETFATsize, GETpw);
				break;
			case 3:
				if (buffer == NULL)
				{
					cout << "Hay tao volume";
					break;
				}
				fat.clear();
				cout << "---Danh sach tap tin---" << endl;
				readFAT(fat, volumeName1);
				printFAT(fat);
				fat.clear();
				break;
			case 4:
				if (buffer == NULL)
				{
					cout << "Hay tao volume";
					break;
				}
				fat.clear();
				readFAT(fat, volumeName1);
				modifyFilePassword(fat);
				isOK = writeFAT(fat, volumeName1);
				if (!isOK)
					cout << "Khong the doi mat khau" << endl;
				else
					cout << "Doi mat khau thanh cong";
				fat.clear();
				break;
			case 5:
				if (buffer == NULL)
				{
					cout << "Hay tao volume";
					break;
				}
				fat.clear();
				readFAT(fat, volumeName1);
				isOK = importfile(fat, volumeName1);
				if (!isOK)
					cout << "Khong the import";
				else
					cout << "Import thanh cong";
				fat.clear();
				break;
			case 6:
				if (buffer == NULL)
				{
					cout << "Hay tao volume";
					break;
				}
				fat.clear();
				readFAT(fat, volumeName1);
				isOK = exportfile(fat, volumeName1);
				if (!isOK)
					cout << "Khong the export";
				else
					cout << "Export thanh cong";
				fat.clear();
				break;
			case 7:
				fat.clear();
				readFAT(fat, volumeName1);
				printFAT(fat);

				cin.ignore();
				cout << "Nhap ten file: ";
				fgets(t2, 8, stdin);
				pos = findFile(fat,t2);
				if (pos == 0)
				{
					cout << "Khong the xoa system";
					break;
				}
				removeFile(fat, pos);
				isOK = removeFAT(fat, volumeName1);
				isOK = writeFAT(fat, volumeName1);
				if (!isOK)
					cout << "Khong the xoa file" << endl;
				else
					cout << "Xoa file thanh cong";
				fat.clear();
				break;
			case 0:
				break;
			default:
				break;
		}
		cout << endl << endl;
		system("pause");
		system("cls");
	} while (button);


	system("pause");
	return 0;
}