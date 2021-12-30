#include "Student.h"

int Student::searchExam(string& exam) {
	for (int i = 0; i < exams.size(); i++) {
		if (exams[i] == exam) return i;
	}
	return -1;
}

void Student::split(string& student, char delimiter, vector<string>& v) {
	int i = 0, len = student.size();
	if (len == 0) return;
	string temp;
	for (; i < len+1; i++) {
		if (student[i] == delimiter || student[i] == '\0') {
			v.push_back(temp);
			temp = "";
			continue;
		}
		temp += student[i];
	}
}

Student::Student(string index, string name, string surname): index(index), name(name), surname(surname) { }

Student::Student(string student) {
	vector<string> v; split(student, ',', v);
	vector<string> n; split(v[1], ' ', n);
	vector<string> ex; split(v[2], ' ', ex);
	index = v[0];
	name = n[0];
	surname = n[1];
	for (int i = 0; i < ex.size(); i++) {
		this->AddExam(ex[i]);
	}
}

Student::Student(const Student& student) {
	index = student.index;
	name = student.name;
	surname = student.surname;
	exams = student.exams;
}

string& Student::getIndex() {
	return index;
}

string& Student::getName() {
	return name;
}

string& Student::getSurname() {
	return surname;
}

bool& Student::DELETED() {
	return deleted;
}

void Student::setDELETED() {
	deleted = true;
}

void Student::AddExam(string exam) { exams.push_back(exam); }

void Student::RemoveExam(string exam) {
	int i = searchExam(exam);
	if (i != -1) exams.erase(exams.begin() + i);
	else cout << "Ispit se ne nalazi u listi" << endl;
}

ostream& operator<<(ostream& os, const Student& student) {
	os << student.index << " " << student.name << " " << student.surname;
	for (int i = 0; i < student.exams.size(); i++) {
		os << ", " << student.exams[i];
	}
	return os;
}
void Student::printIndex() { cout << index; }