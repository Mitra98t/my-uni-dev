import java.io.*;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Paths;

import com.google.gson.Gson;

public class ClientMain {
  private static MulticastSocket multicastSocket;
  private static InetAddress group;
  private static boolean closed = false;
  private static int tcpPort;
  private static int udpPort;
  private static String udpAddress;

  public static void main(String[] args) throws IOException {
    parseConfig();
    Socket socket = new Socket("localhost", tcpPort);
    PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
    BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
    BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
    CliHandlerClient cliHandler = new CliHandlerClient(out);
    Thread udpListenerThread = null;

    Runnable udpListener = new Runnable() {
      @Override
      public void run() {
        try {
          udpSubscribe();
          receiveMulticastMessage();
        } catch (IOException e) {
          e.printStackTrace();
        }
      }
    };

    String serverMessage;
    do {
      serverMessage = in.readLine();
      int status = cliHandler.interpret(serverMessage);
      if (status == 1) {
        break;
      }
      if (status == 2) {
        closed = false;
        udpListenerThread = new Thread(udpListener);
        udpListenerThread.start();
      }
      if (status == 3) {
        closed = true;
        udpUnsubscribe();
        udpListenerThread.interrupt();
      }
    } while (!serverMessage.equals("exit-now"));

    out.close();
    in.close();
    stdIn.close();
    socket.close();
  }

  public static void udpSubscribe() throws IOException {

    multicastSocket = new MulticastSocket(udpPort);

    multicastSocket.setInterface(InetAddress.getLocalHost());
    group = InetAddress.getByName(udpAddress);

    multicastSocket.joinGroup(group);
  }

  public static void udpUnsubscribe() {
    try {
      multicastSocket.leaveGroup(group);
    } catch (IOException e) {
      e.printStackTrace();
    }

    multicastSocket.close();
  }

  public static void receiveMulticastMessage() throws IOException {
    while (!closed) {
      System.out.println("wating message");
      byte[] buffer = new byte[1024];
      DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

      multicastSocket.receive(packet);

      String message = new String(packet.getData(), 0, packet.getLength());

      System.out.println("Messaggio ricevuto: " + message);
    }
  }

  private static void parseConfig() {
    Gson gson = new Gson();
    try {
      Reader reader = Files.newBufferedReader(Paths.get("./ClientConfig.json"));
      ClientConfig config = gson.fromJson(reader, ClientConfig.class);
      tcpPort = config.getTcpPort();
      udpPort = config.getUdpPort();
      udpAddress = config.getUdpAddress();
    } catch (Exception e) {
      System.out.println(e);
    }

  }

}