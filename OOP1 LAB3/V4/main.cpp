#include "includes.h"
#include "Player.h"
#include "Team.h"
#include "PrivilegedTeam.h"
#include "Match.h"
#include "Pair.h"

int main() {
	try {
		Player p1("Pera", 1000);
		Player p2("Ronaldo", 2500);
		Player p3("Zika");
		Player p4("Messi", 3000);
		Team* team1 = new Team("Tim1", 13);
		Team* team2 = new PrivilegedTeam("Tim2", 12, 1000);
		team1->addPlayer(0, &p1);
		team1->addPlayer(1, &p2);
		team2->addPlayer(0, &p3);
		team2->addPlayer(1, &p4);
		//cout << par;
		/*PrivilegedTeam t("ZZ", 12, 1000);
		t.addPlayer(0, &p1);
		t.addPlayer(1, &p2);*/
		Match m(team1, team2);
		cout << m << endl;
		m.playMatch();
		cout << m << endl;
		/*cout << *m.getPointPair() << endl;*/
		//cout << m2;
		return 0;
	}
	catch (ELowValueOfPlayer err) {
		cout << err;
	}
	catch (EMatchNotPlayed err) {
		cout << err;
	}
}