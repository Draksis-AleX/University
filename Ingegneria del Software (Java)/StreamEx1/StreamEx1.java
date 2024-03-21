
import java.util.*;
import java.util.stream.Collectors;

public class StreamEx1 {
    public static void main(String[] args) {
        
        List<Persona> amici = Arrays.asList(new Persona("Saro", 24), new Persona("Iano", 19), new Persona("Al", 16));

        int somma = amici.stream()
            .map(Persona::getEta)
            .reduce(0, Integer::sum);

        System.out.println(somma);

        long c  = amici.stream()
            .filter(s -> s.getNome().equals("Iano"))
            .filter(s -> s.getEta() == 19)
            .count();

        System.out.println(c);

        Optional<Persona> pmax = amici.stream()
            .filter(x -> x.getEta() < 20)
            .reduce(Persona::getMax);
        
        if(pmax.isPresent()) System.out.println("Persona >> " + pmax.get().getNome());

        Optional<Persona> pmax2 = amici.stream()
            .filter(x -> x.getEta() < 20)
            .max(Comparator.comparing(Persona::getEta));

        if(pmax.isPresent()) System.out.println("Persona >> " + pmax2.get().getNome());

        List<Integer> e = amici.stream()
            .map(Persona::getEta)
            .collect(Collectors.toList());
        
        //oppure da Java 16
        
        List<Integer> e1 =  amici.stream()
            .map(Persona::getEta)
            .toList();
    }
}