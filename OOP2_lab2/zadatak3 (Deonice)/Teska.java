package skijanje;

public class Teska extends Deonica {

	public Teska(double duzina, double nagib) {
		super(duzina, nagib);
		this.oznaka = 'T';
	}
	
	@Override
	public double ubrzanje() {
		return (9.81 * Math.sin(this.nagib()*Math.PI/180));
	}

	@Override
	public char oznaka() {
		return this.oznaka;
	}
	
}
