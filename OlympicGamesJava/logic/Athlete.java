package logic;

import java.util.Vector;

public class Athlete extends Competitor {
	private int id, age;
	private double height, weight;
	private String name;
	private char gender;
	private Team team;
	private Vector<Athlete> v = new Vector<Athlete>();
	
	public Athlete(Event e, String medal, int id, String name, char gender, int age, double height, double weight, Team team) {
		super(e, medal);
		this.id = id; this.name = name; this.gender = gender; this.age = age; this.height = height; this.weight = weight; this.team = team;
		v.add(this);
	}
	public Athlete(Event e, String medal, int id, String name, char gender, int age, double hight, double weight) {
		super(e, medal);
		this.id = id; this.name = name; this.gender = gender; this.age = age; this.height = height; this.weight = weight;
		v.add(this);
	}
	
	public Athlete(Event e, String medal, int id, Team team){
		super(e, medal);
		this.id = id;
		this.team = team;
		v.add(this);
	}
	public Athlete(Event e, String medal, int id){
		super(e, medal);
		this.id = id;
		v.add(this);
	}

	public int getId() { return id; }
	public void setId(int id) { this.id = id; }
	public int getAge() { return age; }
	public void setAge(int age) { this.age = age; }
	public double getHeight() { return height; }
	public void setHeight(double height) { this.height = height; }
	public double getWeight() { return weight; }
	public void setWeight(double weight) { this.weight = weight; }
	public String getName() { return name; }
	public void setName(String name) { this.name = name; }
	public char getGender() { return gender; }
	public void setGender(char gender) { this.gender = gender; }
	
	@Override
	public Vector<Athlete> getVectorOfAthletes() { return v; }
	
}
