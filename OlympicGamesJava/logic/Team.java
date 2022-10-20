package logic;

import java.util.Vector;

public class Team extends Competitor {
	private Vector<Athlete> athletes = new Vector<Athlete>();
	
	public Team(Event e, String medal) {
		super(e, medal);
	}
	
	public void addAthlete(Athlete athlete) {
		athletes.add(athlete);
	}
	
	public int getSize() { return athletes.size(); }
	
	@Override
	public Vector<Athlete> getVectorOfAthletes() { return athletes; }
}
