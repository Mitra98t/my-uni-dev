public class ClientConfig {
  private int tcpPort;
  private int udpPort;
  private String udpAddress;

  public ClientConfig(int tcpPort, int udpPort, String udpAddress) {
    this.tcpPort = tcpPort;
    this.udpPort = udpPort;
    this.udpAddress = udpAddress;
  }

  public int getTcpPort() {
    return tcpPort;
  }

  public int getUdpPort() {
    return udpPort;
  }

  public String getUdpAddress() {
    return udpAddress;
  }

}