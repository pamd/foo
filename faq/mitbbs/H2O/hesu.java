// mitbbs: water molecule problem
// http://www.mitbbs.com/article_t/JobHunting/32331973.html
// Code by hesu, uses two blocking queues

import java.util.concurrent.LinkedBlockingQueue;

public class H2O {
    LinkedBlockingQueue<Thread> hQueue = new LinkedBlockingQueue<Thread>();
    LinkedBlockingQueue<Thread> oQueue = new LinkedBlockingQueue<Thread>();
    Object o = new Object();

    public void h() throws InterruptedException {
        hQueue.put(Thread.currentThread());
        synchronized (o){
            System.out.println(Thread.currentThread().getName() + ".h, 
notify");
            o.notify();
        }

        synchronized (this){
            System.out.println(Thread.currentThread().getName()+".h, going 
to wait");
            this.wait();
        }

    }

    public void o() throws InterruptedException {
        oQueue.put(Thread.currentThread());
        synchronized (o){
            System.out.println(Thread.currentThread().getName() + ".o, 
notify");
            o.notify();
        }

        synchronized (this){
            System.out.println(Thread.currentThread().getName()+".o, going 
to wait");
            this.wait();
        }
    }

    public String pop() throws InterruptedException {
        while(true){
            synchronized (o){
                o.wait();
            }
            if(hQueue.size() >= 2 && oQueue.size() >= 1){
                Thread h = hQueue.take();
                synchronized (h){
                    h.notify();
                }

                Thread h2 = hQueue.take();
                synchronized (h2){
                    h2.notify();
                }

                Thread o = oQueue.take();
                synchronized (o){
                    o.notify();
                }

                System.out.println("H2O");
            }
        }
    }

    class hThread implements Runnable{
        public void run(){
            try {
                h();
            } catch (InterruptedException e) {
                e.printStackTrace();  //To change body of catch statement 
		use File | Settings | File Templates.
		    }
        }
    }

    class oThread implements Runnable{
        public void run(){
            try {
                o();
            } catch (InterruptedException e) {
                e.printStackTrace();  //To change body of catch statement 
		use File | Settings | File Templates.
		    }
        }
    }

    class Monitor implements Runnable{
        public void run(){
            try {
                pop();
            } catch (InterruptedException e) {
                e.printStackTrace();  //To change body of catch statement 
		use File | Settings | File Templates.
		    }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        H2O t = new H2O();
        new Thread(t.new Monitor()).start();
        new Thread(t.new hThread()).start();
        new Thread(t.new hThread()).start();
        new Thread(t.new oThread()).start();
        new Thread(t.new hThread()).start();
        new Thread(t.new hThread()).start();
        new Thread(t.new oThread()).start();
        new Thread(t.new hThread()).start();
        new Thread(t.new oThread()).start();
    }
}
