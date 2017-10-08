//This program tests the dataFile class which implements the reading and writing of fixed
//length records using direct access.

#include <iostream>
#include "DataFile.h"

using namespace std;

struct student {
    char name[20];
    float gpa;
    int classification;
};

void addRecords(DataFile &s) {
    student s1;
    strcpy_s(s1.name, "Jerred");
    s1.gpa = 3.0;
    s1.classification = 2;

    s.putRecord(s.recordCount(), &s1);

    if (s.fileStatus() == fsPutFail) {
        cerr << "Error writing record" << endl;
        exit(2);
    }
    s.updateRecordCount(1);

    student s2;
    strcpy_s(s2.name, "Adam");
    s2.gpa = 4.0;
    s2.classification = 3;

    s.putRecord(s.recordCount(), &s2);
    if (s.fileStatus() == fsPutFail) {
        cerr << "Error writing record" << endl;
        exit(2);
    }
    s.updateRecordCount(1);
}

void printRecords(DataFile &s) {
    cout << endl << endl;
    for (int i = 0; i < s.recordCount(); i++) {
        student studentRec;
        s.getRecord(i, &studentRec);
        if (s.fileStatus() == fsGetFail) {
            cerr << "program could not get a record...program exiting" << endl;
            exit(3);
        } else {
            cout << "R #: " << i << endl
                 << "N: " << studentRec.name << endl
                 << "G: " << studentRec.gpa << endl
                 << "C: " << studentRec.classification << endl << endl << endl;
        }
    }
    cout << "Total of " << s.recordCount() << " records" << endl << endl;
}

void main() {
    DataFile students;
    char fileName[80] = "test.bin";

    cout << "OPENING FILE " << fileName << endl;

    //Open the file and read in information
    students.openFile(fileName);

    //Did the open fail?
    if (students.fileStatus() == fsOpenFail) {
        cout << "File does not exist, creating" << endl;
        students.createFile(fileName, sizeof student);
        if (students.fileStatus() == fsCreateFail) {
            cerr << "Error creating file" << endl;
            exit(1);
        }
    } else {
        cout << "Error opening file" << endl;
        exit(0);
    }

    addRecords(students);
    printRecords(students);

    students.closeFile();
    if (students.fileStatus() == fsSuccess) {
        cout << "Data saved to file" << endl;
    }

    system("pause");
}
