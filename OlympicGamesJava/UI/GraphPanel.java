package UI;

import java.awt.Canvas;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;


import javax.swing.JFrame;
import javax.swing.JPanel;

public class GraphPanel extends JFrame{
	
	
	private Canvas canvas;
	
	
	private void populeWindow() {
		
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				dispose();
			}
		});
	}
	
	
	
	public GraphPanel(Canvas canvas) {
		
		this.canvas = canvas;
		add(canvas);
		
		setTitle("Grafik");
		setBounds(200,200,610,600);
		
		setResizable(false);
		
		populeWindow();
		
		setVisible(true);
	}
}
