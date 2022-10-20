package UI;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

public class XYGraph extends Canvas {
	
	private int variant;
	double sizeOfPointX = 0, sizeOfPointY = 0;
	private HashMap<Integer, Double> summerGames;
	private HashMap<Integer, Double> winterGames;
	private Vector<Vector<Integer>> dataSet = new Vector<Vector<Integer>>();
	private Vector<Vector<Integer>> yearDataSet = new Vector<Vector<Integer>>();
	
	private native double calculateSizeOfPointY(double Yoffset, int offsetValue);
	
	public XYGraph(Vector<HashMap<Integer, Double>> v, int variant) {
		this.variant = variant;
		this.summerGames = v.get(0);
		this.winterGames = v.get(1);
		
		System.out.println("Summer");
		for(Map.Entry<Integer, Double> p : summerGames.entrySet()) {
			System.out.println(p.getKey() + " - " + p.getValue());
		}
		System.out.println("Winter");
		for(Map.Entry<Integer, Double> p : winterGames.entrySet()) {
			System.out.println(p.getKey() + " - " + p.getValue());
		}
	}
	
	private void paintFrame(Graphics g) {
		g.setColor(Color.black);
		
		System.loadLibrary("Dll_XYGraph");
		
		yearDataSet.clear();
		dataSet.clear();
		//okvir
		g.drawRect(getX() + 40, getY() + 10,545, 350);
		
		//podeoci godine ( X - osa )
		int startYear = 1900, yearOffset = 20;
		int numberOfYears = 7;
		double Xoffset = getX() + 535 / numberOfYears, x = 40;
		this.sizeOfPointX = Xoffset / yearOffset;
		for(int i = 0; i < numberOfYears; i++, x += Xoffset, startYear += yearOffset) {
			g.drawLine((int)(x + Xoffset), getY() + 360, (int)(x + Xoffset), getY() + 365);
			g.drawString(startYear + "", (int)(x + Xoffset) - 15, getY() + 380);
			yearDataSet.add(new Vector<Integer>());
			yearDataSet.get(i).add(startYear);
			yearDataSet.get(i).add((int)(x+Xoffset));
		}
		
		//podeoci varijanti ( Y - osa )
		int startValue = 0, offsetValue = 0; 
		if(variant == 2) {
			startValue = 0; offsetValue = 50;
		}else if(variant == 3) {
			startValue = 160; offsetValue = 5;
		}else { startValue = 10; offsetValue = 15; }
		int numberOfDivisions = 7;
		double Yoffset = getY() + 350 / numberOfDivisions, y = 350 + 10;
		
		this.sizeOfPointY = calculateSizeOfPointY(Yoffset, offsetValue);
		//this.sizeOfPointY = Yoffset / offsetValue;
		
		for(int i = 0; i < numberOfDivisions; i++, y -= Yoffset) {
			g.drawLine( getX() + 40, (int)(y), getX() + 35, (int)(y));
			g.drawString((startValue + i * offsetValue) + "", getX() + 10, (int) y + 5);
			dataSet.add(new Vector<Integer>());
			dataSet.get(i).add(startValue + i * offsetValue);
			dataSet.get(i).add((int)y);
		}
	}
	
	private void paintDots(HashMap<Integer, Double> games, Graphics g, Color c) {
		Color prevColor = g.getColor();
		g.setColor(c);
		
		int x = 0, y = 0;
		for(Map.Entry<Integer, Double> p : games.entrySet()) {
			int year = p.getKey();
			double data = p.getValue();
			
			for(Vector<Integer> yearDouplet : yearDataSet) {
				x = yearDouplet.get(1);
				if(year <= yearDouplet.get(0)) {
					x -= (yearDouplet.get(0) - year) * sizeOfPointX;
					break;
				}
			}
			for(Vector<Integer> dataDouplet : dataSet) {
				y = dataDouplet.get(1);
				if(data <= dataDouplet.get(0)) {
					y += (dataDouplet.get(0) - data) * sizeOfPointY;
					break;
				}else y += (dataDouplet.get(0) - data) * sizeOfPointY;
			}
			g.fillOval(x, y, 6, 6);
		}
		
		
	}
	
	private void paintLegend(Graphics g) {
		Color prevColor = g.getColor();
		
		g.setColor(Color.red);
		g.fillRect(getX() + 20, getY() + 420, 15, 10);
		g.setColor(Color.black);
		g.drawString("- Summer Olympic Games Data", getX() + 40, getY() + 428);
		
		g.setColor(Color.blue);
		g.fillRect(getX() + 20, getY() + 440, 15, 10);
		g.setColor(Color.black);
		g.drawString("- Winter Olympic Games Data", getX() + 40, getY() + 448);
		
		g.setColor(prevColor);
	}
	
	private void paintData(Graphics g){
		Color prevColor = g.getColor();
		
		paintDots(summerGames, g, Color.red);
		paintDots(winterGames, g, Color.blue);
		paintLegend(g);
		
		g.setColor(prevColor);
	}
	
	@Override
	public void paint(Graphics g) {
		Color prevColor = g.getColor();
		
		paintFrame(g);
		
		paintData(g);
		
		g.setColor(prevColor);
	}
	
	
}
