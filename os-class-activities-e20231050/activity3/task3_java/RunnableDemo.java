class PrintTask implements Runnable {
    private String taskName;

    public PrintTask(String name) {
        this.taskName = name;
    }

    @Override
    public void run() {
        for (int i = 1; i <= 3; i++) {
            System.out.println(taskName + " - Step " + i);

            try {
                Thread.sleep(300);
            } catch (InterruptedException e) {
                System.out.println(taskName + " interrupted.");
            }
        }

        System.out.println(taskName + " completed.");
    }
}

public class RunnableDemo {
    public static void main(String[] args) {
        Thread t1 = new Thread(new PrintTask("Downloader"));
        Thread t2 = new Thread(new PrintTask("Processor"));
        Thread t3 = new Thread(new PrintTask("Uploader"));

        t1.start();
        t2.start();
        t3.start();

        try {
            t1.join();
            t2.join();
            t3.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted.");
        }

        System.out.println("All tasks completed.");
    }
}
