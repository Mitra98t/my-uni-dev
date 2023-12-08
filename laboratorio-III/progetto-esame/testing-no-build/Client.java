import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.Socket;

public class Client {

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
          udpSubscribe();
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

  public static void udpSubscribe() throws IOException {

    udpSocket = new DatagramSocket(4445);
    // Crea un buffer per ricevere i dati
    byte[] buffer = new byte[1024];

    // Crea un DatagramPacket per ricevere i dati
    DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
    // Ricevi il pacchetto
    udpSocket.receive(packet);
    // Converti i dati ricevuti in una stringa
    String message = new String(packet.getData(), 0, packet.getLength());

    // Stampa il messaggio
    System.out.println("\n---\nNotifica:\n" + message + "\n---\n");
  }

  public static void udpUnsubscribe() {
    udpSocket.close();
  }

}