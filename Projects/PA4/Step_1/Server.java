import java.io.*;
import java.net.*;
import java.util.*;


class Server {

    // where to print log
    static PrintStream log = null;

    // properties
    protected static Properties properties = new Properties();

    // takes idle worker threads
    static Vector<Thread> threads = new Vector<Thread>();

    // web servers port it is listening on
    static int port = 23657;

    // max # worker threads
    static int workers = 5;

    // default constructor
    Server() {}
        
    // print to stdout
    protected static void print(String s) {
        System.out.println(s);
    }

    // print to the log file
    static void log(String s) {
        synchronized (log) {
            log.println(s);
            log.flush();
        }
    }
    
    // load properties from directory config
    static void loadProps() throws IOException {
        String fileString = System.getProperty("user.dir") + File.separator + "config" + File.separator + "www-server.properties";
        File file = new File(fileString);
        
        if (file.exists()) {
            InputStream propertiesInputStream = new BufferedInputStream(new FileInputStream(file));
            properties.load(propertiesInputStream);
            propertiesInputStream.close();
            
            String propertyString = properties.getProperty("port");
            if (propertyString != null) {
                port = Integer.parseInt(propertyString);
            }

            propertyString = properties.getProperty("workers");
            if (propertyString != null) {
                workers = Integer.parseInt(propertyString);
            }

            propertyString = properties.getProperty("log");
            if (propertyString != null) {
                print("opening log file: " + propertyString);
                log = new PrintStream(new BufferedOutputStream(
                        new FileOutputStream(propertyString)));
            } else {
                log = System.out;                
            }
        }
    }

    static void printProps() {
        print("port=" + port);
        print("workers=" + workers);
    }
     
    synchronized void workerHasStarted() {
        notify();
    }

    synchronized void run() throws Exception {

        /* start worker threads */
        for (int i = 0; i < workers; ++i) {
            Worker worker = new Worker(this, "worker #" + i);
            wait();
            threads.addElement(worker);
        }


        ServerSocket ss = new ServerSocket(port);
        Worker worker = null;

        print("Start server loop");
        while (true) {

            Socket clientSocket = ss.accept();

            synchronized (threads) {
                if (threads.isEmpty()) {
                    worker = new Worker(this, "additional worker");
                    wait();
                    worker.setSocket(clientSocket);
                } else {
                    worker = (Worker) threads.elementAt(0);
                    threads.removeElementAt(0);
                    worker.setSocket(clientSocket);
                }
            }
        }

    }

    public static void main(String[] args) throws Exception {

        loadProps();
        printProps();

        (new Server()).run();

    }
}
