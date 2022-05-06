package banditi;

import java.util.LinkedList;
import java.util.List;

public class Kompozicija {
	private List<Vagon> listaVagona = new LinkedList<Vagon>();
	
	public void dodajVagon(Vagon vagon) {
		listaVagona.add(vagon);
	}
	
	public Vagon dohvatiVagon(Bandit bandit) throws GNepostojeciVagon{
		for (Vagon vagon : listaVagona) {
			if(vagon.sadrziBandita(bandit)) {
				return vagon;
			}
		}
		throw new GNepostojeciVagon();
	}
	
	public Vagon dohvatiSusedniVagon(Vagon vagon, Smer smer) throws GNepostojeciVagon{
		Vagon vIspred = null;
		Vagon vIza = null;
		short sl = 0;
		for (Vagon v : listaVagona) {
			if(sl == 1) {
				vIza= v;
				break;
			}
			if(v.equals(vagon)) 
				sl = 1;
			else 
				vIspred = v;
		}
		if(sl == 0) throw new GNepostojeciVagon();
		if(smer == Smer.ISPRED) {
			if(vIspred != null)
				return vIspred;
		}
		else {
			if(vIza != null)
				return vIza;
		}
		throw new GNepostojeciVagon();
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		short i = 0;
		for (Vagon vagon : listaVagona) {
			if(i > 0)
				sb.append("_");
			sb.append(vagon);
			i++;
		}
		return sb.toString();
	}
	
}
