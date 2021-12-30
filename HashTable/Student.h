#pragma once
#include "includes.h"
class Student {
private:
	string index, name, surname;
	vector<string> exams;
	bool deleted = false;
	int searchExam(string& exam);
	void split(string& student, char delimiter, vector<string>& v);
public:
	Student(string index, string name, string surname);
	Student(string student);
	Student(const Student& student);
	string& getIndex();
	string& getName();
	string& getSurname();
	bool& DELETED();
	void setDELETED();
	void AddExam(string exam);
	void RemoveExam(string exam);
	friend ostream& operator<<(ostream& os, const Student& student);
	void printIndex();
	void clearExams() { exams.clear(); }
	void setExams(vector<string> exams) { this->exams = exams; }
	vector<string> getExams() { return exams; }
};

