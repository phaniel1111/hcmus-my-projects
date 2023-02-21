#pragma once

#include<iostream>
#include<fstream>
#include <Windows.h>
#include< stdio.h >
#include <vector>
#include<string>
#define BPB 512
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
typedef unsigned char BYTE;

using namespace std;

struct superBlock { //32 byte
	BYTE bytePerBlock[2];
	BYTE superBlockSize[1];
	BYTE blocksInVolume[4];
	BYTE FATsize[4];
	BYTE password[8];
	BYTE unused[13];
};
struct FAT { //32 bytes
	BYTE fileName[8];
	BYTE fileFormat[4];
	BYTE password[8];
	BYTE fileSize[4];
	BYTE startBlock[4];
	BYTE endBlock[4];
	
};
struct dataBlocks {
	BYTE data[512];
};
void createBlankVolume(char volumeName[], int volumeSize);
superBlock createSupperBlock(int volumeSize);
bool isWriteSuperBlock(superBlock sb, LPCWSTR volumeName);
void getInfo(superBlock sb, int& GETbytePerBlock, int& GETsuperBlockSize, int& GETblocksInVolume, int& GETFATsize, char*& GETpw);
superBlock blockTosuperBlock(BYTE* block);

void modifyPassword(superBlock& sb);

bool isEmptyEntry(int index, BYTE* buffer);
bool removeFAT(vector<FAT> fat, LPCWSTR fileName);
FAT createEntry(char* fileName, char* fileFormat, char* password, int fileSize, int startBlock, int totalBlocks);
bool writeFAT(vector<FAT> fat, LPCWSTR fileName);
void readFAT(vector<FAT>& fat, LPCWSTR fileName);
void getInfoEntry(FAT fat, int& GETfileSize, int& GETstartBlock, int& GETtotalBlocks);

void modifyFilePassword(vector<FAT>& fat);
int findFile(vector<FAT> fat, char* temp);
bool isEqual(BYTE* x, BYTE* y);

void printFAT(vector<FAT> fat);

bool importfile(vector<FAT>& fat, LPCWSTR volumeName);

bool exportfile(vector<FAT> fat, LPCWSTR volumeName);

void removeFile(vector<FAT>& fat, int pos);

BYTE* decToHexaLE(unsigned int num, int n);
int reverseByte(BYTE* byte, unsigned int count);
BYTE* createBlankOffets(int n);

BYTE* readBlock(int block, LPCWSTR fileName);
bool writeBlock(int block, BYTE* buffer, LPCWSTR fileName);