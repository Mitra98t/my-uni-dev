import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.Socket;
import java.util.concurrent.atomic.AtomicInteger;

public class Client {
  private static final AtomicInteger clientPortCounter = new AtomicInteger(5000);
  private static DatagramSocket udpSocket;

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
          int clientPort = clientPortCounter.incrementAndGet();
          udpSubscribe(clientPort);
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
        udpListenerThread = new Thread(udpListener);
        udpListenerThread.start();
      }
      if (status == 3) {
        udpUnsubscribe();
        udpListenerThread.interrupt();
      }
    } while (!serverMessage.equals("exit-now"));

    out.close();
    in.close();
    stdIn.close();
    socket.close();
  }

  public static void udpSubscribe(int port) throws IOException {

    udpSocket = new DatagramSocket(port);
    byte[] buffer = new byte[1024];

    DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
    udpSocket.receive(packet);
    String message = new String(packet.getData(), 0, packet.getLength());

    System.out.println("\n---\nNotifica:\n" + message + "\n---\n");
  }

  public static void udpUnsubscribe() {
    udpSocket.close();
  }

}