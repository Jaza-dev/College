#include "TextEmail.h"

TextEmail* TextEmail::vCopy() {
    return new TextEmail(this->sender, this->receiver, this->title);
}

void TextEmail::print(ostream& os) const {
    Email::print(os);
    os << endl << this->text;
}

TextEmail::TextEmail(User* s, User* r, string t) : Email::Email(s, r, t){ }

TextEmail& TextEmail::setText(string t) {
    if (this->getState() == SENT) throw EAlrdySentMessage();
    this->text = t;
    return *this;
}

ostream& operator<<(ostream& os, const TextEmail& te) {
    te.print(os);
    return os;
}

