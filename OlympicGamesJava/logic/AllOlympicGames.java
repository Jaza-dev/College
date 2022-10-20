package logic;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Vector;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Stream;


import java.util.Map;
import java.util.Scanner;

public class AllOlympicGames {
	private static AllOlympicGames allGames = null;
	private Vector<Game> games = new Vector<Game>();

	private AllOlympicGames() {}
	private Game getGame(int year, String season, String city) {
		if(games != null) {
			for (Game game : games)
			{
				if (game.getYear() == year && game.getSeason().equals(season)) return game;
			}
		}
		Game newGame = new Game(year, season, city);
		games.add(newGame);
		return newGame;
	}
	private void parseAllAthletes(String filename) {
		Vector<Athlete> allAthletes = new Vector<Athlete>();
		for (Game game : games) {
			for (Map.Entry<String, Vector<Competitor>> p: game.getCountries().entrySet()) {
				for (Competitor comp : p.getValue()) {
					allAthletes.addAll(comp.getVectorOfAthletes());
				}
			}
		}
		allAthletes.sort((ath1,ath2)->{
			return ath1.getId() - ath2.getId();
		});
		try {
			File file = new File(filename);
			BufferedReader reader = new BufferedReader(new FileReader(file));
			Stream<String> stream = reader.lines();
			Iterator<String> itLine = stream.iterator();
			Iterator<Athlete> itAth = allAthletes.iterator();
			Athlete lst = null;
			String regex;
			Pattern p;
			Matcher m = null;
			while(itAth.hasNext()){
				Athlete ath = itAth.next();
				if (lst != null && ath.getId() == lst.getId()) {
					//if there is same athlete multiple twice, we just put same data, and continue
					ath.setName(m.group(1));
					ath.setGender(m.group(2).charAt(0));
					ath.setAge(m.group(3).equals("NA")? 0 : Integer.parseInt(m.group(3)));
					ath.setHeight(m.group(4).equals("NA") ? 0 : Double.parseDouble(m.group(4)));
					ath.setWeight(m.group(5).equals("NA") ? 0 : Double.parseDouble(m.group(5)));
					continue;
				}
				regex = ath.getId() + "!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)";
				p = Pattern.compile(regex);
				
				while(itLine.hasNext()) {
					String str = itLine.next();
					m = p.matcher(str);
					if (m.matches()) {
						ath.setName(m.group(1));
						ath.setGender(m.group(2).charAt(0));
						ath.setAge(m.group(3).equals("NA") ? 0 : Integer.parseInt(m.group(3)));
						ath.setHeight(m.group(4).equals("NA") ? 0 : Double.parseDouble(m.group(4)));
						ath.setWeight(m.group(5).equals("NA") ? 0 : Double.parseDouble(m.group(5)));
						lst = ath;
						break;
					}
				}
			}
		} catch (FileNotFoundException e) {
			System.out.println("Datoteka nije pronadjena");
		}
		System.out.println("\tATHLETES LOADED");
		System.out.println("-------------------------------");
	}
	
	public static AllOlympicGames getAllOlympicGames() {
		if (allGames == null) {
			allGames = new AllOlympicGames();
		}
		return allGames;
	}

	public void parse(String filename, int y) {
		System.out.println("\n" + "-------------------------------");
		System.out.println("\tLOADING DATA");
		System.out.println("-------------------------------");
		try {
			String year = y == -1 ? "([0-9]{4})" : "(" + y + ")";
			File file = new File(filename);
			BufferedReader reader = new BufferedReader(new FileReader(file));
			Stream<String> stream = reader.lines();
			stream.forEach(str->{
				String regex = year + " ([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([a-zA-Z]*)?";
				Pattern p = Pattern.compile(regex);
				Matcher m = p.matcher(str);
				if(m.matches()) {
					String season = m.group(2);
					String city = m.group(3);
		
					String sportName = m.group(4);
					String disciplin = m.group(5);
					String type = m.group(6);
		
					String country = m.group(7);
					String competitor = m.group(8);
					String medal = m.group(9);
					
					Game game = getGame(Integer.parseInt(m.group(1)), season, city);
					Sport sport = game.getSport(sportName); 
					Event even = sport.getEvent(disciplin, type, sport);

					String id;
					Athlete athlete = null;
					if (type.equals("Team")) {
						Team team = new Team(even, medal);
						competitor = competitor.substring(2, competitor.length());
						//competitor.erase(0, 2);
						String delimiter = "', '";
						int pos = 0;
						
						while ((pos = competitor.indexOf(delimiter)) != -1) {
							id = competitor.substring(0, pos);
							athlete = new Athlete(even, medal, Integer.parseInt(id), team);
							team.addAthlete(athlete);
							competitor = competitor.substring(pos + delimiter.length(), competitor.length());
						}
						delimiter = "']";
						pos = competitor.indexOf(delimiter);
						id = competitor.substring(0, pos);
						athlete = new Athlete(even, medal, Integer.parseInt(id), team);
						team.addAthlete(athlete);
		
						game.addCompetitor(country, team);
						
					}
					else {
						athlete = new Athlete(even, medal, Integer.parseInt(competitor));
						game.addCompetitor(country, athlete);
					}
				}
			});
		} catch (FileNotFoundException e) {
			System.out.println("Datoteka nije pronadjena");
		}
		System.out.println("\tEVENTS LOADED");
		System.out.println("-------------------------------");
	
		parseAllAthletes("D:\\Java Projects\\test11\\src\\athletes.txt");
		System.out.println("\tDATA LOADED" );
		System.out.println("-------------------------------");
	}
	public void parse(String filename) {
		System.out.println("\n" + "-------------------------------");
		System.out.println("\tLOADING DATA");
		System.out.println("-------------------------------");
		int y = -1;
		try {
			String year = y == -1 ? "([0-9]{4})" : "(" + y + ")";
			File file = new File(filename);
			BufferedReader reader = new BufferedReader(new FileReader(file));
			Stream<String> stream = reader.lines();
			stream.forEach(str->{
				String regex = year + " ([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([a-zA-Z]*)?";
				Pattern p = Pattern.compile(regex);
				Matcher m = p.matcher(str);
				if(m.matches()) {
					String season = m.group(2);
					String city = m.group(3);
		
					String sportName = m.group(4);
					String disciplin = m.group(5);
					String type = m.group(6);
		
					String country = m.group(7);
					String competitor = m.group(8);
					String medal = m.group(9);
					
					Game game = getGame(Integer.parseInt(m.group(1)), season, city);
					Sport sport = game.getSport(sportName); 
					Event even = sport.getEvent(disciplin, type, sport);

					String id;
					Athlete athlete = null;
					if (type.equals("Team")) {
						Team team = new Team(even, medal);
						competitor = competitor.substring(2, competitor.length());
						//competitor.erase(0, 2);
						String delimiter = "', '";
						int pos = 0;
						
						while ((pos = competitor.indexOf(delimiter)) != -1) {
							id = competitor.substring(0, pos);
							athlete = new Athlete(even, medal, Integer.parseInt(id), team);
							team.addAthlete(athlete);
							competitor = competitor.substring(pos + delimiter.length(), competitor.length());
						}
						delimiter = "']";
						pos = competitor.indexOf(delimiter);
						id = competitor.substring(0, pos);
						athlete = new Athlete(even, medal, Integer.parseInt(id), team);
						team.addAthlete(athlete);
		
						game.addCompetitor(country, team);
					}
					else {
						athlete = new Athlete(even, medal, Integer.parseInt(competitor));
						game.addCompetitor(country, athlete);
					}
				}
			});
		} catch (FileNotFoundException e) {
			System.out.println("Datoteka nije pronadjena");
		}
		System.out.println("\tEVENTS LOADED");
		System.out.println("-------------------------------");
		parseAllAthletes("D:\\Java Projects\\test11\\src\\athletes.txt");
		System.out.println("\tDATA LOADED" );
		System.out.println("-------------------------------");
	}

	public HashMap<String, Integer> countOfAllAthletes(String sport, String year, String type, String medal) {
		HashMap<String, Integer> map = new HashMap<String, Integer>(); 
		int count = 0, tmp = 0;
		for (Game game : games) {
			if (!sport.equals("")) {
				if (!game.hasSport(sport)) continue;
			}
			if (!year.equals("")) {
				if (game.getYear() != Integer.parseInt(year)) continue;
			}
			for (Map.Entry<String, Vector<Competitor>> p : game.getCountries().entrySet()) {
				for (Competitor comp : p.getValue()) {
					if (!sport.equals("") && !comp.getEvent().getSport().getName().equals(sport)) continue;
					if (!type.equals("") && !comp.getEvent().getType().equals(type)) continue;
					if (!medal.equals("") && !comp.getMedal().equals(medal)) continue;
					tmp = comp.getVectorOfAthletes().size();
					if(map.get(p.getKey()) == null) map.put(p.getKey(), 0);
					map.put(p.getKey(), map.get(p.getKey()) + tmp);
					count += tmp;
				}
			}
		}
		return map;
	}
	public Vector<HashMap<Integer, Double>> countOfAllDisciplins(String sport, String year , String type, String medal, int startYear, int endYear) {
		
		Vector<HashMap<Integer, Double>> data = new Vector<HashMap<Integer, Double>>(); 
		HashMap<Integer, Double> summerGames = new HashMap<Integer, Double>();
		HashMap<Integer, Double> winterGames = new HashMap<Integer, Double>();
		Set<String> allDisciplins = new HashSet<String>();
		
		for (Game game : games) {
			
			if (!sport.equals("")) { 
				if (!game.hasSport(sport)) continue;
			}
			if(!year.equals(""))
				if (game.getYear() != Integer.parseInt(year)) continue;
			
			if (game.getYear() < startYear || game.getYear() > endYear) continue;

			for (Map.Entry<String, Vector<Competitor>> p : game.getCountries().entrySet()) {
				for (Competitor comp : p.getValue()) {
					if (!sport.equals("") && !comp.getEvent().getSport().getName().equals(sport)) continue;  
					if (!type.equals("") && !comp.getEvent().getType().equals(type)) continue; 
					if (!medal.equals("") && !comp.getMedal().equals(medal)) continue;
					allDisciplins.add(comp.getEvent().getDisciplin());
				}
			}
			if(game.getSeason().equals("Summer"))
				summerGames.put(game.getYear(), (double)allDisciplins.size());
			else
				winterGames.put(game.getYear(), (double)allDisciplins.size());
			allDisciplins.clear();
		}
		data.add(summerGames);
		data.add(winterGames);
		
		return data;
	}
	public Vector<HashMap<Integer, Double>> averageHight(String sport, String year, String type, String medal, int startYear, int endYear) {
		double hight = 0;
		int countOfAthletes = 0;
		
		Vector<HashMap<Integer, Double>> data = new Vector<HashMap<Integer, Double>>(); 
		HashMap<Integer, Double> summerGames = new HashMap<Integer, Double>();
		HashMap<Integer, Double> winterGames = new HashMap<Integer, Double>();
		
		for (Game game : games) {
			if (!sport.equals("")) {
				if (!game.hasSport(sport)) continue;
			}
			if (!year.equals("")) {
				if (game.getYear() != Integer.parseInt(year)) continue;
			}
			
			if (game.getYear() < startYear || game.getYear() > endYear) continue;
			
			for (Map.Entry<String, Vector<Competitor>> p : game.getCountries().entrySet()) {
				for (Competitor comp : p.getValue()) {
					if (!sport.equals("") && !comp.getEvent().getSport().getName().equals(sport)) continue;
					if (!type.equals("") && !comp.getEvent().getType().equals(type)) continue;
					if (!medal.equals("") && !comp.getMedal().equals(medal)) continue;
					Vector<Athlete> v = comp.getVectorOfAthletes();
					for (Athlete ath : v) {
						if (ath.getHeight() != 0) {
							hight += ath.getHeight();
							++countOfAthletes;
						}
					}
				}
			}
			if(game.getSeason().equals("Summer"))
				summerGames.put(game.getYear(), hight/countOfAthletes);
			else
				winterGames.put(game.getYear(), hight/countOfAthletes);
			hight = 0.0;
			countOfAthletes = 0;
		}
		
		data.add(summerGames);
		data.add(winterGames);
		return data;
	}
	public Vector<HashMap<Integer, Double>> averageWeight(String sport, String year, String type, String medal, int startYear, int endYear) { 
		double weight = 0;
		int countOfAthletes = 0;
		
		Vector<HashMap<Integer, Double>> data = new Vector<HashMap<Integer, Double>>(); 
		HashMap<Integer, Double> summerGames = new HashMap<Integer, Double>();
		HashMap<Integer, Double> winterGames = new HashMap<Integer, Double>();
		
		for (Game game : games) {
			if (!sport.equals("")) { 
				if (!game.hasSport(sport)) continue;
			}
			if (!year.equals("")) {
				if (game.getYear() != Integer.parseInt(year)) continue;
			}
			
			if (game.getYear() < startYear || game.getYear() > endYear) continue;
			
			for (Map.Entry<String, Vector<Competitor>> p : game.getCountries().entrySet()) {
				for (Competitor comp : p.getValue()) {
					if (!sport.equals("") && !comp.getEvent().getSport().getName().equals(sport)) continue;
					if (!type.equals("") && !comp.getEvent().getType().equals(type)) continue;
					if (!medal.equals("") && !comp.getMedal().equals(medal)) continue;
					Vector<Athlete> v = comp.getVectorOfAthletes();
					for (Athlete ath : v) {
						if (ath.getHeight() != 0) {
							weight += ath.getWeight();
							++countOfAthletes;
						}
					}
				}
			}
			
			if(game.getSeason().equals("Summer"))
				summerGames.put(game.getYear(), weight/countOfAthletes);
			else
				winterGames.put(game.getYear(), weight/countOfAthletes);
			weight = 0.0;
			countOfAthletes = 0;
			
		}
		data.add(summerGames);
		data.add(winterGames);
		return data;
	}
}
