#include "Set.h"
#include "ctype.h"

class Word {
private:
	string word;
	const Set vowels{ "aeiou" };
	const Set sonats{ "lnr" };
	void addChar(char c);
	void addStr(string& s);
	bool comapreWords(Word& w1, Word& w2, int len1, int len2, int n1, int n2);
public:
	Word(string& s);
	Word(string&& s);
	int operator+();
	int operator~();
	int operator()(int n);
	bool operator^(Word& w);
	friend istream& operator>>(istream& is, Word& w);
	friend ostream& operator<<(ostream& os, Word& w);
};