package UI;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

public class CircleGraph extends Canvas{
	
	private HashMap<String, Integer> map;
	private Vector<Map.Entry<String, Integer>> topTen = new Vector<Map.Entry<String, Integer>>();
	private int count;
	private int others;
	
	private void sumAll() {
		int count = 0;
		
		for(Map.Entry<String, Integer> p : map.entrySet()) {
			count += p.getValue();
			topTen.add(p);
		}
		this.count = count;
		topTen.sort((c1,c2)->{
			return c2.getValue() - c1.getValue();
		});
		
		int others = 0;
		for(int i = 9; i < topTen.size(); i++) {
			others += topTen.get(i).getValue();
		}
		this.others = others;
	}
	
	public CircleGraph(HashMap<String, Integer> map) {
		this.map = map;
		sumAll();
	}
	
	@Override
	public void paint(Graphics g) {
		if(count == 0) {
			g.drawString("Rezultat je nula drzava", 150, 50);
			return;
		}
		setBackground(Color.WHITE);
		Color prevColor = g.getColor();
		
		int startAngle = 0, arcAngle = 0;
		double curValue = 0.0;
		
		int legendY = 400;
		int legendX = 50;
		
		for(int i = 0 ; i < 9 && i < topTen.size(); i++) {
			startAngle = (int)(curValue * 360 / count);
			arcAngle = (int) (topTen.get(i).getValue() * 360 / count);

			if(i == 0) g.setColor(new Color(255,228,196));
			else if(i == 1) g.setColor(Color.MAGENTA);
			else if(i==2) g.setColor(Color.pink);
			else if(i==3)g.setColor(Color.yellow);
			else if(i==4)g.setColor(Color.lightGray);
			else if(i==5)g.setColor(new Color(34, 77, 113));
			else if(i==6)g.setColor(Color.red);
			else if(i==7)g.setColor(Color.green);
			else g.setColor(Color.orange);
			
			g.fillArc(150, 50, 300, 300, startAngle, arcAngle);
			
			g.fillRect(legendX, legendY , 30, 20);
			g.setColor(Color.black);
			g.drawString(topTen.get(i).getKey(), legendX + 40, legendY + 15);
			curValue += topTen.get(i).getValue();
			
			legendY += 40;
			if((i + 1) % 4 == 0) {
				legendX += 200;
				legendY = 400;
			}
		}
		if(others > 0) {
			startAngle = (int)(curValue * 360 / count);
			arcAngle = (int) (others * 360 / count);
			g.setColor(Color.blue);
			g.fillArc(150, 50, 300, 300, startAngle, arcAngle);
			g.fillRect(legendX, legendY , 30, 20);
			g.setColor(Color.black);
			g.drawString("Other", legendX + 40, legendY + 15);
		}
		
		g.setColor(prevColor);
	}
}
