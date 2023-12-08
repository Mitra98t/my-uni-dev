import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class Server {
    private static DatagramSocket udpSocket;

    public static void main(String[] args) throws Exception {
        ExecutorService executor = Executors.newCachedThreadPool();
        ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
        scheduler.scheduleAtFixedRate(new ServerSaver(), 30, 30, TimeUnit.SECONDS);
        startUdpServer();
        // tcp server
        try (ServerSocket server = new ServerSocket(6666)) {
            System.out.println("Server started");
            while (true) {
                Socket socket = server.accept();
                System.out.println("Client accepted");

                // Invece di creare un nuovo Thread per ogni connessione, passa il task
                // all'ExecutorService.
                executor.execute(new ServerCycle(socket));
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            executor.shutdown();
            scheduler.shutdown();
            stopUdpServer();
        }
    }

    public static void startUdpServer() throws SocketException {
        // Inizializza il DatagramSocket quando avvii il server
        udpSocket = new DatagramSocket();
        udpSocket.setBroadcast(true);
    }

    public static void broadcast(String broadcastMessage) throws IOException {
        try {
            byte[] buffer = broadcastMessage.getBytes();
            InetAddress address = InetAddress.getByName("255.255.255.255");
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, 4445);
            udpSocket.send(packet);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void stopUdpServer() {
        // Chiudi il DatagramSocket quando fermi il server
        udpSocket.close();
    }
}
