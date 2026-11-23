import java.io.*;
import java.net.*;
import java.nio.file.*;
import java.util.concurrent.*;

public class ScoreServerSync {
    private static final int PORT = 9012;
    private static final String FILE_NAME = "shared_score.txt";

    public static synchronized void updateScore(String name) throws Exception {
        int score = 0;

        if (Files.exists(Paths.get(FILE_NAME))) {
            score = Integer.parseInt(
                Files.readString(Paths.get(FILE_NAME)).trim()
            );
        }

        // Simulate a delay to make synchronization observable.
        Thread.sleep(200);

        score++;

        Files.writeString(Paths.get(FILE_NAME), score + "\n");

        System.out.println(name + " updated score to " + score);
    }

    public static void main(String[] args) throws Exception {
        ExecutorService pool = Executors.newCachedThreadPool();
        ServerSocket server = new ServerSocket(PORT);

        System.out.println("Java synchronized server running on port " + PORT);

        while (true) {
            Socket client = server.accept();

            pool.execute(() -> {
                try {
                    BufferedReader reader = new BufferedReader(
                        new InputStreamReader(client.getInputStream())
                    );

                    PrintWriter writer = new PrintWriter(
                        client.getOutputStream(), true
                    );

                    String name = reader.readLine();

                    updateScore(name);

                    writer.println("Score updated");
                    client.close();

                } catch (Exception e) {
                    e.printStackTrace();
                }
            });
        }
    }
}
