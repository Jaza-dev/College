package UI;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.Dialog.ModalityType;
import java.awt.event.ItemEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;

import logic.AllOlympicGames;

public class ParseDialog extends JDialog{
	private int regime = 0;
	
	private void populateWindow() {
		JLabel lab = new JLabel("Izaberite rezim rada");
		lab.setAlignmentX(JLabel.CENTER);
		lab.setFont(new Font("Verdana", Font.BOLD, 16));
		add(lab);
		JPanel radioPanel = new JPanel(new BorderLayout());
		JRadioButton single = new JRadioButton("Pojedinacni rezim");
		JRadioButton group = new JRadioButton("Grupni rezim", true);
		ButtonGroup regimeOfWork = new ButtonGroup();
		regimeOfWork.add(single); regimeOfWork.add(group);
		radioPanel.add(single, BorderLayout.NORTH);
		radioPanel.add(group, BorderLayout.SOUTH);
		add(radioPanel);
		
		JPanel inputPanel = new JPanel();
		inputPanel.add(new JLabel("Godina: "));
		JTextField yearText = new JTextField(15);
		yearText.setEnabled(false);
		inputPanel.add(yearText);
		add(inputPanel);
		
		group.addItemListener((ie)->{
			if(ie.getStateChange() == ItemEvent.SELECTED) {
				yearText.setEnabled(false);
			}
		});
		single.addItemListener((ie)->{
			if(ie.getStateChange() == ItemEvent.SELECTED) {
				yearText.setEnabled(true);
			}
		});
		
		JButton button = new JButton("Ucitaj");
		button.setFont(new Font("Arial", Font.BOLD, 26));
		button.setBackground(Color.GREEN);
		button.addActionListener((ae)->{
			if(single.isSelected()) regime = 2;
			else regime = 1;
			String year = yearText.getText();
			try {
				if (regime == 1) {
					AllOlympicGames.getAllOlympicGames().parse("D:\\Java Projects\\test11\\src\\events.txt");
				}
				else if (regime == 2) {
					AllOlympicGames.getAllOlympicGames().parse("D:\\Java Projects\\test11\\src\\events.txt", Integer.parseInt(year));
				}
			}catch (Exception e) {
				JDialog errorDialog = new JDialog(this);
				errorDialog.setTitle("Greska");
				errorDialog.setBounds(200,200,200,200);
				errorDialog.setModalityType(ModalityType.APPLICATION_MODAL);
				errorDialog.add(new JLabel(e.toString()));
				errorDialog.setResizable(false);
				errorDialog.setVisible(true);
			}
			
			dispose();
		});
		add(button);
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				dispose();
			}
		});
		
	}
	
	public ParseDialog(Frame owner) {
		super(owner, "Rezim rada" , true);
		setLayout(new GridLayout(4, 1, 5, 5));
		setBounds(340,200, 300, 300);
		setResizable(false);
		populateWindow();
		setVisible(true);
	}
}
