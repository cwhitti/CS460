import java.io.*;
import java.net.*;
import java.util.Scanner;


public class Client {
    
    String serverIP;
    int port;

    
    public Client(String serverIP, int port)
    {
        this.serverIP = serverIP;
        this.port = port;
    }
    
    
    int getResult(int number) throws IOException
    {
        int steps;
        
        Socket socket = null;
        
        DataInputStream fromServer = null;
        DataOutputStream toServer = null;
      
        try {
            // open socket to server
            socket = new Socket(serverIP, port);
            // opening streams to/from server
            fromServer = new DataInputStream(socket.getInputStream());                   
            toServer = new DataOutputStream(socket.getOutputStream());
        } catch (UnknownHostException e) {
            System.err.println("Don't know about host.");
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for the connection to localhost");
            System.exit(1);
        }

        // write number and read steps
        toServer.writeInt(number);
        steps = fromServer.readInt();       
        socket.close();
        
        return steps;
    }
    
    
    public static void main(String[] args) throws IOException {

        // fallback server information, if no command line args provided
        String hostIP = "127.0.0.1";
        int port = 23657;
        
        Scanner userInput = new Scanner(System.in);
        int number = 0, steps;
        
        // get command line args, if provided
        try {
            hostIP = args[0];
            port = Integer.parseInt(args[1]);            
        } catch (ArrayIndexOutOfBoundsException ex)
        {
            // use fallback info
            System.out.println("No command line args provided");
        }
        
        // new client
        Client client = new Client(hostIP, port);
        
        // get user input
        try {
            System.out.print("Enter number: ");
            number = Integer.parseInt(userInput.nextLine());
        } catch (NumberFormatException ex) {
        }

        // get result from server
        steps = client.getResult(number);

        // print result
        System.out.println("Number of steps: " + steps);
    }
}
