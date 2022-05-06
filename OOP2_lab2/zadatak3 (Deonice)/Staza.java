package skijanje;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

public class Staza {
	private List<Deonica> listaDeonica = new ArrayList<Deonica>();
	private String naziv;
	
	public Staza(String naziv) {
		this.naziv = naziv;
	}
	
	public void dodaj(Deonica deonica) {
		this.listaDeonica.add(deonica);
	}
	
	public int broj() {
		return this.listaDeonica.size();
	}
	
	public double duzina() {
		double ukupnaDuzina = 0;
		for (Deonica deonica : listaDeonica) {
			ukupnaDuzina += deonica.duzina();
		}
		return ukupnaDuzina;
	}
	
	public double nagib() {
		double maxNagib = 0;
		for (Deonica deonica : listaDeonica) {
			maxNagib = Math.max(maxNagib, deonica.nagib());
		}
		return maxNagib;
	}
	
	public char oznaka() throws GOznaka {
		//char prvaOznaka = ' ';
		char najbrojnijaOznaka = ' ';
		int maxPojavljivanja = 0;
		Set<Character> oznake = new HashSet<Character>();
		Hashtable<Character, Integer> tabela = new Hashtable<Character, Integer>();
		for (Deonica deonica : listaDeonica) {
			if(!tabela.containsKey(deonica.oznaka())) {
				tabela.put(deonica.oznaka(), 0);
			}
			oznake.add(deonica.oznaka());
			tabela.replace(deonica.oznaka(), tabela.get(deonica.oznaka()) + 1);
		}
		for (char oznaka : oznake) {
			//za slucaj da treba da se vrati prva dodata deonica u listi
			/*if(maxPojavljivanja == 0) prvaOznaka = oznaka;
			if(maxPojavljivanja == tabela.get(oznaka)) return prvaOznaka;*/
			//else
			if(maxPojavljivanja < tabela.get(oznaka)){
				maxPojavljivanja = tabela.get(oznaka);
				najbrojnijaOznaka = oznaka;
			}
		}
		if(najbrojnijaOznaka == ' ') throw new GOznaka();
		return najbrojnijaOznaka;
	}
	
	public double brzina(double pocetnaBrzina) {
		double Vk = pocetnaBrzina;
		Iterator<Deonica> it = listaDeonica.iterator();
		while(it.hasNext()) {
			Vk = (it.next()).brzina(Vk);
		}
		return Vk;
	}
	
	public double vreme(double pocetnaBrzina) {
		double t = 0;
		double Vp = pocetnaBrzina;
		for (Deonica deonica : listaDeonica) {
			t += deonica.vreme(Vp);
			Vp = deonica.brzina(Vp);
		}
		return t;
	}

	@Override
	public String toString() {
		short flag = 0;
		StringBuilder sb = new StringBuilder();
		sb.append(naziv).append("|").append(broj()).append("|").append(duzina()).append("|").append(nagib()).append("\n").append("[");
		for (Deonica deonica : listaDeonica) {
			if(flag > 0) sb.append(",");
			sb.append(deonica);
			flag++;
		}
		sb.append("]");
		return sb.toString();
	}
	
	
}
