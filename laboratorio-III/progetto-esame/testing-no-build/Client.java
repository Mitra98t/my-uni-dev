import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.Socket;
import java.util.concurrent.atomic.AtomicInteger;

public class Client {
  private static MulticastSocket multicastSocket;
  private static InetAddress group;
  private static boolean closed = false;

  public static void main(String[] args) throws IOException {
    Socket socket = new Socket("localhost", 6666);
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
          while (true) {
            receiveMulticastMessage();
          }
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
    System.setProperty("java.net.preferIPv4Stack", "true");

    multicastSocket = new MulticastSocket(4445);

    // multicastSocket.setReuseAddress(true);

    group = InetAddress.getByName("239.30.40.40");
    multicastSocket.joinGroup(group);
  }

  public static void udpUnsubscribe() {
    try {
      // Lascia il gruppo multicast
      multicastSocket.leaveGroup(group);
    } catch (IOException e) {
      e.printStackTrace();
    }

    // Chiudi il socket
    multicastSocket.close();
  }

  public static void receiveMulticastMessage() throws IOException {
    while (!closed) {

      byte[] buffer = new byte[1024];
      DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

      // Ricevi il pacchetto
      multicastSocket.receive(packet);

      // Converti i dati ricevuti in una stringa
      String message = new String(packet.getData(), 0, packet.getLength());

      // Stampa il messaggio
      System.out.println("Messaggio ricevuto: " + message);
    }
  }

}