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
    // TODO read header
    if (file.is_open()) {
        fStatus = fsSuccess;
    } else {
        fStatus = fsOpenFail;
    }
    readHeader();
}

void DataFile::closeFile() {
    // TODO write file header?
    file.close();
    // TODO set status
}

void DataFile::putRecord(long recordNumber, const void *locationToReadFrom) {

}

void DataFile::getRecord(long recordNumber, const void *locationToWriteTo) {

}

void DataFile::updateRecordCount(int newRecordCount) {

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

    FileHeader * fileHeader = (FileHeader *) buffer;
    header = *fileHeader;
}
