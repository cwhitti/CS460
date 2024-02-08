import java.io.IOException;
import java.net.Socket;
import java.io.InputStream;

public class DaytimeClient 
    {
     static Socket socket;
     static String SERVER_HOST = "time.nist.gov";
     static int PORT = 13;
     static char OTM = '*';

    public static void main(String[] args) throws IOException
        {
         Socket socket = new Socket(SERVER_HOST, PORT);
         
         if (socket.isConnected())
            {
             System.out.println("Connected successfully to " + SERVER_HOST + " on port " + PORT);
             socket.close();
            }
         else
            {
             System.out.println("Failed to connect to " + SERVER_HOST + " on port " + PORT);
            }
        }
    }
