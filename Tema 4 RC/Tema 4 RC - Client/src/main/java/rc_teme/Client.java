
package rc_teme;

import java.io.*;
import java.math.BigInteger;
import java.net.Socket;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Client {
    public static void main(String[] args) throws Exception {
        String host = "localhost";
        int port = 8888;
        try (Socket socket = new Socket(host, port);
             BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
             Scanner sc = new Scanner(System.in)) {

            System.out.println("Conectat la server " + host + ":" + port);
            while (true) {
                System.out.println("Alege modul de criptare:");
                System.out.println("1 – Ceasar cu Diffie-Hellman");
                System.out.println("2 – Transpoziție");
                System.out.println("0 – Iesire");
                System.out.print("> ");
                String choice = sc.nextLine();
                if (choice.equals("0")) {
                    out.println("exit");
                    break;
                }

                if (choice.equals("1")) {
                    out.println("1");

                    System.out.print("Generezi aleatoriu p şi g? (d/n): ");
                    String ans = sc.nextLine();
                    BigInteger p, g;
                    if (ans.equalsIgnoreCase("d")) {
                        System.out.print("Introdu lungimea în biți a primului modul (ex: 16): ");
                        int bits = Integer.parseInt(sc.nextLine());
                        p = CryptoUtils.generatePrime(bits);
                        g = CryptoUtils.findPrimitiveRoot(p);
                    } else {

                        while (true) {
                            System.out.print("Introdu p (prim): ");
                            p = new BigInteger(sc.nextLine());
                            if (p.isProbablePrime(20)) {
                                break;
                            } else {
                                System.out.println("Valoarea introdusă nu este primă. Te rog încearcă din nou.");
                            }
                        }

                        while (true) {
                            System.out.print("Introdu g (generator, < p): ");
                            g = new BigInteger(sc.nextLine());
                            if (g.compareTo(BigInteger.TWO) >= 0 && g.compareTo(p) < 0) {
                                break;
                            } else {
                                System.out.println("Generator invalid. g trebuie să fie ≥2 și < p.");
                            }
                        }
                    }

                    out.println(p.toString());
                    out.println(g.toString());
                    BigInteger xA = CryptoUtils.generatePrivateKey(p);
                    BigInteger yA = CryptoUtils.generatePublicKey(xA, g, p);
                    out.println(yA.toString());

                    BigInteger yB = new BigInteger(in.readLine());
                    BigInteger shared = CryptoUtils.computeSharedBig(yB, xA, p);
                    int shift = shared.mod(BigInteger.valueOf(26)).intValue();

                    System.out.print("Mesaj de trimis: ");
                    String msg = sc.nextLine();
                    String cipher = CryptoUtils.caesarEncrypt(msg, shift);
                    System.out.println("[Client] Caesar criptat: " + cipher);
                    out.println(cipher);

                } else if (choice.equals("2")) {

                    String key;
                    while (true) {
                        System.out.print("Introdu cheia (ex: SALUT): ");
                        key = sc.nextLine().trim();

                        if (!key.matches("[A-Za-z]+")) {
                            System.out.println("Cheia poate conține doar litere. Încearcă din nou.");
                            continue;
                        }

                        Set<Character> seen = new HashSet<>();
                        boolean dup = false;
                        for (char c : key.toUpperCase().toCharArray()) {
                            if (!seen.add(c)) {
                                dup = true;
                                break;
                            }
                        }
                        if (dup) {
                            System.out.println("Cheia nu poate conține litere duplicate. Încearcă din nou.");
                            continue;
                        }
                        break;
                    }

                    System.out.print("Mesaj de trimis: ");
                    String msg = sc.nextLine();
                    String cipher = CryptoUtils.transposeEncrypt(msg, key);
                    System.out.println("[Client] Transp criptat: " + cipher);
                    out.println(key);
                    out.println(msg.length());
                    out.println(cipher);

                } else {
                    System.out.println("Opțiune invalidă.");
                }
                System.out.println("----------");
            }
        }
        System.out.println("Client închis.");
    }
}
