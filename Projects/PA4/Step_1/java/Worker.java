import java.io.*;
import java.net.*;
import java.util.*;

class Worker extends Thread {

    /* Socket to client we're handling */
    private Socket socket;
    /* WebServer the worker works for */
    Server webServer;

    Worker(Server webServer, String name) {
        super(name);
        this.webServer = webServer;

        this.start();
    }

    synchronized void setSocket(Socket socket) {
        this.socket = socket;
        notify();
    }

    @Override
    public synchronized void run() {

        webServer.workerHasStarted();

        while (true) {
            /* nothing to do */
            try {
                wait();
            } catch (InterruptedException e) {
                /* should not happen */
                continue;
            }

            try {
                handleClient();
            } catch (Exception e) {
                e.printStackTrace();
            }
            /* go back in wait queue if there's fewer
             * than numHandler connections.
             */

            Vector pool = webServer.threads;
            synchronized (pool) {
                if (pool.size() >= webServer.workers) {
                    /* too many threads, exit this one */
                    return;
                } else {
                    pool.addElement(this);
                }
            }
        }
    }

    void handleClient() throws IOException {
        
        int number = 0, steps = 0;
        
        Server.print("started handle client ...");
        
        //BufferedReader fromClient = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        DataInputStream fromClient = new DataInputStream(socket.getInputStream());
        DataOutputStream toClient  = new DataOutputStream(socket.getOutputStream());

        //socket.setSoTimeout(webServer.timeout);
        //socket.setTcpNoDelay(true);
        
        // read number from client
        try {
            number = fromClient.readInt();
        } catch (IOException e) {
        }
        
        // compute the number of steps
        steps = three_a_plus_one(number);
        Server.print(number + "------->" + steps);
        
        // send steps back to client
        // read number from client
        try {
            toClient.writeInt(steps);
            //toClient.flush();
        } catch (IOException e) {
        }

        
        // close socket
        socket.close();
    }
    
    int three_a_plus_one(int input) {
        int counter = 0;
        int current = input;

        while (current != 1) {
            counter++;
            if ((current % 2) == 1) {
                current = (current * 3) + 1;
            } else {
                current >>= 1;
            }
        }
        return counter;
    }
}
