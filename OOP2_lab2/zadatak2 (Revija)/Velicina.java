package revija;

public class Velicina {
	private Oznaka oznaka;
	
	public static enum Oznaka { S, M, L };
	
	
	public Velicina(Oznaka oznaka) {
		this.oznaka = oznaka;
	}
	
	public Oznaka dohvOznaku() {
		return oznaka;
	}
	
	public boolean manja(Velicina velicina2) {
		if(this.oznaka == Oznaka.S && velicina2.oznaka != Oznaka.S) return true;
		if(this.oznaka == Oznaka.M && velicina2.oznaka == Oznaka.L) return true;
		return false;
	}

	@Override
	public String toString() {
		return dohvOznaku().toString();
	}
	
	
}
