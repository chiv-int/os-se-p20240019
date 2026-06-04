import java.util.concurrent.Semaphore;

class Account {
    String name;
    int balance;
    Semaphore lock = new Semaphore(1);

    Account(String name, int balance) {
        this.name = name;
        this.balance = balance;
    }
}

class Transfer {
    static void transfer(Account from, Account to, int amount) {
        try {
            System.out.println(Thread.currentThread().getName()
                    + " trying to lock FROM " + from.name);
            from.lock.acquire();
            System.out.println(Thread.currentThread().getName()
                    + " locked FROM " + from.name);

            Thread.sleep(100);

            System.out.println(Thread.currentThread().getName()
                    + " trying to lock TO " + to.name);
            to.lock.acquire();
            System.out.println(Thread.currentThread().getName()
                    + " locked TO " + to.name);

            from.balance -= amount;
            to.balance += amount;

            System.out.println(Thread.currentThread().getName()
                    + " transfer completed");

            to.lock.release();
            from.lock.release();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

public class DeadlockSimulation {
    public static void main(String[] args) throws InterruptedException {
        Account account1 = new Account("Account-A", 1000);
        Account account2 = new Account("Account-B", 1000);

        System.out.println("Starting balances:");
        System.out.println("Account-A: " + account1.balance);
        System.out.println("Account-B: " + account2.balance);
        System.out.println("Starting total: " + (account1.balance + account2.balance));
        System.out.println("---");

        Thread t1 = new Thread(() ->
                Transfer.transfer(account1, account2, 100),
                "Thread-1"
        );

        Thread t2 = new Thread(() ->
                Transfer.transfer(account2, account1, 200),
                "Thread-2"
        );

        t1.start();
        t2.start();

        // Watchdog - wait 3 seconds then check if still alive
        Thread.sleep(3000);

        if (t1.isAlive() || t2.isAlive()) {
            System.out.println("---");
            System.out.println("Deadlock detected: transactions are stuck");
            if (t1.isAlive()) {
                System.out.println("Thread-1 is waiting for Account-B");
            }
            if (t2.isAlive()) {
                System.out.println("Thread-2 is waiting for Account-A");
            }
            System.out.println("Final Account-A: " + account1.balance);
            System.out.println("Final Account-B: " + account2.balance);
            System.exit(1);
        }
    }
}
