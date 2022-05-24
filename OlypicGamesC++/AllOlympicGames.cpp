#include "AllOlympicGames.h"

AllOlympicGames* AllOlympicGames::allGames = nullptr;

Game* AllOlympicGames::getGame(int year, string& season, string& city) {
	//eather get game that is already created before, or make a new one and return
	for (Game* game : games)
	{
		if (game->getYear() == year && game->getSeason() == season) return game;
	}
	Game* newGame = new Game(year, season, city);
	games.push_back(newGame);
	return newGame;
}

void AllOlympicGames::parseAllAthletes(string filename) {
	//parses all data from athletes that are in file with events

	//first we gather all athletes in one vector
	vector<Athlete*> allAthletes;
	vector<Athlete*> v;
	for (Game* game : games) {
		for (pair<string, vector<Competitor*>> p : game->getCountries()) {
			for (Competitor* comp : p.second) {
				v = comp->getVectorOfAthletes();
				allAthletes.insert(allAthletes.end(), v.begin(), v.end());
			}
		}
	}

	//we sort vector, so we need on one passage to parse all athletes
	sort(allAthletes.begin(), allAthletes.end(), [](Athlete* ath1, Athlete* ath2) { return ath1->getId() < ath2->getId(); });

	ifstream file(filename);
	string textLine;
	Athlete* lst = nullptr;
	smatch result;
	for (Athlete* ath : allAthletes) {
		if (lst != nullptr && ath->getId() == lst->getId()) {
			//if there is same athlete multiple twice, we just put same data, and continue
			ath->setName(result.str(1));
			ath->setGender(result.str(2)[0]);
			ath->setAge(result.str(3) == "NA" ? 0 : stoi(result.str(3)));
			ath->setHight(result.str(4) == "NA" ? 0 : stod(result.str(4)));
			ath->setWeight(result.str(5) == "NA" ? 0 : stod(result.str(5)));
			continue;
		}
		regex rx(to_string(ath->getId()) + "!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)");
		while (getline(file, textLine)) {
			//passing all data in order and expecting to find athlete
			if (regex_match(textLine, result, rx)) {
				ath->setName(result.str(1));
				ath->setGender(result.str(2)[0]);
				ath->setAge(result.str(3) == "NA" ? 0 : stoi(result.str(3)));
				ath->setHight(result.str(4) == "NA" ? 0 : stod(result.str(4)));
				ath->setWeight(result.str(5) == "NA" ? 0 : stod(result.str(5)));
				lst = ath;
				break;
			}
		}
	}
	cout << "\tATHLETES LOADED" << endl
		<< "-------------------------------" << endl;
	/*for (Athlete* ath : allAthletes) {
		cout << ath->getId() << ". " << ath->getName() << " " << ath->getAge() << " " << ath->getHight() << " " << ath->getWeight() << endl;
	}*/
}

AllOlympicGames::~AllOlympicGames() {
	for (Game* game : games) {
		delete game;
	}
}

void AllOlympicGames::parse(string filename, int y) {
	//parses data from file, possibly for given year
	ifstream file(filename);
	string textLine;
	string year = y == -1 ? "([0-9]{4})" : "(" + to_string(y) + ")"; //eather no specific year so we search all, or its sepcific one
	regex rx(year + " ([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([a-zA-Z]*)?");
	string season, city, sportName, disciplin, type, country, competitor, medal;
	smatch result;
	while (getline(file, textLine)) {
		if (regex_match(textLine, result, rx)) {
			season = result.str(2);
			city = result.str(3);

			sportName = result.str(4);
			disciplin = result.str(5);
			type = result.str(6);

			country = result.str(7);
			competitor = result.str(8);
			medal = result.str(9);

			//getting all needed data to create, or fill game
			Game* game = getGame(stoi(result.str(1)), season, city); //year //if there is no game with same date, we create new one
			Sport* sport = game->getSport(sportName); //if there is no same sport on game yet we create it
			Event* even = sport->getEvent(disciplin, type, sport); //if there is no added event for sport we add it

			string id;
			Athlete* athlete = nullptr;
			if (type == "Team") {
				//if competitor is team, we create it, reading athlete one by one
				Team* team = new Team(even, medal);
				competitor.erase(0, 2);
				string delimiter = "', '";
				size_t pos = 0;
				
				while ((pos = competitor.find(delimiter)) != string::npos) {
					id = competitor.substr(0, pos);
					athlete = new Athlete(even, medal, stoi(id), team);
					team->addAthlete(athlete);
					competitor.erase(0, pos + delimiter.length());
				}
				delimiter = "']";
				pos = competitor.find(delimiter);
				id = competitor.substr(0, pos);
				athlete = new Athlete(even, medal, stoi(id), team);
				team->addAthlete(athlete);

				game->addCompetitor(country, team);
			}
			else {
				//if its individual, we create athlete and add it for that country
				athlete = new Athlete(even, medal, stoi(competitor));

				game->addCompetitor(country, athlete);
			}
		}
	}
	cout << "\tEVENTS LOADED" << endl
		<< "-------------------------------" << endl;
	parseAllAthletes("C:\\Users\\jazar\\Downloads\\13S112POOP_PZ1_2122_prilog\\athletes.txt");
}

int AllOlympicGames::countOfAllAthletes(string& sport, string& country, string& year, string& type, string& medal) {
	//counts number of athlets filterd
	vector<Athlete*> allAthletes;
	int count = 0;
	for (Game* game : games) {
		if (sport != "") { //filter basted on sport
			if (!game->hasSport(sport)) continue;
		}
		if (year != "") { //filter based on year
			if (game->getYear() != stoi(year)) continue;
		}
		
		//going through all countries-competitors to finde right ones
		for (pair<string, vector<Competitor*>> p : game->getCountries()) {
			if (country != "" && p.first != country) continue; //filter based on country
			for (Competitor* comp : p.second) {
				if (sport != "" && comp->getEvent()->getSport()->getName() != sport) continue; //filter based on sport
				if (type != "" && comp->getEvent()->getType() != type) continue; //filter based on type of event
				if (medal != "" && comp->getMedal() != medal) continue; //filter based on medal
				count += comp->getVectorOfAthletes().size();
			}
		}
	}
	return count;
}

int AllOlympicGames::countOfAllDisciplins(string& sport, string& country, string& year, string& type, string& medal) {
	//counts number of disciplins filterd
	set<string> allDisciplins; //using set in order not to repeat same disciplin twice

	for (Game* game : games) {
		if (sport != "") { //skracenje posla ako olimpijada uopste nije imala taj sport
			if (!game->hasSport(sport)) continue;
		}
		if (year != "") { //filter na osnovu godine
			if (game->getYear() != stoi(year)) continue;
		}

		//going through all countries-competitors to finde right ones
		for (pair<string, vector<Competitor*>> p : game->getCountries()) {
			if (country != "" && p.first != country) continue;  //filter based on country
			for (Competitor* comp : p.second) {
				if (sport != "" && comp->getEvent()->getSport()->getName() != sport) continue;  //filter based on sport
				if (type != "" && comp->getEvent()->getType() != type) continue; //filter based on type of event
				if (medal != "" && comp->getMedal() != medal) continue; //filter based on medal
				vector<Athlete*> v = comp->getVectorOfAthletes();
				for (Athlete* ath : v) {
					allDisciplins.insert(ath->getEvent()->getDisciplin());
				}
			}
		}
	}
	return allDisciplins.size();
}

double AllOlympicGames::averageHight(string& sport, string& country, string& year, string& type, string& medal) {
	//calculates average hight of all players filterd
	double hight = 0;
	int countOfAthletes = 0;
	for (Game* game : games) {
		if (sport != "") { //skracenje posla ako olimpijada uopste nije imala taj sport
			if (!game->hasSport(sport)) continue;
		}
		if (year != "") { //filter na osnovu godine
			if (game->getYear() != stoi(year)) continue;
		}
		for (pair<string, vector<Competitor*>> p : game->getCountries()) {
			if (country != "" && p.first != country) continue; //filter na osnovu drzave
			for (Competitor* comp : p.second) {
				if (sport != "" && comp->getEvent()->getSport()->getName() != sport) continue; //filter na osnovu sporta
				if (type != "" && comp->getEvent()->getType() != type) continue; //filter na osnovu tipa dogadjaja
				if (medal != "" && comp->getMedal() != medal) continue; //filter na osnovu medalje
				vector<Athlete*> v = comp->getVectorOfAthletes();
				for (Athlete* ath : v) {
					if (ath->getHight() != 0) {
						hight += ath->getHight();
						++countOfAthletes;
					}
				}
			}
		}
	}
	return hight/countOfAthletes;
}

double AllOlympicGames::averageWeight(string& sport, string& country, string& year, string& type, string& medal) {
	//calculates average weight of all filterd athletes
	double weight = 0;
	int countOfAthletes = 0;
	for (Game* game : games) {
		if (sport != "") { //skracenje posla ako olimpijada uopste nije imala taj sport
			if (!game->hasSport(sport)) continue;
		}
		if (year != "") { //filter na osnovu godine
			if (game->getYear() != stoi(year)) continue;
		}
		for (pair<string, vector<Competitor*>> p : game->getCountries()) {
			if (country != "" && p.first != country) continue; //filter na osnovu drzave
			for (Competitor* comp : p.second) {
				if (sport != "" && comp->getEvent()->getSport()->getName() != sport) continue; //filter na osnovu sporta
				if (type != "" && comp->getEvent()->getType() != type) continue; //filter na osnovu tipa dogadjaja
				if (medal != "" && comp->getMedal() != medal) continue; //filter na osnovu medalje
				vector<Athlete*> v = comp->getVectorOfAthletes();
				for (Athlete* ath : v) {
					if (ath->getHight() != 0) {
						weight += ath->getWeight();
						++countOfAthletes;
					}
				}
			}
		}
	}
	return weight / countOfAthletes;
}

int AllOlympicGames::numberOfSports(string& country) {
	//number of sports in witch given country won atleast one medal
	vector<Athlete*> allAthletesForCountry;
	set<string> allDifferentSports;
	for (Game* game : games) {
		for (Competitor* comp : game->getCountries()[country]) {
			if (comp->getMedal() != "NO MEDAL")
				//inserting athletes that won medal for country
				allAthletesForCountry.insert(allAthletesForCountry.end(), comp->getVectorOfAthletes().begin(), comp->getVectorOfAthletes().end());
		}
	}
	for (Athlete* ath : allAthletesForCountry) {
		allDifferentSports.insert(ath->getEvent()->getSport()->getName());
	}
	return allDifferentSports.size();
}

string* AllOlympicGames::threeBestCountries(string& year, string& season) {
	//three countries with best result

	//structure that hold countryName and count of each type of medal
	struct singleCountry {
		string cname;
		int countOfMedals[3] = { 0, 0, 0 };
		singleCountry(string name) :cname(name) {}
		void incGold() { ++countOfMedals[0]; }
		void incSilver() { ++countOfMedals[1]; }
		void incBronze() { ++countOfMedals[2]; }
	};
	//map<string, int[3]> leaderBoard; //svaka drzava ima tri polja [0]-gold, [1]-silver, [2]-bronze

	vector<singleCountry*> leaderboard;  //place we sort based on count of medals
	singleCountry* sc = nullptr;
	for (Game* game : games) {
		if (game->getYear() != stoi(year) || game->getSeason() != season) continue; //skip country that doesn't fulfill condition

		for (pair<string, vector<Competitor*>> p : game->getCountries()) {

			sc = new singleCountry(p.first);

			for (Competitor* comp : p.second) {

				for (Athlete* ath : comp->getVectorOfAthletes()) {
					if (ath->getMedal() == "Gold") sc->incGold();
					else if (ath->getMedal() == "Silver") sc->incSilver();
					else if (ath->getMedal() == "Bronze") sc->incBronze();
				}
			}
			leaderboard.push_back(sc);
		}
		break; //only one olympic game can fulfill condition, so we can break if we come here
	}
	if (leaderboard.size() < 3)return nullptr;
	sort(leaderboard.begin(), leaderboard.end(), [](singleCountry* sc1, singleCountry* sc2) {
		if (sc1->countOfMedals[0] != sc2->countOfMedals[0]) return sc1->countOfMedals[0] > sc2->countOfMedals[0];
		else if (sc1->countOfMedals[1] != sc2->countOfMedals[1]) return sc1->countOfMedals[1] > sc2->countOfMedals[1];
		else return sc1->countOfMedals[2] > sc2->countOfMedals[2];
		});

	/*for (singleCountry* sc : leaderboard) {
		cout << sc->cname << " : " << sc->countOfMedals[0] << ", " << sc->countOfMedals[1] << ", " << sc->countOfMedals[2] << endl;
	}*/ //print leaderbord

	return new string[]{ leaderboard[0]->cname, leaderboard[1]->cname, leaderboard[2]->cname };
}

set<string> AllOlympicGames::countriesThatWereTheBestOnce() {
	//all countries that were once the best
	set<string> bestCountries;
	for (Game* game : games) {
		string year = to_string(game->getYear()), season = game->getSeason();
		bestCountries.insert(threeBestCountries(year, season)[0]);
	}
	return bestCountries;
}

set<Athlete*> AllOlympicGames::allAthletesParticipatedOnPairOfGames(pair<Game*, Game*> pairOfGames) {
	map<int, int[2]> m; //id of athlete, [number of different games, last year we inc]
	set<Athlete*> athletes;
	for (Game* game : games) {
		if ((game->getYear() == pairOfGames.first->getYear() && game->getSeason() == pairOfGames.first->getSeason())
			|| (game->getYear() == pairOfGames.second->getYear() && game->getSeason() == pairOfGames.second->getSeason())) {

			for (pair<string, vector<Competitor*>> p : game->getCountries()) {

				for (Competitor* comp : p.second) {

					for (Athlete* ath : comp->getVectorOfAthletes()) {

						//we inc first spot if year is any diferent, we set year that is different
						if (m[ath->getId()][1] != game->getYear()) m[ath->getId()][0]++;
						if(m[ath->getId()][1] == 0) m[ath->getId()][1] = game->getYear();
						if (m[ath->getId()][0] == 2)athletes.insert(ath);
					}
				}


			}

		}
	}
	return athletes;
}

set<string> AllOlympicGames::olympicCities() {
	set<string> allCities;
	for (Game* game : games) {
		allCities.insert(game->getCity());
	}
	return allCities;
}

vector<Team*> AllOlympicGames::getAllTeams(string& country, string& year, string& season) {
	vector<Team*> allAthletes;
	for (Game* game : games) {
		if (game->getYear() != stoi(year) || game->getSeason() != season) continue;
		vector<Competitor*> competitors = game->getCountries()[country];
		for (Competitor* comp : competitors) {
			if (comp->getVectorOfAthletes().size() > 1) allAthletes.push_back((Team*)comp);
		}
	}
	sort(allAthletes.begin(), allAthletes.end(), [](Team* team1, Team* team2) {
		if (team1->getSize() != team2->getSize()) return team1->getSize() > team2->getSize();
		else return team1->getEvent()->getDisciplin() > team2->getEvent()->getDisciplin();
		});
	return allAthletes;
}

vector<Athlete*> AllOlympicGames::tenYoungestAthletesThatWonMedal() {
	map<int, int> m;
	vector<Athlete*> athletes;
	for (Game* game : games) {

		for (pair<string, vector<Competitor*>> p : game->getCountries()) {

			for (Competitor* comp : p.second) {

				for (Athlete* ath : comp->getVectorOfAthletes()) {
					if (m[ath->getId()] == -1) continue;
					if (ath->getMedal() != "NO MEDAL") {
						m[ath->getId()] = ath->getAge();
						//if ath is not already in we can add him
						if ((athletes.size() < 10 || athletes[9]->getAge() > ath->getAge()) && ath->getAge() > 0 && 
							find_if(athletes.begin(), athletes.end(), [ath](Athlete* a) {return a->getName() == ath->getName(); }) == athletes.end()) {
							if(athletes.size() == 10)
								athletes.pop_back();//taking out oldest
							athletes.push_back(ath); //adding him
							//keeping vector of 10 youngest athletes sorted all time
							sort(athletes.begin(), athletes.end (), [](Athlete* ath1, Athlete* ath2) {return ath1->getAge() < ath2->getAge(); });
						}
							
					}
					else m[ath->getId()] = -1;
				}
			}

		}
		
	}
	return athletes;
}

vector<pair<string, Athlete*>> AllOlympicGames::getPairsWithMedalInIndividualAndTeam() {

	map<int, int[2] > m; //id_athlete, data (medal in individual, in team)
	vector<pair<string, Athlete*>> v;
	for (Game* game : games) {
		for (pair<string, vector<Competitor*>> p : game->getCountries()) {

			for (Competitor* comp : p.second) {
				if (comp->getMedal() == "NO MEDAL") continue;

				vector<Athlete*> athletes = comp->getVectorOfAthletes();
				for (Athlete* ath : athletes) {

					if (athletes.size() == 1) {
						++m[ath->getId()][0];

						if (m[ath->getId()][0] == 1 && m[ath->getId()][1] > 0) {
							v.push_back({ p.first, ath });
						}

					}
					else {
						++m[ath->getId()][1];

						if (m[ath->getId()][0] > 0 && m[ath->getId()][1] == 1) {
							v.push_back({ p.first, ath });
						}

					}
				}
			}
		}
	}

	return v;
}
