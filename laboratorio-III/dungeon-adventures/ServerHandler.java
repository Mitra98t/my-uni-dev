import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

import javax.swing.text.GapContent;

public class ServerHandler implements Runnable {
  private Socket clientSocket;
  private PrintWriter out;
  private BufferedReader in;

  public ServerHandler(Socket socket) {
    this.clientSocket = socket;
  }

  public void run() {
    try {
      out = new PrintWriter(clientSocket.getOutputStream(), true);
      in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

      int winCond = 0;
      String inputLine;
      GameManager game = new GameManager();
      out.println("Welcome to the game!");
      while (true) {
        System.out.println("game start");
        out.println(game.getGameState());
        out.println("What do you want to do?");
        out.println("1. Attack");
        out.println("2. Drink potion");
        out.println("3. Flee");
        out.println("player-choose-now");

        inputLine = in.readLine();
        System.out.println("waiting for userinput");
        System.out.println("Received message: " + inputLine + " from client " + clientSocket.getPort());

        if (inputLine.equals("exit")) {
          break;
        }

        if (this.isValidChoice(inputLine)) {
          winCond = game.doTurn(Integer.parseInt(inputLine));
          System.out.println("game state: " + game.getGameState());
        }

        if (winCond == 1) {
          out.println("You won");
          out.println("Play again? (y/n)");
          out.println("player-choose-now");
          inputLine = in.readLine();
          if (inputLine.equals("n"))
            break;
          game = new GameManager();
        } else if (winCond == -1) {
          out.println("player-lost");
          break;
        }
      }

      in.close();
      out.close();
      clientSocket.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  private boolean isValidChoice(String choice) {
    return choice.equals("1") || choice.equals("2") || choice.equals("3");
  }
}
