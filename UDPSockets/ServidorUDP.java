package UDPSockets;

import java.io.*;
import java.net.*;

/*Program adapted by Joel Trejo*/
/* 24^th January  2017 */

class ServidorUDP
{
   public static void main(String args[]) throws Exception
      {
	        boolean lanzar=true;
            DatagramSocket serverSocket = new DatagramSocket(7777); //Create a New socket
            byte[] receiveData = new byte[1024]; //The size of the received data as type byte
            byte[] sendData = new byte[1024];    //The size of the sent data as type byte
            String sentence;
            while(lanzar)
               {
            	  sentence="";
            	  //This is the data received by the client socket
                  DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                  serverSocket.receive(receivePacket);
                  sentence = new String( receivePacket.getData(),0,receivePacket.getLength());
                  System.out.println("Mensaje :"+sentence);                  
                  if (sentence.contains("FIN") || sentence.contains("fin")){
                	  lanzar=false;
                	  System.out.println("Servidor Desconectado");
                  }
                  //Get the address and port of the client socket
                  InetAddress IPAddress = receivePacket.getAddress();
                  int port = receivePacket.getPort();
                  String capitalizedSentence = sentence.toUpperCase();
                  sendData = capitalizedSentence.getBytes();
                  DatagramPacket sendPacket =
                  new DatagramPacket(sendData, sendData.length, IPAddress, port);
                  serverSocket.send(sendPacket);
               }
      }
}