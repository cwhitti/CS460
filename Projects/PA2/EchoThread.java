
import java.io.*;
import java.net.Socket;

// objects of this class work on one request
class EchoThread implements Runnable {

    Socket client;
    DataInputStream fromClient;
    DataOutputStream toClient;
    int charFromClient;
    int state = 0;

    // output streams to destination web server and requesting client
    EchoThread(Socket client) {
        this.client = client;
    }

    @Override
    public void run() {
        
        // first get the streams
        try {
            this.fromClient = new DataInputStream (client.getInputStream ());
            this.toClient   = new DataOutputStream(client.getOutputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }

        // now talk to the client
        while (true) {
            try {
                charFromClient = fromClient.readByte();
            } catch (IOException e) {
                e.printStackTrace();
            }

            // only echo back letters
            if (charFromClient >= 'a' && charFromClient <= 'z' || charFromClient >= 'A' && charFromClient <= 'Z') {
                try {
                    toClient.writeByte(charFromClient);
                } catch (IOException e) {
                    e.printStackTrace();
                }

                // primitive state machine to keep track of the word 'quit', upon reception of which we bail out
                switch (charFromClient) {
                    case 'q':
                        state = 1;
                        break;
                        
                    case 'u':
                        if (state == 1) state++;
                        break;
                        
                    case 'i':
                        if (state == 2) state++;
                        break;
                        
                    case 't':
                        if (state == 3) state++;
                        break;
                        
                    default:
                        state = 0;
                }
                
                /*
                switch (state) {
                    case 0:
                        state = (charFromClient == 'q') ? 1 : 0;
                        break;
                
                    case 1:
                        state = (charFromClient == 'u') ? 2 : 0;
                        break;
                
                    case 2:
                        state = (charFromClient == 'i') ? 3 : 0;
                        break;
                
                    case 3:
                        state = (charFromClient == 't') ? 4 : 0;
                        break;
                }
                */
                
                if (state == 4) {
                    System.out.println("Bailing out!");
                    break;
                }
            }
        }

        try {
            client.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
