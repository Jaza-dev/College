#include "Word.h"

void Word::addChar(char c) {
	if (isalpha(c)) {
		word += c;
	}
}
void Word::addStr(string& s) {
	int i = 0;
	char c;
	while ((c = s[i]) != '\0') {
		addChar(c);
		i++;
	}
}

bool Word::comapreWords(Word& w1, Word& w2, int len1, int len2, int n1, int n2) {
	if (len1 - n1 != len2 - n2) return false;
	for (int i = n1, j = n2; i < len1; i++, j++) {
		if (tolower(w1.word[i]) != tolower(w2.word[j])) return false;
	}
	return true;
}

Word::Word(string& s) {
	addStr(s);
}

Word::Word(string&& s) {
	addStr(s);
}

int Word::operator+() {
	return size(word);
}

int Word::operator~() {
	int i, len = +*this, count = 0;
	if (len == 0) return 0;
	if (len == 1 && (sonats(word[0]) || vowels(word[0]))) return 1;
	else if (len == 1) return 0;
	//prvo proveravam prvi da li je nosilac sloga
	if (vowels(word[0])) count++;
	else if (sonats(word[0]) && !vowels(word[1])) count++;
	//proveravam poslednji da li je nosilac sloga
	if (vowels(word[len - 1])) count++;
	else if (sonats(word[len - 1]) && !vowels(word[len - 2])) count++;
	//proveravam ostale da li su nosioci sloga
	for (i = 1; i < len-1; i++) {
		if(vowels(word[i]) || (sonats(word[i]) && !vowels(word[i-1]) && !vowels(word[i+1]))) count++;
	}
	return count;
}

int Word::operator()(int n) {
	int len = +*this, count = ~*this, iter = -1, i;
	if (n >= 0 && n + 1 > count)return -1;
	if (n < 0 && n < -count) return -1;
	if (n < 0) n = count + n;
	//prvo proveravam prvi da li je nosilac sloga
	if (vowels(word[0])) iter++;
	else if (sonats(word[0]) && !vowels(word[1])) iter++;
	if (iter == n) return 0;
	for (i = 1; i < len - 1 && iter < n; i++) {
		if (vowels(word[i]) || (sonats(word[i]) && !vowels(word[i - 1]) && !vowels(word[i + 1]))) iter++;
	}
	--i;
	if (n == iter) return i;
	//proveravam poslednji da li je nosilac sloga
	if (vowels(word[len - 1])) iter++;
	else if (sonats(word[len - 1]) && !vowels(word[len - 2])) iter++;
	if (iter == n) return len - 1;
	else return -1;
}

bool Word::operator^(Word& w) {
	int count1 = ~*this, count2 = ~w;
	int len1 = +*this, len2 = +w;
	int n1, n2, i;
	if (count1 == 0 || count2 == 0) return false; //ako nemaju ni jedan slog false
	if (count1 == 1 || count2 == 1) { //ako imaju 1 slog prvo poredim da li su iste duzine, ako jesu poredim redom slova
		n1 = (*this)(0);
		n2 = w(0);
		return comapreWords(*this, w, len1, len2, n1, n2);
	}
	else { //ako imaju vise od 1 sloga uzimam poziciju predposlednjeg i sve slova do kraja proveravam
		n1 = (*this)(-2);
		n2 = w(-2);
		return comapreWords(*this, w, len1, len2, n1, n2);
	}
}
