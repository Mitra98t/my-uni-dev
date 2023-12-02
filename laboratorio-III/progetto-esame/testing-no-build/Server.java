import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    public static void main(String[] args) throws Exception {

        
        // tcp server
        try (ServerSocket server = new ServerSocket(6666)) {
            System.out.println("Server started");
            while (true) {
                Socket socket = server.accept();
                System.out.println("Client accepted");

                Thread thread = new Thread(new ServerCycle(socket));
                thread.start();
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
