package logic;

import java.util.Vector;

public class Sport {
	private String name;
	private Vector<Event> events = new Vector<Event>();
	
	public Sport(String name) {
		this.name = name;
	}
	
	public String getName() { return this.name; }

	public Event getEvent(String disciplin, String type, Sport sport) {
		for (Event e : events) {
			if (e.getDisciplin().equals(disciplin) && e.getType().equals(type)) return e;
		}
		Event newEvent = new Event(disciplin, type, sport);
		events.add(newEvent);
		return newEvent;
	}
}
