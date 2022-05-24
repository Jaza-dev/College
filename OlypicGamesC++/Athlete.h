#pragma once
#include "includes.h"
#include "Competitor.h"

class Team;
class Event;

class Athlete : public Competitor {
private:
	int id, age;
	double hight, weight;
	string name;
	char gender;
	Team* team;
	vector<Athlete*> v = { this };
public:
	Athlete(Event* e, string& medal, int id, string name, char gender, int age, double hight, double weight, Team* team = nullptr) :
		Competitor(e, medal), id(id), name(name), gender(gender), age(age), hight(hight), weight(weight), team(team) {}
	Athlete(Event* e, string& medal, int id, Team* team = nullptr) : Competitor(e, medal), id(id) {}
	int getId() { return this->id; }
	string& getName() { return this->name; }
	double getHight() { return this->hight; }
	double getWeight() { return this->weight; }
	int getAge() { return this->age; }
	void setAge(int age) { this->age = age; }
	void setHight(double hight) { this->hight = hight; }
	void setWeight(double weight) { this->weight = weight; }
	void setName(string name) { this->name = name; }
	void setGender(char gender) { this->gender = gender; }
	vector<Athlete*>& getVectorOfAthletes() override;

	friend ostream& operator<< (ostream& os, const Athlete& ath);
};