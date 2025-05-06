
package rc_teme;

import java.io.*;
import java.math.BigInteger;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    public static void main(String[] args) throws Exception {
        int port = 8888;
        System.out.println("Server pornit pe portul " + port);
        try (ServerSocket serverSocket = new ServerSocket(port);
             Socket client = serverSocket.accept();
             BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
             PrintWriter out = new PrintWriter(client.getOutputStream(), true)) {

            System.out.println("Client conectat: " + client.getInetAddress());

            String mode;
            while ((mode = in.readLine()) != null) {
                if (mode.equals("exit")) break;

                if (mode.equals("1")) {

                    BigInteger p = new BigInteger(in.readLine());
                    BigInteger g = new BigInteger(in.readLine());


                    BigInteger yA = new BigInteger(in.readLine());
                    BigInteger xB = CryptoUtils.generatePrivateKey(p);
                    BigInteger yB = CryptoUtils.generatePublicKey(xB, g, p);
                    out.println(yB.toString());


                    BigInteger shared = CryptoUtils.computeSharedBig(yA, xB, p);
                    int shift = shared.mod(BigInteger.valueOf(26)).intValue();
                    String cipher = in.readLine();
                    System.out.println("[Server] Caesar criptat: " + cipher);
                    String plain = CryptoUtils.caesarDecrypt(cipher, shift);
                    System.out.println("[Server] Decriptat: " + plain);

                } else if (mode.equals("2")) {

                    String key = in.readLine();
                    int origLen = Integer.parseInt(in.readLine());
                    String cipher = in.readLine();
                    System.out.println("[Server] Transp criptat: " + cipher);
                    String plain = CryptoUtils.transposeDecrypt(cipher, key, origLen);
                    System.out.println("[Server] Decriptat: " + plain);
                }

                System.out.println("----------");
            }
        }
        System.out.println("Server închis.");
    }
}
