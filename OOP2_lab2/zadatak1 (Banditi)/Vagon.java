package banditi;

import java.util.ArrayList;
import java.util.List;

public class Vagon {
	private List<Bandit> listaBandita = new ArrayList<Bandit>();
	
	public void dodajBandita(Bandit bandit) {
		listaBandita.add(bandit);
	}
	
	public boolean sadrziBandita(Bandit bandit) {
		for (Bandit b : listaBandita) {
			if(b == bandit) return true;
		}
		return false;
	}
	
	public void ukloniBandita(Bandit bandit) {
		int i = 0;
		for (Bandit b : listaBandita) {
			if(b == bandit) {
				listaBandita.remove(i);
				break;
			}
			++i;
		}
	}
	
	public int dohvatiBrojBandita() {
		return listaBandita.size();
	}
	
	public Bandit dohvatiBandita(int pozicija) {
		int i = 0;
		for (Bandit b : listaBandita) {
			if(i == pozicija) {
				return b;
			}
			++i;
		}
		return null;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("[");
		short i = 0;
		for (Bandit b : listaBandita) {
			if(i > 0) {
				sb.append(",");
			}
			sb.append(b);
			i++;
		}
		sb.append("]");
		return sb.toString();
	}

	/*
	 * @Override public boolean equals(Object obj) { if (this == obj) return true;
	 * if (obj == null) return false; if (getClass() != obj.getClass()) return
	 * false; Vagon other = (Vagon) obj; return Objects.equals(listaBandita,
	 * other.listaBandita); }
	 */
	 
}
