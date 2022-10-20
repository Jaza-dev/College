package logic;

import java.util.Vector;
import java.util.HashMap;

public class Game {
	private int year;
	private String season, city;
	private Vector<Sport> sports = new Vector<Sport>();
	private HashMap<String, Vector<Competitor>> countries = new HashMap<String, Vector<Competitor>>();
	
	public Game(int y, String s, String c){
		this.year = y; this.season = s; this.city = c;
	}
	public int getYear() { return this.year; }
	public String getSeason() { return this.season; }
	public String getCity() { return this.city; }
	public HashMap<String, Vector<Competitor>> getCountries() { return countries; }

	public Sport getSport(String name) {
		for (Sport sport : sports) {
			if (sport.getName().equals(name)) return sport;
		}
		Sport newSport = new Sport(name);
		sports.add(newSport);
		return newSport;
	}
	public boolean hasSport(String name) {
		for (Sport sport : sports) {
			if (sport.getName().equals(name)) return true;
		}
		return false;
	}
	public void addCompetitor(String country, Competitor competitor) {
		if( countries.get(country) == null )
			countries.put(country, new Vector<Competitor>());
		countries.get(country).add(competitor);
	}
}
