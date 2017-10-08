#ifndef DIRECT_ACCESS_FIXED_LENGTH_DATAFILE_H
#define DIRECT_ACCESS_FIXED_LENGTH_DATAFILE_H

#include <fstream>

#define fsCreateFail 0
#define fsSuccess 1
#define fsGetFail 2
#define fsCloseFail 3
#define fsOpenFail 4
#define fsPutFail 5

using std::fstream;

struct FileHeader {
    int recordSize;
    int recordCount;
};

class DataFile {
private:
    fstream file;
    FileHeader header;
    int fStatus;
    int recordStart = sizeof header + 1;
    void writeHeader();
    void readHeader();
public:
    void createFile(char *fileName, unsigned int sizeOfRecordsInBytes);

    void openFile(char *fileName);

    void closeFile();

    void putRecord(long recordNumber, const void *dataToWriteToFile);

    void getRecord(long recordNumber, const void *locationToWriteInto);

    int recordCount();

    void updateRecordCount(int newRecordCount);

    int fileStatus();
};


#endif //DIRECT_ACCESS_FIXED_LENGTH_DATAFILE_H
