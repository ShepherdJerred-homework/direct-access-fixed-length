#include "DataFile.h"

void DataFile::createFile(char *fileName, unsigned int sizeOfRecordsInBytes) {
    file.open(fileName);
    if (file.is_open()) {
        fStatus = fsSuccess;
    } else {
        fStatus = fsCloseFail;
    }
    // TODO create header
    file.close();
    recSize = sizeOfRecordsInBytes;
}

void DataFile::openFile(char *fileName) {
    file.open(fileName);
    // TODO read header
    if (file.is_open()) {
        fStatus = fsSuccess;
    } else {
        fStatus = fsOpenFail;
    }
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
    return recCount;
}

int DataFile::fileStatus() {
    return fStatus;
}
