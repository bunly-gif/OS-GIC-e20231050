import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class PoolDemo {
    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(2);

        System.out.println("Submitting 6 tasks to a pool of 2 threads...");

        for (int i = 1; i <= 6; i++) {
            final int taskId = i;

            executor.submit(() -> {
                System.out.println("Task " + taskId +
                    " started by " + Thread.currentThread().getName());

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    System.out.println("Task " + taskId + " interrupted.");
                    return;
                }

                System.out.println("Task " + taskId + " completed.");
            });
        }

        executor.shutdown();

        try {
            if (!executor.awaitTermination(30, TimeUnit.SECONDS)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
            Thread.currentThread().interrupt();
        }

        System.out.println("All tasks completed.");
    }
}
