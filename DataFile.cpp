#include <iostream>
#include "DataFile.h"

using std::ios;
using std::cout;
using std::endl;

void DataFile::createFile(char *fileName, unsigned int sizeOfRecordsInBytes) {
    file.open(fileName, ios::out | ios::binary);
    file.close();
    file.open(fileName, ios::in | ios::out | ios::binary);
    if (!file.fail()) {
        fStatus = fsSuccess;
        cout << "File created" << endl;
    } else {
        fStatus = fsCreateFail;
        cout << "Error creating file" << endl;
    }
    header.recordCount = 0;
    header.recordSize = sizeOfRecordsInBytes;
    writeHeader();
    file.close();
}

void DataFile::openFile(char *fileName) {
    file.open(fileName);
    readHeader();
    if (file.is_open()) {
        fStatus = fsSuccess;
        cout << "File opened" << endl;
    } else {
        fStatus = fsOpenFail;
        cout << "Error opening file" << endl;
    }
    readHeader();
}

void DataFile::closeFile() {
    writeHeader();
    file.close();
    // TODO make this an actual condition
    if (true) {
        fStatus = fsSuccess;
    } else {
        fStatus = fsCloseFail;
    }
}

void DataFile::putRecord(long recordNumber, const void *dataToWriteToFile) {

    cout << "W REC: " << recordNumber << endl;
    cout << "W DATA: " << &dataToWriteToFile << endl;

    if (0 <= recordNumber && recordNumber <= header.recordCount) {
        long location = recordStart + (recordNumber * header.recordSize);
        file.seekp(location);
        file.write((char *) &dataToWriteToFile, header.recordSize);
        fStatus = fsSuccess;
    } else {
        fStatus = fsPutFail;
    }
}

void DataFile::getRecord(long recordNumber, const void *locationToWriteInto) {
    if (0 <= recordNumber && recordNumber <= header.recordCount) {
        long location = recordStart + (recordNumber * header.recordSize);
        file.seekg(location);
        file.read((char *) &locationToWriteInto, header.recordSize);
        fStatus = fsSuccess;
    } else {
        fStatus = fsGetFail;
    }

    cout << "R REC: " << recordNumber << endl;
    cout << "R DATA: " << &locationToWriteInto << endl;

}

void DataFile::updateRecordCount(int newRecordCount) {
    header.recordCount = header.recordCount + newRecordCount;
}

int DataFile::recordCount() {
    return header.recordCount;
}

int DataFile::fileStatus() {
    return fStatus;
}

void DataFile::writeHeader() {
    file.seekp(ios::beg);
    file.write((char *) &header, sizeof header);
}

void DataFile::readHeader() {
    unsigned char buffer[sizeof header];

    file.seekg(ios::beg);
    file.read((char *) &buffer, sizeof header);

    FileHeader *fileHeader = (FileHeader *) buffer;
    header = *fileHeader;
}
