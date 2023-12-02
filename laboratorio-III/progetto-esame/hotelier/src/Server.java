import java.io.FileInputStream;
import java.net.ServerSocket;
import java.net.Socket;

import org.apache.commons.io.IOUtils;

public class Server {
    public static void main(String[] args) throws Exception {

        // FileInputStream fis = new FileInputStream("src/resources/Hotels.json");
        // String data = IOUtils.toString(fis, "UTF-8");
        // Hotel[] hotels = JSONParser.parseHotels(data);
        // for (Hotel hotel : hotels) {
        // System.out.println(hotel);
        // System.out.println("--------------------------------------------------");
        // }

        // tcp server
        try (ServerSocket server = new ServerSocket(6666)) {
            System.out.println("Server started");
            while (true) {
                Socket socket = server.accept();

                Thread thread = new Thread(new ServerCycle(socket));
                thread.start();
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
