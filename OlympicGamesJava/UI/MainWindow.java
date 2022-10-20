package UI;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dialog.ModalityType;
import java.awt.FlowLayout;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.event.ItemEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.HashMap;
import java.util.Map;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;

import logic.AllOlympicGames;
import logic.EWrongOption;

public class MainWindow extends JFrame{
	private String sport, year, type, medal, optionStr;
	private int option;
	
	private void populateWindow() {
		new ParseDialog(this);
		
		
		JPanel centralPanel = new JPanel(new FlowLayout());
		JLabel metrixLabel = new JLabel("Odaberite metriku koju zelite da se prikaze");
		JComboBox<String> metrix = new JComboBox<String>(new String[]{"Broj ucesnika na dogadjajima", "Broj disciplina na dogadjajima",
				"Prosecnu visinu", "Prosecnu tezinu"}) ;
		centralPanel.add(metrixLabel);
		centralPanel.add(metrix);
		
		JPanel filterPanel = new JPanel(new GridLayout(0,2, 5, 5));
		JLabel filterLabel = new JLabel("Na osnovu cega zelite da radite filtriranje podatak: ");
		JCheckBox fSportCB = new JCheckBox("Sporta");
		JCheckBox fYearCB = new JCheckBox("Godine");
		JCheckBox fTypeCB = new JCheckBox("Tipa");
		JCheckBox fMedalCB = new JCheckBox("Medalje");
		filterPanel.add(fSportCB);
		JTextField fSportTF = new JTextField(10);
		fSportTF.setEnabled(false);
		filterPanel.add(fSportTF);
		filterPanel.add(fYearCB);
		JTextField fYearTF = new JTextField(10);
		fYearTF.setEnabled(false);
		filterPanel.add(fYearTF);
		filterPanel.add(fTypeCB);
		JTextField fTypeTF = new JTextField(10);
		fTypeTF.setEnabled(false);
		filterPanel.add(fTypeTF);
		filterPanel.add(fMedalCB);
		JTextField fMedalTF = new JTextField(10);
		fMedalTF.setEnabled(false);
		filterPanel.add(fMedalTF);
		
		centralPanel.add(filterPanel);
		
		fSportCB.addItemListener((ie)->{
			if(ie.getStateChange() == ItemEvent.SELECTED) {
				fSportTF.setEnabled(true);
			}else fSportTF.setEnabled(false);
		});
		fYearCB.addItemListener((ie)->{
			if(ie.getStateChange() == ItemEvent.SELECTED) {
				fYearTF.setEnabled(true);
			}else fYearTF.setEnabled(false);
		});
		fTypeCB.addItemListener((ie)->{
			if(ie.getStateChange() == ItemEvent.SELECTED) {
				fTypeTF.setEnabled(true);
			}else fTypeTF.setEnabled(false);
		});
		fMedalCB.addItemListener((ie)->{
			if(ie.getStateChange() == ItemEvent.SELECTED) {
				fMedalTF.setEnabled(true);
			}else fMedalTF.setEnabled(false);
		});
		
		JPanel typeOfGraphPanel = new JPanel(new GridLayout(0,1,1,1));
		JRadioButton circleGraphRB = new JRadioButton("Kruzni grafikon", true);
		JRadioButton XYGraphRB = new JRadioButton("XY grafikon");
		circleGraphRB.setSelected(true);
		XYGraphRB.setEnabled(false);
		ButtonGroup graphChoiceGroup = new ButtonGroup();
		graphChoiceGroup.add(circleGraphRB);
		graphChoiceGroup.add(XYGraphRB);
		typeOfGraphPanel.add(circleGraphRB);
		typeOfGraphPanel.add(XYGraphRB);
		centralPanel.add(typeOfGraphPanel);
		
		JButton buttonShow = new JButton("Prikazi grafikon");
		centralPanel.add(buttonShow);
		
		JPanel yearRangePanel = new JPanel(new GridLayout(2, 0, 4, 4));
		
		JLabel startYearLabel = new JLabel("Od: ");
		yearRangePanel.add(startYearLabel);
		JTextField startYearTF = new JTextField(10);
		startYearTF.setText("1900");
		yearRangePanel.add(startYearTF);
		
		JLabel endYearLabel = new JLabel("Do: ");
		yearRangePanel.add(endYearLabel);
		JTextField endYearTF = new JTextField(10);
		endYearTF.setText("2020");
		yearRangePanel.add(endYearTF);
		yearRangePanel.setVisible(false);
		centralPanel.add(yearRangePanel);
		
		add(centralPanel, BorderLayout.CENTER);
		
		buttonShow.addActionListener((ae)->{
			
			int startYear, endYear;
			
			optionStr = metrix.getItemAt(metrix.getSelectedIndex());
			if(optionStr.equals("Broj ucesnika na dogadjajima")) option = 1;
			else if(optionStr.equals("Broj disciplina na dogadjajima")) option = 2;
			else if(optionStr.equals("Prosecnu visinu")) option = 3;
			else option = 4;
			
			if(fSportCB.isSelected())
				sport = fSportTF.getText();
			else sport = "";
			if(fYearCB.isSelected())
				year = fYearTF.getText();
			else year = "";
			if(fTypeCB.isSelected())
				type = fTypeTF.getText();
			else type = "";
			if(fMedalCB.isSelected())
				medal = fMedalTF.getText().toUpperCase();
			else medal = "";
			
			try {
				if(circleGraphRB.isSelected() && option == 1) {
					new GraphPanel(new CircleGraph(AllOlympicGames.getAllOlympicGames().countOfAllAthletes(sport, year, type, medal)));
				}else {
					
					startYear = Integer.parseInt(startYearTF.getText());
					endYear = Integer.parseInt(endYearTF.getText());
					
					switch (option)
					{
					case 2:
						new GraphPanel(new XYGraph(AllOlympicGames.getAllOlympicGames().countOfAllDisciplins(sport, year, type, medal, startYear, endYear), option));
						break;
					case 3:
						new GraphPanel(new XYGraph(AllOlympicGames.getAllOlympicGames().averageHight(sport, year, type, medal, startYear, endYear), option));
						break;
					case 4:
						new GraphPanel(new XYGraph(AllOlympicGames.getAllOlympicGames().averageWeight(sport, year, type, medal, startYear, endYear), option));
						break;
					}
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
			
		});

		metrix.addActionListener((ae)->{
			if(metrix.getItemAt(metrix.getSelectedIndex()) == "Broj ucesnika na dogadjajima") {
				circleGraphRB.setSelected(true);
				circleGraphRB.setEnabled(true);
				XYGraphRB.setEnabled(false);
				yearRangePanel.setVisible(false);
				setBounds(getX(), getY(), 300, 270);
			}else {
				XYGraphRB.setSelected(true);
				circleGraphRB.setEnabled(false);
				XYGraphRB.setEnabled(true);
				yearRangePanel.setVisible(true);
				setBounds(getX(), getY(), 300, 320);
			}
		});
	}
	
	public MainWindow() {
		
		setTitle("Olimpijske igre");
		setBounds(200, 150, 300, 275);
		setLayout(new BorderLayout());
		populateWindow();
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				dispose();
			}
		});
		setVisible(true);
	}
	
	public static void main(String[] args) {
		new MainWindow();
	}
}
