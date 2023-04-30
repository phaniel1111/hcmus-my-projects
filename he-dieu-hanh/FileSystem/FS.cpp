#include "FS.h"


//----------1
// Tao volumn rong
void createBlankVolume(char volumeName[], int volumeSize) {
	fstream f;
	f.open(volumeName, ios::trunc | ios::out);
	BYTE block[BPB]; // each block take 512 byte
	for (int i = 0; i < BPB; i++) {
		block[i] = BYTE(0);
	}
	int totalBLock = (volumeSize * 1048576) / 512; //1 MB = 1048576B
	for (int i = 0; i < totalBLock; i++) {
		f.write((char*)&block, BPB);
	}
	f.close();
}
// Tao superblock
superBlock createSupperBlock(int volumeSize) {
	superBlock sb;

	sb.bytePerBlock[0] = BYTE(0);
	sb.bytePerBlock[1] = BYTE(2);

	int biv = (1024 * 1024 * volumeSize) / 512; // don vi: block
	BYTE* temp = decToHexaLE(biv, 4);
	for (int i = 0; i < 4; i++)
		sb.blocksInVolume[i] = temp[i];

	BYTE* temp1 = decToHexaLE(32, 1);
	sb.superBlockSize[0] = temp1[0];

	int fs = (1024 * 1024 * volumeSize / 512) * 32;
	BYTE* temp2 = decToHexaLE(fs, 4);
	for (int i = 0; i < 4; i++)
		sb.FATsize[i] = temp2[i];

	for (int i = 0; i < 8; i++)
		sb.password[i] = NULL;

	return sb;
}
// ghi superblock vao volume
// Tham khao tu https://github.com/ngohuudang/mid_term_OS/blob/main/volumeMyFS/Source.cpp
bool isWriteSuperBlock(superBlock sb, LPCWSTR volumeName) {
	DWORD bytesRead;
	HANDLE headerFile;
	headerFile = CreateFile(volumeName,
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	SetFilePointer(headerFile, 0, NULL, FILE_BEGIN);
	bool isOK = WriteFile(headerFile, &sb, sizeof(sb), &bytesRead, NULL);
	CloseHandle(headerFile);
	return isOK;
}
// chuyen cac thanh phan cua superblock thanh du lieu doc duoc
void getInfo(superBlock sb, int& GETbytePerBlock, int& GETsuperBlockSize, int& GETblocksInVolume, int& GETFATsize, char*& GETpw) {
	GETbytePerBlock = reverseByte(sb.bytePerBlock, 2);
	GETsuperBlockSize = reverseByte(sb.superBlockSize, 1);
	GETblocksInVolume = reverseByte(sb.blocksInVolume, 4);
	GETFATsize = reverseByte(sb.FATsize, 4);

	for (int i = 0; i < 8; i++) {
		GETpw[i] = sb.password[i];
	}
}
// chuyen chuoi BYTE thanh struct superblock
superBlock blockTosuperBlock(BYTE* block) {
	superBlock sb;
	sb.bytePerBlock[0] = block[0];
	sb.bytePerBlock[1] = block[1];
	sb.superBlockSize[0] = block[2];
	sb.blocksInVolume[0] = block[3];
	sb.blocksInVolume[1] = block[4];
	sb.blocksInVolume[2] = block[5];
	sb.blocksInVolume[3] = block[6];
	sb.FATsize[0] = block[7];
	sb.FATsize[1] = block[8];
	sb.FATsize[2] = block[9];
	sb.FATsize[3] = block[10];
	for (int i = 0; i < 8; i++) {
		sb.password[i] = block[i+11];
	}
	return sb;
}

//----------2
// Doi mat khau volume
void modifyPassword(superBlock& sb) {
	char* temp = new char[8];
	cin.ignore();
	cout << "Nhap mat khau: ";
	fgets(temp,8,stdin);
	
	for (int i = 0; i < 8; i++) {
		sb.password[i] = temp[i];
	}
}

//----------3
// kiem tra entry trong hay khong
bool isEmptyEntry(int index, BYTE* buffer) {
	if (buffer[index] != BYTE(0))
		return false;
	return true;
}
// remove fat
bool removeFAT(vector<FAT> fat, LPCWSTR fileName) {
		DWORD bytesRead;
	HANDLE hFile;
	bool flag;
	hFile = CreateFile(fileName,
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	
	BYTE buffer[32];
	for (int j = 0; j < 32; j++) {
		buffer[j] = BYTE(0);
	}
	int i = 0;
	for (auto& element : fat) {
		SetFilePointer(hFile, BPB + 32 +i, NULL, FILE_BEGIN);
		flag = WriteFile(hFile, &buffer, 32, &bytesRead, NULL);
		i += 32;
	}
	CloseHandle(hFile);
	return flag;
}
// tao entry
FAT createEntry(char* fileName, char* fileFormat, char* password, int fileSize, int startBlock, int endBlock) {
	FAT entry;

	for (int k = 0; k < 8; k++)
	{
		entry.fileName[k] = fileName[k];
		entry.password[k] = NULL;
	}
	for (int k = 0; k < 4; k++)
	{
		entry.fileFormat[k] = fileFormat[k];
	}
	BYTE* temp = decToHexaLE(fileSize, 4);
	for (int i = 0; i < 4; i++)
		entry.fileSize[i] = temp[i];
	BYTE* temp1 = decToHexaLE(startBlock, 4);
	for (int i = 0; i < 4; i++)
		entry.startBlock[i] = temp1[i];
	BYTE* temp2 = decToHexaLE(endBlock, 4);
	for (int i = 0; i < 4; i++)
		entry.endBlock[i] = temp2[i];
	return entry;
}
// viet fat
bool writeFAT(vector<FAT> fat, LPCWSTR fileName) {
	DWORD bytesRead;
	HANDLE hFile;
	bool flag;
	hFile = CreateFile(fileName,
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	int i = 0;
	for (auto& element : fat) {
		SetFilePointer(hFile, BPB + i, NULL, FILE_BEGIN);
		flag = WriteFile(hFile, &element, 32, &bytesRead, NULL);
		i += 32;
	}
	CloseHandle(hFile);
	return flag;
}
// doc tu volume
void readFAT(vector<FAT>& fat,LPCWSTR fileName) {
	BYTE* buffer = new BYTE[512];
	FAT entry;
	for (int i = 1; i < 100; i++)
	{
		buffer = readBlock(i, fileName);
		//cout << "Block: " << i << endl;
		for (int j = 0; j < BPB; j+=32) { // j/32
			
			if (!isEmptyEntry(j, buffer))
			{
				//cout << "\tEntry: " << j / 32 << endl;				
				for (int k = 0; k < 8; k++)
				{
					entry.fileName[k] = buffer[j + k];
					entry.password[k] = buffer[j + 12 + k];
				}
				//cout << "XXX" << entry.fileName << "XXX" << endl;
				
				for (int k = 0; k < 4; k++)
				{
					entry.fileFormat[k] = buffer[j + 8 + k];
					entry.fileSize[k] = buffer[j + 20 + k];
					entry.startBlock[k] = buffer[j + 24 + k];
					entry.endBlock[k] = buffer[j + 28 + k];
				}
				fat.push_back(entry);
			}
		}
	}
}
// chuyen doi thong tin cua entry thanh du lieu co the doc duoc
void getInfoEntry(FAT fat, int& GETfileSize, int& GETstartBlock, int& GETtotalBlocks) {
	GETfileSize = reverseByte(fat.fileSize, 4);
	GETstartBlock = reverseByte(fat.startBlock, 4);
	GETtotalBlocks = reverseByte(fat.endBlock, 4);

}
// xuat danh sach file
void printFAT(vector<FAT> fat) {
	int GETfileSize;
	int GETstartBlock;
	int GETtotalBlocks;
	cout << "Name\t\t file size (byte)" << endl;
	for (auto& element : fat) {
		getInfoEntry(element, GETfileSize, GETstartBlock, GETtotalBlocks);
		cout << element.fileName << "\t\t" << GETfileSize << endl;
	}
	
}

//------ 4
// Tao mat khau file
void modifyFilePassword(vector<FAT>& fat) {
	char* temp = new char[8];
	cin.ignore();
	cout << "Nhap ten file: ";
	fgets(temp, 8, stdin);

	BYTE* t = new BYTE[8];
	for (int i = 0; i < 8; i++) {
		t[i] = temp[i];
	}
	FAT* entry = NULL;
	for (auto& element : fat) {
		if (isEqual(element.fileName, t)){
			char* temp = new char[8];
			cin.ignore();
			cout << "Nhap mat khau: ";
			fgets(temp, 8, stdin);

			for (int i = 0; i < 8; i++) {
				element.password[i] = temp[i];
			}
			break;
		}
	}
}
int findFile(vector<FAT> fat, char* temp) {
	BYTE* t = new BYTE[8];
	for (int i = 0; i < sizeof(temp); i++) {
		if(temp[i] == NULL)
			t[i] = BYTE(0);
		else
			t[i] = temp[i];
	}
	FAT* entry = NULL;
	int count = 0;
	for (auto& element : fat) {
		if(isEqual(element.fileName,t))
		{
			entry = &element;
			return count;
		}
		count++;
	}
	return 0;
}
// kiem tra file ton tai
bool isEqual(BYTE* x, BYTE* y) {
	for (int i = 0; i < 8; i++)
	{
		if (x[i] != y[i])
		{
			if (y[i] == BYTE("") || x[i] == BYTE("") || y[i] == BYTE(0) || x[i] == BYTE(0) || y[i] == NULL || x[i] == NULL)
				return true;
			return false;
		}
	}
	return true;
}

//------5
// Import 1 file vao volume
bool importfile(vector<FAT>& fat, LPCWSTR volumeName) {
	char* path = new char[50];
	cout << "nhap ten file can sao chep tren o dia (vd D:\\abc.txt): ";
	cin >> path;
	fstream f;
	f.open(path, ios::in);
	if (!f) {
		cerr << "Loi: Khong mo duoc file." << endl;
		return 0;
	}
	string data;
	string line;
	while (!f.eof()){
		getline(f, line);
		data += line;
	}
	string p = path;
	string fileFormat = p.substr(p.find(".")+1);
	p = p.erase(p.find("."));
	string fileName;
	cout << "Dat ten file: ";
	cin >> fileName;
	int t = 0, s=0,e=0;
	bool isOK;
	char* x = new char;
	char* y = new char;
	strcpy(x, fileName.c_str());
	strcpy(y, fileFormat.c_str());
	getInfoEntry(fat.back(), t, s, e);
	FAT entry = createEntry(x, y, NULL, data.length(), e + 1 , e+1 + data.length()/512);
	fat.push_back(entry);
	isOK = writeFAT(fat, volumeName);
	if (!isOK) {
		cout << "Khong the ghi vao bang FAT" << endl;
		return 0;
	}
	//18636
	for (int i = 0; i < data.length() ; i+=512){
		BYTE buffer[BPB];
		for (int j = 0; j < 512; j++) {
			if (i + j == data.length())
				break;
			buffer[j] = data[i+j];
		}
		writeBlock(e + 1 + i / 512, buffer, volumeName);
		cout << "Writing block: " << e + 1 + i / 512 << endl;
	}
}

//------ 6
// Export 1 file ra ngoai
bool exportfile(vector<FAT> fat, LPCWSTR volumeName) {
	char* path = new char[50];
	cout << "nhap ten file can sao chep tren MyS (vd 123.txt): ";
	cin >> path;
	string p = path;
	string fileFormat = p.substr(p.find(".") + 1);
	p = p.erase(p.find("."));
	string fileName = p;
	int t = 0, s = 0, e = 0;
	char* x = new char[8];
	char* y = new char[8];
	for (int i = 0; i < 8; i++) {
		if (fileName[i] == NULL)
			break;
		x[i] = fileName[i];
	}
	strcpy(y, fileFormat.c_str());
	int pos = findFile(fat,x);
	getInfoEntry(fat[pos], t, s, e);
	BYTE* t1 = new BYTE[8];
	char* temp = new char[8];
	if (fat[pos].password[0] != NULL && fat[pos].password[0] != BYTE(0)){
		do {
			cout << "Nhap mat khau: ";
			fgets(temp, 8, stdin);
			for (int i = 0; i < 8; i++) {
				t1[i] = temp[i];
			}
		} while (!isEqual(fat[pos].password, t1));
	}
	BYTE* buffer = new BYTE[BPB];
	int count = 0;
	string data1;
	int c = 0;
	for (int i = s; i <= e; i++){
		buffer = readBlock(i, volumeName);
		for (int j = 0; j < 512; j++){
			if (data1.length() == t)
				break;
			data1 += buffer[j];
		}
	}
	string newName;
	cout << "Dat ten file (vd D:\\aa1.txt): ";
	cin >> newName;
	fstream f;
	f.open(newName, ios::out);
	f.write(data1.data(), data1.length());
	f.close();
	return 1;
}

//-------7
// Xoa 1 file
void removeFile(vector<FAT>& fat, int pos) {
	BYTE* t1 = new BYTE[8];
	char* temp = new char[8];
	if(fat[pos].password[0] != NULL && fat[pos].password[0] != BYTE(0)){
		cin.ignore();
		while(1){
			cout << "Nhap mat khau: ";
			fgets(temp, 8, stdin);
			for (int i = 0; i < 8; i++) {
				t1[i] = temp[i];
			}
			if (isEqual(fat[pos].password, t1))
				break;
			cout << "Nhap lai!" << endl;
		}
	}
	fat.erase(fat.begin() + pos);
}

// Nhung ham phuc vu khac
// Tham khao tu https://github.com/ngohuudang/mid_term_OS/blob/main/volumeMyFS/Source.cpp
BYTE* decToHexaLE(unsigned int num, int n) {
	BYTE* byte = createBlankOffets(n);
	while (1) {
		unsigned int dec = num;
		int n = 0;
		while (dec > 256) {
			dec = dec >> 8;
			n++;
		}
		byte[n] = BYTE(dec);
		num = num - (dec << (8 * n));
		if (n == 0)
			break;
	}
	return byte;
}
// Tham khao tu https://github.com/ngohuudang/mid_term_OS/blob/main/volumeMyFS/Source.cpp
int reverseByte(BYTE* byte, unsigned int count)
{
	int result = 0;
	for (int i = count - 1; i >= 0; i--)
		result = (result << 8) | byte[i];
	return result;
}
// Tham khao tu https://github.com/ngohuudang/mid_term_OS/blob/main/volumeMyFS/Source.cpp
BYTE* createBlankOffets(int n) {
	BYTE* offsets = new BYTE[n];

	for (int i = 0; i < n; i++) {
		offsets[i] = BYTE(0);
	}
	return offsets;
}
// Tham khao tu https://github.com/ngohuudang/mid_term_OS/blob/main/volumeMyFS/Source.cpp
BYTE* readBlock(int block, LPCWSTR fileName) {
	DWORD bytesRead;
	HANDLE hFile;
	bool flag;
	BYTE* buffer = new BYTE[BPB];
	hFile = CreateFile(fileName,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	SetFilePointer(hFile, block*BPB, NULL, FILE_BEGIN);
	flag = ReadFile(hFile, buffer, BPB, &bytesRead, NULL);
	CloseHandle(hFile);
	if (flag)
		return buffer;
	return NULL;
}
// Tham khao tu https://github.com/ngohuudang/mid_term_OS/blob/main/volumeMyFS/Source.cpp
bool writeBlock(int block, BYTE* buffer, LPCWSTR fileName) {
	DWORD bytesRead;
	HANDLE hFile;
	bool flag;
	hFile = CreateFile(fileName,
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	SetFilePointer(hFile, block*BPB, NULL, FILE_BEGIN);
	flag = WriteFile(hFile, buffer, BPB, &bytesRead, NULL);
	CloseHandle(hFile);
	return flag;
}
