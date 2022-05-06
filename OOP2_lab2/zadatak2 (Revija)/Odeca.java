package revija;

public class Odeca implements Nosivo {
	String naziv;
	Velicina velicina;
	
	public Odeca(String naziv, Velicina velicina) {
		this.naziv = naziv;
		this.velicina = velicina;
	}
	
	public String dohvNaziv() {
		return this.naziv;
	}
	
	public Velicina dohvVelicinu() {
		return this.velicina;
	}

	@Override
	public boolean odgovara(Model model) {
		if(velicina.manja(model.dohvVelicinu()))return false;
		return true;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("odeća ").append(naziv).append(" ").append(velicina);
		return sb.toString();
	}
	
	
}
