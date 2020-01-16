### 15.0
```
// implement java.lang.Runnable interface
class C implements Runnable
{
    public int count = 0;
    
    public void run()
    {
        System.out.println("Run start");
        try
        {
            while (count < 5)
            {
                Thread.sleep(50);
                System.out.println("In Run, count is " + count);
                count++;
            }
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
        System.out.println("Run end");
    }
}

public class Main {
    public static void main(String[] args) {
        C c = new C();
        Thread t = new Thread(c);
        t.start();
        
        while (c.count != 5)
        {
            try
            {
                System.out.println("In Main, count is " + c.count);
                Thread.sleep(25);
            }
            catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }
    }
}
```

```
// extending java.lang.Thread class
class C extends Thread
{
    public int count = 0;
    
    public void run()
    {
        System.out.println("Run start");
        try
        {
            while (count < 5)
            {
                Thread.sleep(50);
                System.out.println("In Run, count is " + count);
                count++;
            }
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
        System.out.println("Run end");
    }
}

public class Main {
    public static void main(String[] args) {
        C c = new C();
        c.start();
        
        while (c.count != 5)
        {
            try
            {
                System.out.println("In Main, count is " + c.count);
                Thread.sleep(25);
            }
            catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }
    }
}
```

* In C++, have your class overload operator()() instead of defining a run function, and then simply pass that to a new std::thread. Simpler, cleaner and more efficient
```
// A callable object 
class thread_obj { 
public: 
    void operator()(int x) 
    {
        // similar to interface Runnable from Java
    } 
}; 
  
int main() 
{ 
    thread th(thread_obj(), 3); 
    th.join(); 
    return 0; 
} 
```
> ref: https://www.geeksforgeeks.org/multithreading-in-cpp/

### 15.3
```
// simple simulation of the dining philosophers problem
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class chopstick
{
    public chopstick()
    {
        lock = new ReentrantLock();
    }
    
    public void pickUp()
    {
        lock.lock();
    }
    
    public void putDown()
    {
        lock.unlock();
    }
    
    private Lock lock;
}

class philosopher extends Thread
{
    public philosopher(chopstick le, chopstick ri)
    {
        this.le = le;
        this.ri = ri;
    }
    
    public void eat()
    {
        pickUp();
        chew();
        putDown();
    }
    
    public void chew() {}
    
    public void pickUp()
    {
        le.pickUp();
        ri.pickUp();
    }
    
    public void putDown()
    {
        ri.putDown();
        le.putDown();
    }

    public void run()
    {
        for (int i = 0; i < bites; i++)
        {
            System.out.println(i);
            eat();
        }
    }
    
    private int bites = 10;
    private chopstick le, ri;
}
```

```
// All or nothing
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class chopstick
{
    public chopstick()
    {
        lock = new ReentrantLock();
    }
    
    public boolean pickUp()
    {
        return lock.tryLock();
    }
    
    public void putDown()
    {
        lock.unlock();
    }
    
    private Lock lock;
}

class philosopher extends Thread
{
    public philosopher(chopstick le, chopstick ri)
    {
        this.le = le;
        this.ri = ri;
    }
    
    public void eat()
    {
        if (pickUp())
        {
            chew();
            putDown();
        }
    }
    
    public void chew() {}
    
    public boolean pickUp()
    {
        if (!le.pickUp())
        {
            return false;
        }
        
        if (!ri.pickUp())
        {
            le.putDown();
            return false;
        }
        
        return true;
    }
    
    public void putDown()
    {
        ri.putDown();
        le.putDown();
    }

    public void run()
    {
        for (int i = 0; i < bites; i++)
        {
            System.out.println(i);
            eat();
        }
    }
    
    private int bites = 10;
    private chopstick le, ri;
}
```

```
// Prioritized Chopsticks
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class chopstick
{
    public chopstick(int id)
    {
        this.id = id;
        lock = new ReentrantLock();
    }
    
    public void pickUp()
    {
        lock.lock();
    }
    
    public void putDown()
    {
        lock.unlock();
    }
    
    public int id;
    private Lock lock;
}

class philosopher extends Thread
{
    public philosopher(chopstick le, chopstick ri)
    {
        this.le = le;
        this.ri = ri;
    }
    
    public void eat()
    {
        pickUp();
        chew();
        putDown();
    }
    
    public void chew() {}
    
    public void pickUp()
    {
        if (le.id < ri.id)
        {
            le.pickUp();
            ri.pickUp();
        }
        else
        {
            ri.pickUp();
            le.pickUp();
        }
    }
    
    public void putDown()
    {
        if (le.id < ri.id)
        {
            ri.putDown();
            le.putDown();
        }
        else
        {
            le.putDown();
            ri.putDown(); 
        }
    }

    public void run()
    {
        for (int i = 0; i < bites; i++)
        {
            System.out.println(i);
            eat();
        }
    }
    
    private int bites = 10;
    private chopstick le, ri;
}
```

### 15.5
* Because we need to be very careful about thread safety, simple boolean flags won't do the job
* 1 thread is actually performing the lock, but different threads attempt to unlock the locks. This is not allowed(will raise an exception). A lock in Java is owned by the same thread which locked it.

```
class Foo
{
    public Foo()
    {
        s1 = new Semaphore(1);
        s2 = new Semaphore(1);
        try
        {
            s1.acquire();
            s2.acquire();
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
    }
    
    public void first()
    {
        System.out.println("first"); 
        s1.release();
    }
    
    public void second()
    {
        try
        {
            s1.acquire();
            s1.release();
            System.out.println("second");
            s2.release();
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
    }
    
    public void third()
    {
        try
        {
            s2.acquire();
            s2.release();
            System.out.println("third");
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }

    }
    
    private Semaphore s1;
    private Semaphore s2;
}
```

### 15.7
```
class Globals {
   public static int count = 1;
}

class A extends Thread
{
    public void run()
    {
        while (true)
        {
            synchronized(this) {
                if (Globals.count > 100) return;
            
                if (Globals.count % 3 != 0 && Globals.count % 5 != 0)
                {
                    System.out.println(Globals.count);
                    Globals.count++;
                }
            }
        }
    }
}

class B extends Thread
{
    public void run()
    {
        while (true)
        {
            synchronized(this) {
                if (Globals.count > 100) return;
                
                if (Globals.count % 3 == 0 && Globals.count % 5 != 0)
                {
                    System.out.println("Fizz");
                    Globals.count++;
                }
            }
        }
    }
}

class C extends Thread
{
    public void run()
    {
        while (true)
        {
            synchronized(this) {
                if (Globals.count > 100) return;
            
                if (Globals.count % 3 != 0 && Globals.count % 5 == 0)
                {
                    System.out.println("Buzz");
                    Globals.count++;
                }
            }
        }
    }
}

class D extends Thread
{
    public void run()
    {
        while (true)
        {
            synchronized(this) {
                if (Globals.count > 100) return;
            
                if (Globals.count % 3 == 0 && Globals.count % 5 == 0)
                {
                    System.out.println("FizzBuzz");
                    Globals.count++;
                }
            }
        }
    }
}
```
