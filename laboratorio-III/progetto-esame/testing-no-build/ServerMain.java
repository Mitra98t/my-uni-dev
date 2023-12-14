import java.io.FileInputStream;
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

import org.apache.commons.io.IOUtils;
import org.json.JSONObject;

public class ServerMain {
    private static MulticastSocket multicastSocket;
    private static InetAddress group;
    private static int tcpPort;
    private static int udpPort;
    private static String udpAddress;
    private static String HotelsPath;
    private static String UsersPath;

    public static void main(String[] args) throws Exception {
        parseConfig();
        ExecutorService executor = Executors.newCachedThreadPool();
        ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
        scheduler.scheduleAtFixedRate(new ServerSaver(), 30, 30, TimeUnit.SECONDS);

        startUdpServer();

        try (ServerSocket server = new ServerSocket(tcpPort)) {
            System.out.println("Server started");
            while (true) {
                Socket socket = server.accept();
                System.out.println("Client accepted");

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
        try {

            multicastSocket = new MulticastSocket(udpPort);

            multicastSocket.setReuseAddress(true);

            multicastSocket.setInterface(InetAddress.getLocalHost());
            System.out.println("\ninterface: " + multicastSocket.getInterface() + "\n");
            group = InetAddress.getByName(udpAddress);

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
            multicastSocket.leaveGroup(group);

            multicastSocket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String getHotelsPath() {
        return HotelsPath;
    }

    public static String getUsersPath() {
        return UsersPath;
    }

    private static void parseConfig() {
        try {
            FileInputStream fis = new FileInputStream("./ServerConfig.json");
            String data = IOUtils.toString(fis, "UTF-8");
            JSONObject config = new JSONObject(data);
            tcpPort = config.getInt("tcpPort");
            udpPort = config.getInt("udpPort");
            udpAddress = config.getString("udpAddress");
            HotelsPath = config.getString("HotelsPath");
            UsersPath = config.getString("UsersPath");
        } catch (Exception e) {
            System.out.println(e);
        }

    }
}
