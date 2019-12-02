### 1.
Thread in java: java.lang.Thread
* main thread
* 


* implement java.lang.Runnable interface
```
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

* extending java.lang.Thread class
```
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
