package banditi;

public abstract class Akcija {
	Kompozicija kompozicija;
	
	public Akcija(Kompozicija kompozicija) {
		this.kompozicija = kompozicija;
	}
	
	abstract public void izvrsi(Bandit bandit) throws GNepostojeciVagon;
}
