/*
 * DAFL by Jerred Shepherd
 * This class provides a clean interface for storing a retrieving fixed data in a binary file
 */

#include <iostream>
#include "DataFile.h"

using std::ios;
using std::cout;
using std::endl;

/**
 * Create a file with header
 * @param fileName
 * @param sizeOfRecordsInBytes
 */
void DataFile::createFile(char *fileName, unsigned int sizeOfRecordsInBytes) {
    file.clear();
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
}

/**
 * Open a previously created file to read and write data
 * @param fileName
 */
void DataFile::openFile(char *fileName) {
    file.open(fileName);
    if (file.is_open()) {
        fStatus = fsSuccess;
        cout << "File opened" << endl;
    } else {
        fStatus = fsOpenFail;
        cout << "Error opening file" << endl;
    }
    readHeader();
}

/**
 * Close an open file
 */
void DataFile::closeFile() {
    writeHeader();
    file.flush();
    file.close();
    // TODO make this an actual condition
    if (true) {
        fStatus = fsSuccess;
    } else {
        fStatus = fsCloseFail;
    }
}


/**
 * Store a new record in the data file
 * @param recordNumber
 * @param dataToWriteToFile
 */
void DataFile::putRecord(long recordNumber, const void *dataToWriteToFile) {
    if (0 <= recordNumber && recordNumber <= header.recordCount) {
        long location = recordStart + (recordNumber * header.recordSize);
        file.seekp(location);
        file.write((char *) dataToWriteToFile, header.recordSize);
        fStatus = fsSuccess;
    } else {
        fStatus = fsPutFail;
    }
}

/**
 * Get a record from the data file
 * @param recordNumber
 * @param locationToWriteInto
 */
void DataFile::getRecord(long recordNumber, const void *locationToWriteInto) {
    if (0 <= recordNumber && recordNumber <= header.recordCount) {
        long location = recordStart + (recordNumber * header.recordSize);
        file.seekg(location);
        file.read((char *) locationToWriteInto, header.recordSize);
        fStatus = fsSuccess;
    } else {
        fStatus = fsGetFail;
    }
}

/**
 * Update the record count and write it to file
 * @param newRecordCount
 */
void DataFile::updateRecordCount(int newRecordCount) {
    header.recordCount = header.recordCount + newRecordCount;
    writeHeader();
}

int DataFile::recordCount() {
    return header.recordCount;
}

int DataFile::fileStatus() {
    return fStatus;
}

/**
 * Write the header struct to file
 */
void DataFile::writeHeader() {
    file.seekp(ios::beg);
    file.write((char *) &header, sizeof header);
}

/**
 * Read the file header into a struct
 */
void DataFile::readHeader() {
    unsigned char buffer[sizeof header];

    file.seekg(ios::beg);
    file.read((char *) &buffer, sizeof header);

    FileHeader *fileHeader = (FileHeader *) buffer;
    header = *fileHeader;
}
