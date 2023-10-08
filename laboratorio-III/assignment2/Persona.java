import java.security.SecureRandom;
import java.util.UUID;
import java.util.concurrent.TimeUnit;

public class Persona implements Runnable {

    private final String id = UUID.randomUUID().toString().substring(0, 8);
    private final long sleepTime = new SecureRandom().nextInt(4) + 1;

    @Override
    public void run() {
        System.out.println("STA: " + id + " - " + sleepTime + " sec.");
        try {
            TimeUnit.SECONDS.sleep(sleepTime);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("END: " + id + " - " + sleepTime + " sec.");
    }

    public String getId() {
        return id;
    }

    public String getSleepTime() {
        return sleepTime + " sec.";
    }
}