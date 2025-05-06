// CryptoUtils.java
package rc_teme;

import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.*;

public class CryptoUtils {
    private static final SecureRandom random = new SecureRandom();


    public static final BigInteger P_DEFAULT = BigInteger.valueOf(23);
    public static final BigInteger G_DEFAULT = BigInteger.valueOf(5);

    public static BigInteger generatePrime(int bitLength) {
        return BigInteger.probablePrime(bitLength, random);
    }

    public static BigInteger findPrimitiveRoot(BigInteger p) {
        BigInteger phi = p.subtract(BigInteger.ONE);
        Set<BigInteger> factors = factorize(phi);
        for (BigInteger g = BigInteger.valueOf(2); g.compareTo(p) < 0; g = g.add(BigInteger.ONE)) {
            boolean ok = true;
            for (BigInteger q : factors) {
                if (g.modPow(phi.divide(q), p).equals(BigInteger.ONE)) {
                    ok = false;
                    break;
                }
            }
            if (ok) return g;
        }
        throw new IllegalStateException("Nu s-a găsit rădăcină primitivă pentru p=" + p);
    }


    private static Set<BigInteger> factorize(BigInteger n) {
        BigInteger two = BigInteger.valueOf(2);
        Set<BigInteger> fac = new HashSet<>();
        BigInteger tmp = n;
        while (tmp.mod(two).equals(BigInteger.ZERO)) {
            fac.add(two);
            tmp = tmp.divide(two);
        }
        BigInteger f = BigInteger.valueOf(3);
        while (f.multiply(f).compareTo(tmp) <= 0) {
            if (tmp.mod(f).equals(BigInteger.ZERO)) {
                fac.add(f);
                tmp = tmp.divide(f);
            } else {
                f = f.add(two);
            }
        }
        if (tmp.compareTo(BigInteger.ONE) > 0) fac.add(tmp);
        return fac;
    }

    public static BigInteger generatePrivateKey(BigInteger p) {
        return new BigInteger(p.bitLength() - 2, random).add(BigInteger.ONE);
    }

    public static BigInteger generatePrivateKey() {
        return generatePrivateKey(P_DEFAULT);
    }

    public static BigInteger generatePublicKey(BigInteger x, BigInteger g, BigInteger p) {
        return g.modPow(x, p);
    }

    public static BigInteger generatePublicKey(BigInteger x) {
        return generatePublicKey(x, G_DEFAULT, P_DEFAULT);
    }

    public static BigInteger computeSharedBig(BigInteger yOther, BigInteger x, BigInteger p) {
        return yOther.modPow(x, p);
    }

    public static int computeSharedKey(BigInteger yOther, BigInteger x) {
        BigInteger k = computeSharedBig(yOther, x, P_DEFAULT);
        return k.mod(BigInteger.valueOf(26)).intValue();
    }
    // --- CIFRUL Caesar ---
    public static String caesarEncrypt(String text, int shift) {
        StringBuilder sb = new StringBuilder();
        for (char c : text.toCharArray()) {
            if (Character.isLetter(c)) {
                char base = Character.isUpperCase(c) ? 'A' : 'a';
                sb.append((char)((c - base + shift) % 26 + base));
            } else {
                sb.append(c);
            }
        }
        return sb.toString();
    }
    public static String caesarDecrypt(String text, int shift) {
        return caesarEncrypt(text, 26 - (shift % 26));
    }

    // --- CIFRUL cu TRANSPOZIȚIE ---
    public static int[] getTransposeOrder(String key) {
        int n = key.length();
        Character[] chars = new Character[n];
        for (int i = 0; i < n; i++) chars[i] = key.charAt(i);
        List<Map.Entry<Character, Integer>> list = new ArrayList<>();
        for (int i = 0; i < n; i++)
            list.add(new AbstractMap.SimpleEntry<>(chars[i], i));
        list.sort(Comparator.comparing(Map.Entry::getKey));
        int[] order = new int[n];
        for (int rank = 0; rank < n; rank++) {
            order[list.get(rank).getValue()] = rank;
        }
        return order;
    }
    public static String transposeEncrypt(String text, String key) {
        int cols = key.length();
        int rows = (int)Math.ceil((double)text.length() / cols);
        char[][] mat = new char[rows][cols];
        for (int i = 0; i < rows*cols; i++) {
            mat[i/cols][i%cols] = (i < text.length() ? text.charAt(i) : 'X');
        }
        int[] order = getTransposeOrder(key);
        StringBuilder sb = new StringBuilder();
        for (int colRank = 0; colRank < cols; colRank++) {
            for (int j = 0; j < cols; j++) {
                if (order[j] == colRank) {
                    for (int i = 0; i < rows; i++) sb.append(mat[i][j]);
                    break;
                }
            }
        }
        return sb.toString();
    }
    public static String transposeDecrypt(String cipher, String key, int origLen) {
        int cols = key.length();
        int rows = cipher.length() / cols;
        char[][] mat = new char[rows][cols];
        int[] order = getTransposeOrder(key);
        int idx = 0;
        for (int colRank = 0; colRank < cols; colRank++) {
            for (int j = 0; j < cols; j++) {
                if (order[j] == colRank) {
                    for (int i = 0; i < rows; i++) mat[i][j] = cipher.charAt(idx++);
                    break;
                }
            }
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < rows*cols; i++) sb.append(mat[i/cols][i%cols]);
        return sb.substring(0, Math.min(origLen, sb.length()));
    }
}
