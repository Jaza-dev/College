package banditi;

public class Pomeranje extends Akcija {
	private Smer smer;
	
	public Pomeranje(Kompozicija kompozicija, Smer smer) {
		super(kompozicija);
		this.smer = smer;
	}

	@Override
	public void izvrsi(Bandit bandit) throws GNepostojeciVagon {
		try {
			Vagon susedniVagon = this.kompozicija.dohvatiSusedniVagon(kompozicija.dohvatiVagon(bandit), smer);
			kompozicija.dohvatiVagon(bandit).ukloniBandita(bandit);
			susedniVagon.dodajBandita(bandit);
		}catch (GNepostojeciVagon e) {
			return;
		}
		
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("Pomeranje: ").append(smer);
		return sb.toString();
	}

}
