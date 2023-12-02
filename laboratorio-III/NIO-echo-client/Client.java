import java.nio.*;
import java.nio.channels.SocketChannel;
import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Client {
private static final String SERVER_HOST = "localhost";
    private static final int SERVER_PORT = 8080;
    private static final int BUFFER_SIZE = 1024;
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input;
        do {
            input = scanner.nextLine();
            try {
                SocketChannel socketChannel = SocketChannel.open();
                socketChannel.connect(new InetSocketAddress(SERVER_HOST, SERVER_PORT));

                System.out.println("Connected to server: " + socketChannel.getRemoteAddress());

                String message = "Hello, Server!";
                ByteBuffer buffer = ByteBuffer.allocate(BUFFER_SIZE);
                buffer.put(message.getBytes());
                socketChannel.write(buffer);

                buffer.clear();
                socketChannel.read(buffer);
                buffer.flip();
                byte[] response = new byte[buffer.remaining()];
                buffer.get(response);

                System.out.println("Server response: " + new String(response));

                socketChannel.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        } while (!input.equalsIgnoreCase("exit"));
        scanner.close();

    }
}