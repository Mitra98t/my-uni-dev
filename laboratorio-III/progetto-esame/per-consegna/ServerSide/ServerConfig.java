public class ServerConfig {
    private int tcpPort;
    private int udpPort;
    private String udpAddress;
    private String HotelsPath;
    private String UsersPath;

    public ServerConfig(int tcpPort, int udpPort, String udpAddress, String HotelsPath, String UsersPath) {
        this.tcpPort = tcpPort;
        this.udpPort = udpPort;
        this.udpAddress = udpAddress;
        this.HotelsPath = HotelsPath;
        this.UsersPath = UsersPath;
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

    public String getHotelsPath() {
        return HotelsPath;
    }

    public String getUsersPath() {
        return UsersPath;
    }
}