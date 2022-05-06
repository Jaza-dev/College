package skijanje;

abstract public class Deonica {
	private double duzina, nagib;
	protected char oznaka;
	
	public Deonica(double duzina, double nagib) {
		this.duzina = duzina;
		this.nagib = nagib;
	}

	public double duzina() {
		return duzina;
	}

	public double nagib() {
		return nagib;
	}
	
	public double brzina(double pocetnaBrzina) {
		return Math.sqrt(2 * this.ubrzanje() * this.duzina() + Math.pow(pocetnaBrzina, 2));
	}
	
	public double vreme(double pocetnaBrzina) {
		return ((this.brzina(pocetnaBrzina)-pocetnaBrzina) / this.ubrzanje());
	}
	
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(oznaka()).append("(").append(duzina).append(",").append(nagib).append(")");
		return sb.toString();
	}

	abstract public char oznaka();
	abstract public double ubrzanje();
	
}
