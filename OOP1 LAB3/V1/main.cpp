#include "includes.h"
#include "List.h"
#include "User.h"
#include "Email.h"
#include "TextEmail.h"
#include "Timestamp.h"

int main() {
	try {
		User* A = new User("Zika", "zika@gmail.com");
		User* B = new User("Pera", "pera@gmail.com");
		User* G = new User("Mika", "mika@gmail.com");
		User* F = new User("Nika", "nika@gmail.com");
		/*cout << A.getEmailAddress() << endl;
		cout << B.getName() << endl;
		cout << A << endl << B << endl;
		Timestamp ts(1, 1, 1, 0, 0);
		cout << ts;*/
		Email* mail1 = new Email(A, B, "Naslov");
		Email* mail2 = new Email(A, B, "Naslov2");
		/*cout << *mail1 << endl;
		cout << *mail2 << endl;*/
		TextEmail* mail3 = new TextEmail(G, F, "Poruka");
		mail3->setText("Pera peric je Pera Peric");
		TextEmail mail4(A, B, "Naslov3");
		mail4 = *mail3;
		cout << mail4;
		List<Email*> mailovi;
		mailovi.add(mail1);
		mailovi.add(mail2);
		mailovi.add(mail3);
		mailovi.add(&mail4);

		for (mailovi.setToHead(); mailovi.checkCurr() ; mailovi.setNext()) {
			cout << *mailovi.getCurrValue() << endl;
		}

		List<Email*> mailovi2 = mailovi;
		for (mailovi2.setToHead(); mailovi2.checkCurr(); mailovi2.setNext()) {
			cout << *mailovi2.getCurrValue() << endl;
		}

	}
	catch (ENoCurrElement err) {
		cout << err;
	}
	catch (EAlrdySentMessage err) {
		cout << err;
	}
	
	return 0;
}