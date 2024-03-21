public class MainEsami {
    
    public static void main(String[] args) {
        Studente s = new Studente();
        s.setNome("Alan", "Rossi");
        s.setMatr("M12345");
        s.nuovoEsame("Italiano", 8);
        s.nuovoEsame("Fisica", 7);
        s.printAll();
    }

}
