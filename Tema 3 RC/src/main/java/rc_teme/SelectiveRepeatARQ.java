package rc_teme;

import java.util.*;

public class SelectiveRepeatARQ {
    static class Packet {
        final int id;
        boolean acked = false;
        int sendCount = 0;
        long lastSentTime = 0;
        Packet(int id) { this.id = id; }
    }

    private static boolean sendAndReceive(Packet p, double pLoss, double ackLoss, Random rnd) {
        p.sendCount++;
        p.lastSentTime = System.currentTimeMillis();
        System.out.printf("%s pachet %d … ", p.sendCount>1 ? "Retrimit" : "Trimit", p.id);

        if (rnd.nextDouble() < pLoss) {
            System.out.println("Pierdut!");
            return false;
        }
        System.out.println("Primit de receiver.");

        System.out.printf("  Trimite ACK(%d) … ", p.id);
        if (rnd.nextDouble() < ackLoss) {
            System.out.println("Pierdut!");
            return false;
        }
        System.out.println("Ajunge la sender.");
        return true;
    }

    public static void main(String[] args) throws InterruptedException {
        final int    TOTAL      = 8;
        final int    WINDOW     = 4;
        final double P_LOSS     = 0.3;
        final double ACK_LOSS   = 0.1;
        final long   TIMEOUT    = 1000;

        List<Packet> pkts = new ArrayList<>();
        for (int i = 1; i <= TOTAL; i++)
            pkts.add(new Packet(i));

        Random rnd = new Random();
        List<Integer> receiveOrder = new ArrayList<>();

        int base    = 0;
        int nextSeq = 0;

        while (base < TOTAL) {

            while (nextSeq < TOTAL && nextSeq < base + WINDOW) {
                Packet p = pkts.get(nextSeq++);
            }

            int windowSize = Math.min(WINDOW, TOTAL - base);
            System.out.printf("=== Ferestră activă [%d .. %d] (dim %d) ===%n",
                    base+1, base + windowSize, windowSize);

            for (int i = base; i < base + windowSize; i++) {
                Packet p = pkts.get(i);
                if (!p.acked && (p.sendCount == 0 || System.currentTimeMillis() - p.lastSentTime >= TIMEOUT)) {

                    boolean gotAck = sendAndReceive(p, P_LOSS, ACK_LOSS, rnd);
                    if (gotAck) {
                        p.acked = true;
                        if (!receiveOrder.contains(p.id))
                            receiveOrder.add(p.id);
                    }
                }
            }

                if (pkts.get(base).acked) {
                base++;

                int newWin = Math.min(WINDOW, TOTAL - base);
                System.out.printf("-> Slide la [%d .. %d] (dim %d)%n",
                        base+1, base + newWin, newWin);

                if (nextSeq < TOTAL) {
                    Packet p = pkts.get(nextSeq++);
                    boolean gotAck = sendAndReceive(p, P_LOSS, ACK_LOSS, rnd);
                    if (gotAck) {
                        p.acked = true;
                        if (!receiveOrder.contains(p.id))
                            receiveOrder.add(p.id);
                    }
                }
                continue;
            }

            System.out.printf("Timeout pentru pachetul %d… aștept %d ms%n \n", base+1, TIMEOUT);
            Thread.sleep(TIMEOUT);
        }

        System.out.println("\n=== Simulare terminată ===");
        System.out.println("Ordinea efectivă de recepție: " + receiveOrder);

        List<Integer> sorted = new ArrayList<>(receiveOrder);
        Collections.sort(sorted);
        System.out.println("Ordinea sortată             : " + sorted);
    }
}
