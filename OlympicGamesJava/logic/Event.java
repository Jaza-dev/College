package logic;

public class Event {
	private String disciplin, type;
	private Sport sport;
	
	public Event(String disciplin, String type, Sport sport){
		this.disciplin = disciplin; this.type = type; this.sport = sport;
	}

	public String getDisciplin() { return disciplin; }
	public String getType() { return type; }
	public Sport getSport() { return sport; }
}
