package revija;

public class Model {
	private static int id = -1;
	private int modelId = ++id;
	private Velicina velicina;
	
	public Model(Velicina velicina) {
		this.velicina = velicina;
	}
	
	public int dohvId() {
		return this.modelId;
	}
	
	public Velicina dohvVelicinu() {
		return velicina;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("Model ").append(this.dohvId()).append(" (").append(this.dohvVelicinu()).append(") ");
		return sb.toString();
	}
	
	
}
