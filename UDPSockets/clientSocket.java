package UDPSockets;

import java.io.*;
import java.net.*;

class clientSocket
{
   public static void main(String args[]) throws Exception
   {
	  //Leer el mensaje que se tiene que enviar
	   System.out.println("Introduzca un mensaje:");
      BufferedReader inFromUser =
         new BufferedReader(new InputStreamReader(System.in));
      DatagramSocket clientSocket = new DatagramSocket();
      //Get the address of the server socket
      InetAddress IPAddress = InetAddress.getByName("localhost");
      byte[] sendData = new byte[1024];
      byte[] receiveData = new byte[1024];
      String sentence = inFromUser.readLine();
      sendData = sentence.getBytes();
      DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 7777);
      //Send a Datagram to Server
      clientSocket.send(sendPacket);
      //Receive a Datagram from Server
      DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
      clientSocket.receive(receivePacket);
      String modifiedSentence = new String(receivePacket.getData(),0,receivePacket.getLength());
      System.out.println("FROM SERVER:" + modifiedSentence);
      clientSocket.close();
   }
}