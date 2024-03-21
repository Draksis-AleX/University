public class Posizioni extends GnrPosizioni {
    @Override
    public Posto getPosto(int tipo){
        if (tipo == 1) return new Palco();
        return new Platea();
    }   
}
