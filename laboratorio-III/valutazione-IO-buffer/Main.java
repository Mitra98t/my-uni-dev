import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.FileChannel;
import java.nio.channels.ReadableByteChannel;
import java.nio.channels.WritableByteChannel;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try {
            ReadableByteChannel source = Channels.newChannel(new FileInputStream("input.txt"));
            WritableByteChannel dest = Channels.newChannel(new FileOutputStream("output.txt"));

            Scanner sc = new Scanner(System.in);

            System.out.println("Choose copying method");
            System.out.println("1. File channel con buffer diretti");
            System.out.println("2. File channel con buffer indiretti");
            System.out.println("3. File channel con operazione Transfer To");
            System.out.println("4. Buffered stream IO");
            System.out.println("5. Byte array con implementazione mia");

            String choice = sc.nextLine();
            sc.close();

            switch (choice) {
                case "1":
                    copy1(source, dest);
                    break;
                case "2":
                    copy2(source, dest);
                    break;
                case "3":
                    copy3(source, dest);
                    break;
                case "4":
                    copy4(source, dest);
                    break;
                case "5":
                    copy5(source, dest);
                    break;

                default:
                    System.out.println("Invalid choice");
                    break;
            }

            source.close();
            dest.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static void copy1(ReadableByteChannel in, WritableByteChannel out) throws IOException {
        ByteBuffer buffer = ByteBuffer.allocateDirect(1024);

        while (in.read(buffer) != -1) {
            buffer.flip();
            out.write(buffer);
            buffer.clear();
        }
        System.out.println("File copied with direct buffers");
    }

    static void copy2(ReadableByteChannel in, WritableByteChannel out) throws IOException {
        try {
            // Creazione di un buffer indiretto
            ByteBuffer buffer = ByteBuffer.allocate(1024);

            // Copia dei dati
            while (in.read(buffer) != -1) {
                buffer.flip();
                while (buffer.hasRemaining()) {
                    out.write(buffer);
                }
                buffer.clear();
            }
            System.out.println("File copied with indirect buffers");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static void copy3(ReadableByteChannel in, WritableByteChannel out) throws IOException {
        ((FileChannel) in).transferTo(0, Integer.MAX_VALUE, ((FileChannel) out));
        System.out.println("File copied with ");
    }

    static void copy4(ReadableByteChannel in, WritableByteChannel out) throws IOException {
        try (BufferedInputStream bis = new BufferedInputStream(Channels.newInputStream(in));
                BufferedOutputStream bos = new BufferedOutputStream(Channels.newOutputStream(out))) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = bis.read(buffer)) != -1) {
                bos.write(buffer, 0, bytesRead);
            }
            System.out.println("File copied with buffered stream IO");
        }
    }

    static void copy5(ReadableByteChannel in, WritableByteChannel out) throws IOException {
        System.out.println("Still to implement");
    }
}
