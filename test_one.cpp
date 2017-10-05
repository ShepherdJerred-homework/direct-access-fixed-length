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

void addRecords(DataFile& s) {
    char response;
    do {
        cout << "enter a record (y/n): ";
        cin >> response;
        cin.get();

        if (response == 'y') {
            student studentRec;
            cout << "Name: ";
            cin.getline(studentRec.name, 20);

            cout << "GPA: ";
            cin >> studentRec.gpa;
            cin.get();

            cout << "Classification (4=sr, 3=jr, 2=so, 1=fr): ";
            cin >> studentRec.classification;
            cin.get();

            s.putRecord(s.recordCount(), &studentRec);
            if (s.fileStatus() == fsPutFail) {
                cerr << "error writing record...program exiting" << endl;
                exit(2);
            }
            s.updateRecordCount(1);
        }
    } while (response == 'y');
}

void printRecords(DataFile& s) {
    for (int i = 0; i < s.recordCount(); i++) {
        student studentRec;
        s.getRecord(i, &studentRec);
        if (s.fileStatus() == fsGetFail) {
            cerr << "program could not get a record...program exiting" << endl;
            exit(3);
        } else {
            cout << "RECORD #: " << i << "  "
                 << "NAME: " << studentRec.name << "  "
                 << "GPA: " << studentRec.gpa << "  "
                 << "CLASSIFICATION: " << studentRec.classification
                 << endl;
        }
    }
    cout << "Total of " << s.recordCount() << " records" << endl << endl;
}

void main() {
    DataFile students;
    char fileName[80];

    cout << "Enter file to open: ";
    cin.getline(fileName, 80);

    //Open the file and read in information
    students.openFile(fileName);

    //Did the open fail?
    if (students.fileStatus() == fsOpenFail) {
        cout << "File does not exist, create it? (y/n): ";
        char response;
        cin >> response;
        cin.get();
        if (response == 'y') {
            //Create an empty "dataFile" with correct structure
            students.createFile(fileName, sizeof student);
            if (students.fileStatus() == fsCreateFail) {
                cerr << "file could not be created...program exiting" << endl;
                exit(1);
            }
        } else {
            cout << "program exiting" << endl;
            exit(0);
        }
    }

    addRecords(students);
    printRecords(students);

    students.closeFile();
    if (students.fileStatus() == fsSuccess)
        cout << "All data saved on file" << endl;

    cin.get();
}
