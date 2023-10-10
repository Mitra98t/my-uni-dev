import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedDeque;

class Main{
    public static void main(String[] args){
        Queue<Persona> queue = new ConcurrentLinkedDeque<>();
        for(int i = 0; i < 10; i++){
            queue.add(new Persona());
        }
        Ufficio ufficio = new Ufficio();
        ufficio.apriSportelli(queue);
    }
}
