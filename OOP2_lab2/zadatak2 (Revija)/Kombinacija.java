package revija;

public class Kombinacija{
	private int maxBroj, trenutniBroj = 0;
	private Nosivo stvari[];
	
	public Kombinacija(int broj) {
		maxBroj = broj;
		stvari = new Nosivo[broj];
	}
	
	public int dohvBrStvari() {
		return this.trenutniBroj;
	}
	
	public int dohvMaxBrStvari() {
		return this.maxBroj;
	}
	
	public void dodaj(Nosivo stvar) throws GDodavanje{
		if(trenutniBroj==maxBroj) throw new GDodavanje();
		this.stvari[trenutniBroj] = stvar;
		++trenutniBroj;
	}
	
	public Nosivo dohvStvar(int pozicija) throws GIndeks {
		if(pozicija < 0 || pozicija >= trenutniBroj || stvari[pozicija] == null) throw new GIndeks();
		return stvari[pozicija];
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("[");
		for (int i = 0; i < this.trenutniBroj; i++) {
			if(i != 0) sb.append(",");
			sb.append(stvari[i]);
		}
		sb.append("]");
		return sb.toString();
	}
	
	
}
