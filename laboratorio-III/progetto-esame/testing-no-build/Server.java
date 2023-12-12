import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class Server {
    private static MulticastSocket multicastSocket;
    private static InetAddress group;

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
        try {

            multicastSocket = new MulticastSocket(4445);

            multicastSocket.setReuseAddress(true);

            multicastSocket.setInterface(InetAddress.getLocalHost());
            System.out.println("\ninterface: " + multicastSocket.getInterface() + "\n");
            group = InetAddress.getByName("230.30.40.40");

            multicastSocket.joinGroup(group);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void broadcast(String broadcastMessage) {
        try {
            System.out.println(broadcastMessage);
            byte[] buffer = broadcastMessage.getBytes();
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, group, 4445);
            multicastSocket.send(packet);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void stopUdpServer() {
        try {
            // Lascia il gruppo multicast
            multicastSocket.leaveGroup(group);

            // Chiudi il socket
            multicastSocket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
