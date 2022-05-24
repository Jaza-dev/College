#include "AllOlympicGames.h"
#include <windows.h>
#include "EWrongOption.h"


int main() {
	short option = 0;
	string sport, year, country, type, medal, season, *leaderboard;
	Game* game1 = nullptr, * game2 = nullptr;
	cout << "U kom rezimu zelite da se ucitavaju podaci?" << endl
		<< "1. Grupni rezim." << endl
		<< "2. Pojedinacni rezim." << endl
		<< "Rezim: ";
	try {
		cin >> option;
		cout << endl << "-------------------------------" << endl
			<< "\tLOADING DATA" << endl
			<< "-------------------------------" << endl;
		if (option == 1) { 
			//parsing data without specific year
			AllOlympicGames::getAllOlympicGames()->parse("C:\\Users\\jazar\\Downloads\\13S112POOP_PZ1_2122_prilog\\events.txt");
		}
		else if (option == 2) {
			//parsing data with specific year
			cout << "Unesite godinu za koju zelite da ucitate podatke: ";
			cin >> year;
			AllOlympicGames::getAllOlympicGames()->parse("C:\\Users\\jazar\\Downloads\\13S112POOP_PZ1_2122_prilog\\events.txt", stoi(year));
		}
		else {
			throw EWrongOption();
		}
		cout << "\tDATA LOADED" << endl;
		cout << "-------------------------------" << endl;
	}
	catch (EWrongOption e) {
		cout << "Uneli ste nepostojecu opciju za rezim rada programa." << endl;
		return -1;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	while (true) {
		cout << "1. Ispis" << endl
			<< "2. Odrediti broj razlicitih sportova u kojima je zadata drzava osvojila barem jednu medalju" << endl
			<< "3. Odrediti tri najbolje drzave po uspehu na zadatim Olimpijskim igrama" << endl
			<< "4. Odrediti drzave koje su barem jednom osvojile najbolji rezultat" << endl
			<< "5. Odreditit deset najmladjih ucesnika Olimpijskih igara koji su osvojili medalju na svom prvom ucescu" << endl
			<< "6. Odrediti sve parove drzava-sportista gde je sportista osvojio bar jednu medalju u pojedinacnoj i bar jednu u timskoj konkurenciji" << endl
			<< "7. Odrediti sve sportiste koji su ucestvovali na zadatom paru Olimpijskih igara" << endl
			<< "8. Odrediti sve timove koje zadata drzava ima na zadatim Olimpijskim igrama" << endl
			<< "9. Odrediti sve gradove u kojima su se Olimpijske igre odrzale bar jednom" << endl
			<< "0. Kraj rada" << endl
			<< "Opcija: ";
		cin >> option;
		try {
			switch (option)
			{
			case 0:
				cout << "Da li ste sigurni da zelite da ugasite program?" << endl
					<< "1. DA" << endl
					<< "2. NE" << endl;
				cin >> option;
				if (option == 1) {
					delete AllOlympicGames::getAllOlympicGames();
					exit(0);
				}
			case 1:
				sport = "", year = "", country = "", type = "", medal = "";
				cout << "Koju metriku zelite?" << endl;
				cout << "1. Broj ucesnika na svim dogadjajima na Olimpijskim igrama" << endl;
				cout << "2. Ukupan broj disciplina na Olimpijskim igrama" << endl;
				cout << "3. Prosecnu visinu svih sportista" << endl;
				cout << "4. Prosecnu tezinu svih sportista" << endl;
				cout << "Metrika: ";
				cin >> option;

				int option2;
				while (true) {
					short flag = 0;
					cout << "Na osnovu cega zelite da radite filtriranje ispisa podataka?" << endl;
					cout << "1. Na osnovu zadatog sporta" << endl;
					cout << "2. Na osnovu drzave" << endl;
					cout << "3. Na osnovu godine odrzavanja" << endl;
					cout << "4. Na osnovu tipa dogadjaja (individualni ili timski)" << endl;
					cout << "5. Na osnovu osvojene medalje (zlatna, srebrna, bronzana ili bez medalje" << endl;
					cout << "6. Kraj unosa" << endl;
					cout << "Filter: ";
					cin >> option2;
					switch (option2)
					{
					case 1:
						cout << "Sport: ";
						cin.ignore();
						getline(cin, sport);
						break;
					case 2:
						cout << "Drzava: ";
						cin.ignore();
						getline(cin, country);
						break;
					case 3:
						cout << "Godina: ";
						cin >> year;
						break;
					case 4:
						cout << "Tip: ";
						cin >> type;
						break;
					case 5:
						cout << "Medalja (Gold, Silver, Bronze, NO MEDAL): ";
						cin >> medal;
						break;
					case 6:
						flag = 1;
						break;
					default:
						throw EWrongOption();
						break;
					}
					if (flag) break;
				}

				switch (option)
				{
				case 1:
					cout << "Broj ucesnika: " << AllOlympicGames::getAllOlympicGames()->countOfAllAthletes(sport, country, year, type, medal) << endl;
					break;
				case 2:
					cout << "Broj razlicitih disciplina: " << AllOlympicGames::getAllOlympicGames()->countOfAllDisciplins(sport, country, year, type, medal) << endl;
					break;
				case 3:
					cout << "Prosecna visina: " << AllOlympicGames::getAllOlympicGames()->averageHight(sport, country, year, type, medal) << endl;
					break;
				case 4:
					cout << "Prosecna tezina: " << AllOlympicGames::getAllOlympicGames()->averageWeight(sport, country, year, type, medal) << endl;
					break;
				default:
					throw EWrongOption();
					break;
				}
				break;
			case 2:
				cout << "Drzava: ";
				cin.ignore();
				getline(cin, country);
				cout << "Broj sportova je: " << AllOlympicGames::getAllOlympicGames()->numberOfSports(country) << endl;
				break;
			case 3:
				cout << "Godina odrzavanja: ";
				cin >> year;
				cout << "Godisnje doba: ";
				cin >> season;
				leaderboard = AllOlympicGames::getAllOlympicGames()->threeBestCountries(year, season);
				if (!leaderboard) { cout << "Ne postoje tri najbolje zemlje sa zadatim podacima." << endl; break; }
				cout << "Najbolje tri zemlje:" << endl;
				for (int i = 0; i < 3; i++) {
					cout << (i + 1) << "." << leaderboard[i] << endl;
				}
				break;
			case 4:
				cout << "Drzave koje su bar jednom bile najbolje:" << endl;
				for (string c : AllOlympicGames::getAllOlympicGames()->countriesThatWereTheBestOnce()) {
					cout << c << endl;
				}
				break;
			case 5:
				for (Athlete* ath : AllOlympicGames::getAllOlympicGames()->tenYoungestAthletesThatWonMedal()) {
					cout << ath->getId() << ". " << ath->getName() << ", " << ath->getAge() << endl;
				}
				break;
			case 6:
				for (pair<string, Athlete*> p : AllOlympicGames::getAllOlympicGames()->getPairsWithMedalInIndividualAndTeam()) {
					cout << p.first << ", " << *p.second << endl;
				}
				break;
			case 7:
				cout << "Unesite godine prvih olimpijskih igara: ";
				cin >> year;
				cout << "Unesite sezonu prvih olimpijskih igara: ";
				cin >> season;
				game1 = new Game(stoi(year), season, "");
				cout << "Unesite godine drugih olimpijskih igra: ";
				cin >> year;
				cout << "Unesite sezonu drugih olimpijskih igara: ";
				cin >> season;
				game2 = new Game(stoi(year), season, "");
				cout << "Sportisti koji su ucestovavli na zadatim Olimpijskim igrama: " << endl;
				for (Athlete* ath : AllOlympicGames::getAllOlympicGames()->allAthletesParticipatedOnPairOfGames({ game1,game2 })) {
					cout << ath->getId() << ". " << ath->getName() << endl;
				}
				break;
			case 8:
				cout << "Drzava: ";
				cin.ignore();
				getline(cin, country);
				cout << "Godina odrzavanja igara: ";
				cin >> year;
				cout << "Sezona igara: ";
				cin >> season;
				for (Team* team : AllOlympicGames::getAllOlympicGames()->getAllTeams(country, year, season)) {
					cout << team;
				}
				break;
			case 9:
				for (string city : AllOlympicGames::getAllOlympicGames()->olympicCities()) {
					cout << city << endl;
				}
				break;
			default:
				throw EWrongOption();
				break;
			}
		}
		catch (EWrongOption e) {
			cout << "Uneli ste nepostojecu opciju, pokusajte ponovo." << endl;
		}
	}
	
	return 0;
}