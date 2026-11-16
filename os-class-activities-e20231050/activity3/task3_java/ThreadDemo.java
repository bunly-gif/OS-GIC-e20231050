class CounterThread extends Thread {
    private String threadName;

    public CounterThread(String name) {
        this.threadName = name;
    }

    public void run() {
        for (int i = 1; i <= 5; i++) {
            System.out.println(threadName + " - Count: " + i);

            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                System.out.println(threadName + " interrupted.");
            }
        }

        System.out.println(threadName + " finished.");
    }
}

public class ThreadDemo {
    public static void main(String[] args) {
        System.out.println("Main thread PID: " +
            ProcessHandle.current().pid());

        CounterThread t1 = new CounterThread("Alpha");
        CounterThread t2 = new CounterThread("Beta");
        CounterThread t3 = new CounterThread("Gamma");

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

        System.out.println("All threads completed.");
    }
}
