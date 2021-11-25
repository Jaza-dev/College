#pragma once
#include "iostream"
#include "string"
using namespace std;

class Set {
private:
	string set;
public:
	Set(string& s);
	Set(string&& s);
	Set(const Set& s) = delete;
	Set& operator=(const Set& s) = delete;
	bool operator()(char c) const;
	Set& operator+=(char c);
};