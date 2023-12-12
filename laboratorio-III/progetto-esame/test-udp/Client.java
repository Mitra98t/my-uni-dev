
import java.io.*;
import java.net.*;

public class Client {

  public final static int port = 6789;

  @SuppressWarnings("deprecation")
  public static void main(String[] args) throws UnknownHostException {

    // InetAddress group =InetAddress.getByName(args[0]);

    MulticastSocket ms = null;
    InetAddress group = InetAddress.getByName("225.255.4.1");

    try {

      ms = new MulticastSocket(port);
      ms.setInterface(InetAddress.getLocalHost());
      ms.joinGroup(group);
      System.out.println(group.isMulticastAddress() + "  il gruppo è in un indirizzo multicast");
      System.out.println(ms.isConnected() + "    se il multicast è connesso");
      byte[] buffer = new byte[8192];
      for (int i = 0; i < 10; i++) {
        DatagramPacket dp = new DatagramPacket(buffer, buffer.length);
        ms.receive(dp);

        String s = new String(dp.getData(), "8859_1");
        System.out.println(s);
      }
    } catch (IOException ex) {
      System.err.println(ex);
    }

  }

}