#include "Set.h"
#include "Word.h"
istream& operator>>(istream& is, Word& w) {
	string temp;
	w.word = "";
	is >> temp;
	w.addStr(temp);
	return is;
}
ostream& operator<<(ostream& os, Word& w) {
	return os << w.word;
}
int main() {
	//a e i o u | l n r
	Word w1("fryla");
	Word w2("prula");
	Word w3("Fiskalni");
	Word w4("Milicioner");
	Word w5("Dirka");
	cout << ~w1 << endl;
	cout << ~w2 << endl;
	cout << ~w3 << endl;
	cout << "Pozicija: " << w4(-5) << endl;
	cout << ~w5 << endl;
	cout << (w1^w2) << endl;
	cout << "---------------------" << endl;
	cin >> w1;
	cout << w1;
}