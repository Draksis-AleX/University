public class Persona{
    private String nome;
    private int eta;
    public Persona(String n, int e){
        nome = n;
        eta = e;
    }
    public String getNome(){ return nome; }
    public int getEta(){ return eta; }
    public static Persona getMax(Persona p1, Persona p2){
        if (p1.getEta() > p2.getEta())
            return p1;
        return p2;
    }
}