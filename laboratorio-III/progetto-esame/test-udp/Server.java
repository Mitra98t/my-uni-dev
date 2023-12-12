import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.UnknownHostException;
import java.sql.Timestamp;
import java.time.ZonedDateTime;

public class Server {
  public final static int port = 6789;

  public static void main(String[] args) throws InterruptedException, IOException {

    // read the address from the command line

    try {
      InetAddress group = InetAddress.getByName("225.255.4.1");

      // byte[] buffer= new byte[800];
      byte[] buffer;

      while (true) {
        Timestamp ts = Timestamp.from(ZonedDateTime.now().toInstant());
        String ts_str = ts.toString();
        buffer = ts_str.getBytes();
        DatagramPacket dp = new DatagramPacket(buffer, buffer.length, group, port);
        MulticastSocket ms = new MulticastSocket(port);
        ms.send(dp);

        Thread.sleep(2000);
      }
    } catch (IOException ex) {
      System.err.println(ex);
    }

  }

}