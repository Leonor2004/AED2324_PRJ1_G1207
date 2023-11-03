#include "Student.h"
#include <algorithm>
#include <iostream>
#include "CsvAndVectors.h"

Student::Student() {
    this->studentCode = "";
    this->studentName = "";
}

Student::Student(string studentCode, string studentName) {
    this->studentCode = std::move(studentCode);
    this->studentName = std::move(studentName);
}

Student::Student(string studentCode, string studentName, vector<UC> ucs) : ucs(std::move(ucs)) {
    this->studentCode = std::move(studentCode);
    this->studentName = std::move(studentName);
}

string Student::getStudentCode() const {
    return this->studentCode;
}

string Student::getStudentName() const {
    return this->studentName;
}


vector<UC> Student::getUCs() const {
    return this->ucs;
}

//  O(log n) + O(n) where n is the number of students int the CSVInfo.StudentsVector
void Student::addUC(const UC &uc) {
    this->ucs.push_back(uc);
    CsvAndVectors CSVInfo;

    int idx = this->binarySearchCsvStudentVector(0, CSVInfo.StudentsVector.size());
    CSVInfo.StudentsVector[idx].getUCs().push_back(uc);
    CSVInfo.setFromStudentsVector();
}

void Student::removeUC(const UC &uc) {
    CsvAndVectors CSVInfo;

    auto it = find(this->ucs.begin(), this->ucs.end(), uc);
    this->ucs.erase(it);
    int idx = this->binarySearchCsvStudentVector(0, CSVInfo.StudentsVector.size());
    cout << idx << CSVInfo.StudentsVector[idx].getStudentName() << endl;

    for (int i = 0; i < CSVInfo.StudentsVector[idx].getUCs().size(); i++) {
        if (CSVInfo.StudentsVector[idx].getUCs()[i] == uc) {
            CSVInfo.StudentsVector[idx].getUCs().erase(CSVInfo.StudentsVector[idx].getUCs().begin() + i);
            CSVInfo.setFromStudentsVector();
            return;
        }
    }
}

int Student::binarySearchCsvStudentVector(unsigned long left, unsigned long right) {
    if (left > right) return -1; //not found

    CsvAndVectors CSVInfo;

    sort(CSVInfo.StudentsVector.begin(), CSVInfo.StudentsVector.end(), [](Student &A, Student &B) {
        return A.getStudentCode() < B.getStudentCode();
    });
    unsigned long mid = left + (right - left) / 2;
    if (CSVInfo.StudentsVector[mid].getStudentCode() == this->studentCode) {
        return mid; // Found the UC object at index mid
    }
    else if (CSVInfo.StudentsVector[mid].getStudentCode() > this->studentCode) {
        return binarySearchCsvStudentVector(left, mid - 1);
    }
    return binarySearchCsvStudentVector(mid + 1, right);
}

UC Student::changeUC(const UC &uc) {
    UC old_uc = this->findUc(uc.getUcCode());
    if (!(old_uc == UC())) {
        this->removeUC(old_uc);
        this->addUC(uc);
        return old_uc;
    }
    return UC();
}

UC Student::findUc(const string& UcCode) const{
    for (UC uc: this->ucs) {
        cout << uc.getUcCode() << endl;
        if (uc.getUcCode() == UcCode) {
            return uc;
        }
    }
    return UC();
}

bool Student::Enrolled(const string& UcCode) {
    for (UC uc: this->ucs) {
        if (uc.getUcCode() == UcCode) {
            return true;
        }
    }
    return false;
}

bool Student::operator<(const Student &s) const {
    return this->studentName < s.getStudentName();
}

bool Student::operator==(const Student &s) const {
    return this->studentCode == s.getStudentCode();
}

void Student::printUcAndClass() const {
    for (auto uc: ucs) {
        cout << uc.getUcCode() << " " << uc.getClassCode() << endl;
    }
}
