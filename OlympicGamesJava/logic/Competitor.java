package logic;

import java.util.Vector;

public abstract class Competitor {
	private enum Medal { GOLD, SILVER, BRONZE, NO_MEDAL };
	private Event event;
	private Medal medal = Medal.NO_MEDAL;
	
	public Competitor(Event e, String medal){
		event = e;
		if (medal.equals("Gold")) this.medal = Medal.GOLD;
		else if (medal.equals("Silver")) this.medal = Medal.SILVER;
		else if (medal.equals("Bronze")) this.medal = Medal.BRONZE;
		else this.medal = Medal.NO_MEDAL;
	}
	
	public Event getEvent() { return this.event; }
	
	public String getMedal() { 
		if (this.medal == Medal.GOLD) return "GOLD";
		else if (this.medal == Medal.SILVER) return "SILVER";
		else if (this.medal == Medal.BRONZE) return "BRONZE";
		else return "NO MEDAL";
	}
	
	public abstract Vector<Athlete> getVectorOfAthletes();
}
