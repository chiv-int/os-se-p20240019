import java.util.concurrent.Semaphore;

class Account2 {
    String name;
    int balance;

    Account2(String name, int balance) {
        this.name = name;
        this.balance = balance;
    }
}

public class DeadlockFixed {
    static Semaphore mutex = new Semaphore(1);

    static void transfer(Account2 from, Account2 to, int amount) {
        try {
            mutex.acquire();
            try {
                System.out.println(Thread.currentThread().getName()
                        + " transferring " + amount
                        + " from " + from.name + " to " + to.name);

                Thread.sleep(100);

                from.balance -= amount;
                to.balance += amount;

                System.out.println(Thread.currentThread().getName()
                        + " transfer completed. "
                        + from.name + ": " + from.balance
                        + ", " + to.name + ": " + to.balance);
            } finally {
                mutex.release();
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Account2 accountA = new Account2("Account-A", 1000);
        Account2 accountB = new Account2("Account-B", 1000);

        System.out.println("Starting balances:");
        System.out.println("Account-A: " + accountA.balance);
        System.out.println("Account-B: " + accountB.balance);
        System.out.println("Starting total: " + (accountA.balance + accountB.balance));
        System.out.println("---");

        Thread t1 = new Thread(() ->
                transfer(accountA, accountB, 100),
                "Thread-1"
        );

        Thread t2 = new Thread(() ->
                transfer(accountB, accountA, 200),
                "Thread-2"
        );

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        System.out.println("---");
        System.out.println("Final Account-A: " + accountA.balance);
        System.out.println("Final Account-B: " + accountB.balance);
        System.out.println("Final total: " + (accountA.balance + accountB.balance));
        System.out.println("No deadlock occurred");
    }
}
