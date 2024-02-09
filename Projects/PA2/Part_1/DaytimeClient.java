/*
PA2

Claire Whittington
Peter Hilbert

*/

import java.io.*;
import java.net.Socket;
import java.io.DataInputStream;

public class DaytimeClient
    {
     static Socket socket;
     static String SERVER_HOST = "hwsrv-1126936.hostwindsdns.com";
     //static String SERVER_HOST = "time.nist.gov";
     static int PORT = 13;
     static char OTM = '*';

    public static void main(String[] args) throws IOException
        {
         Socket socket = new Socket(SERVER_HOST, PORT);
         DataInputStream fromServer = new DataInputStream(socket.getInputStream());

         System.out.println("Daytime Client");

         if (socket.isConnected())
            {
             System.out.println("Connected successfully to " + SERVER_HOST + " on port " + PORT);
            }
         else
            {
             System.out.println("Failed to connect to " + SERVER_HOST + " on port " + PORT);
            }

         // read first character of input
         byte inByte = readByteFromStream(fromServer);

         while (inByte != OTM)
            {
             // print read character
             System.out.print((char)inByte);

             // read the next character
             inByte = readByteFromStream(fromServer);
            }

         // print new line
         System.out.println();

         socket.close();
        }

      private static byte readByteFromStream(DataInputStream inputStream)
        {
         try
            {
             return inputStream.readByte();
            }
          catch (EOFException eofe)
            {
             return (byte)'\n';
            }
          catch (IOException ioe)
            {
             ioe.printStackTrace();
             return (byte)'\n';
            }
        }
    }
