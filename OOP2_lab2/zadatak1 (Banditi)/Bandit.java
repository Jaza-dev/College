package banditi;


public class Bandit {
	public static enum Tim { A, B };
	private Tim tim;
	private int brojZlatnika = 50;
	
	public Bandit (Tim tim) {
		this.tim = tim;
	}

	public Tim dohvatiTim() {
		return this.tim;
	}

	public int dohvatiBrojZlatnika() {
		return this.brojZlatnika;
	}
	
	public void promeniBrojZlatnika(int brojZlatnika) {
		this.brojZlatnika += brojZlatnika;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(this.dohvatiTim()).append(this.dohvatiBrojZlatnika());
		return sb.toString();
	}

	/*
	 * @Override public boolean equals(Object obj) { if (obj == null) return false;
	 * if (this == (Bandit)obj) return true; if (getClass() != obj.getClass())
	 * return false; Bandit other = (Bandit) obj; return (brojZlatnika ==
	 * other.brojZlatnika && tim == other.tim); }
	 */
	
	
	
}
