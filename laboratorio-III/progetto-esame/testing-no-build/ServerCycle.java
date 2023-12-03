import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;

enum State {
  HOME("Home"),
  HOMELOGGEDIN("HomeLoggedIn"),
  LOGIN("Login"),
  REGISTER("Register"),
  SEARCHHOTEL("SearchHotel"),
  SEARCHALLHOTELS("SearchAllHotels"),
  VOTEHOTEL("VoteHotel"),
  SHOWBADGES("ShowBadges"),
  LOGOUT("Logout"),
  NULL("Null"),
  EXIT("Exit");

  private String state;

  State(String state) {
    this.state = state;
  }

  public String getState() {
    return this.state;
  }

  public boolean isState(String state) {
    return this.state == state;
  }
}

public class ServerCycle implements Runnable {
  private Socket clientSocket;
  private PrintWriter out;
  private BufferedReader in;
  private State state;
  private State prevState;
  private User currentLoggedUser = null;

  public ServerCycle(Socket socket) {
    this.clientSocket = socket;
    this.state = State.HOME;
    this.prevState = State.NULL;
  }

  @Override
  public void run() {
    try {
      out = new PrintWriter(clientSocket.getOutputStream(), true);
      in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
      CliHandlerServer cliHandler = new CliHandlerServer(out, in);
      // usage loop
      while (state.getState() != "exit") {
        if (currentLoggedUser != null) {
          cliHandler.send("You are logged in as " + currentLoggedUser.getUsername());
        }
        switch (state) {
          case HOME:
            String[] options = { State.LOGIN.getState(), State.REGISTER.getState(), State.SEARCHHOTEL.getState(),
                State.SEARCHALLHOTELS.getState(), State.EXIT.getState() };
            String selection = options[cliHandler.selection(options)];
            advanceState(State.valueOf(selection.toUpperCase()));
            System.out.println("client selected: " + selection);
            cliHandler.send(selection);

            cliHandler.pause();
            break;
          case HOMELOGGEDIN:
            String[] options2 = { State.SEARCHHOTEL.getState(), State.SEARCHALLHOTELS.getState(),
                State.SHOWBADGES.getState(), State.VOTEHOTEL.getState(), State.LOGOUT.getState(),
                State.EXIT.getState() };
            String selection2 = options2[cliHandler.selection(options2)];
            State chosenState = State.valueOf(selection2.toUpperCase());
            System.out.println("chosen state: " + chosenState);
            advanceState(chosenState);
            System.out.println("client selected: " + selection2);
            cliHandler.send(selection2);

            cliHandler.pause();
            break;
          case LOGIN:
            String username = cliHandler.prompt("Enter your username: ");
            cliHandler.send("You entered " + username);
            String password = cliHandler.prompt("Enter your password: ");
            cliHandler.send("You entered " + password);
            System.out.println("client username: " + username);
            System.out.println("client password: " + password);
            User userToCheck = JSONParser.getUserByUsername("resources/Users.json", username);
            System.out.println("userToCheck: " + userToCheck);
            if (userToCheck != null && userToCheck.getPassword().equals(password)) {
              currentLoggedUser = userToCheck;
            }
            if (currentLoggedUser == null) {
              cliHandler.send("Wrong username or password.");
              advanceState(State.HOME);
            } else {
              cliHandler.send("You have been logged in.");
              advanceState(State.HOMELOGGEDIN);
            }
            cliHandler.pause();
            break;
          case REGISTER:
            String username2 = cliHandler.prompt("Enter your username: ");
            cliHandler.send("You entered " + username2);
            String password2 = cliHandler.prompt("Enter your password: ");
            cliHandler.send("You entered " + password2);
            System.out.println("client username: " + username2);
            System.out.println("client password: " + password2);
            User userToRegister = new User(username2, password2);
            boolean registerResult = JSONParser.registerUser("resources/Users.json", userToRegister);
            if (registerResult) {
              cliHandler.send("You have been registered.");
            } else {
              cliHandler.send("Username already taken.");
            }
            advanceState(State.HOME);
            cliHandler.pause();
            break;
          case SEARCHHOTEL:
            String hotelName = cliHandler.prompt("Enter the name of the hotel you want to search for: ");
            cliHandler.send("You entered " + hotelName);
            String hotelCity = cliHandler.prompt("Enter the city of the hotel you want to search for: ");
            cliHandler.send("You entered " + hotelCity);
            Hotel hotelToSearch = JSONParser.getHotelByNameAndCity("resources/Hotels.json", hotelName, hotelCity);
            if (hotelToSearch == null) {
              cliHandler.send("Hotel not found.");
              returnToPreviousState();
              break;
            }
            cliHandler.send(hotelToSearch.toString());
            System.out.println("client hotelName: " + hotelName);
            cliHandler.pause();
            returnToPreviousState();
            break;
          case SEARCHALLHOTELS:
            String cityToSearch = cliHandler.prompt("Enter the city of the hotel you want to search for: ");
            ArrayList<Hotel> hotels = JSONParser.getAllHotelsByCity("resources/Hotels.json", cityToSearch);
            hotels.sort((h1, h2) -> h1.getLocalRanking() > h2.getLocalRanking() ? 1 : -1);
            for (int i = 0; i < hotels.size(); i++) {
              cliHandler.send(hotels.get(i).toString());
              cliHandler.send("---");
            }
            cliHandler.pause();
            returnToPreviousState();
            break;
          case VOTEHOTEL:
            String hotelToVote = cliHandler.prompt("Enter the name of the hotel you want to vote for:");
            cliHandler.send("You entered " + hotelToVote);
            String hotelCityToVote = cliHandler.prompt("Enter the city of the hotel you want to vote for:");
            cliHandler.send("You entered " + hotelCityToVote);
            Hotel hotelToVoteFor = JSONParser.getHotelByNameAndCity("resources/Hotels.json", hotelToVote,
                hotelCityToVote);
            if (hotelToVoteFor == null) {
              cliHandler.send("Hotel not found.");
              returnToPreviousState();
              break;
            }
            double rate = cliHandler.voting("Vote your experience with " + hotelToVoteFor.getName() + ":");
            double clean = cliHandler.voting("Vote the cleanliness of " + hotelToVoteFor.getName() + ":");
            double service = cliHandler.voting("Vote the service of " + hotelToVoteFor.getName() + ":");
            double location = cliHandler.voting("Vote the location of " + hotelToVoteFor.getName() + ":");
            double quality = cliHandler.voting("Vote the price to quality ratio of " + hotelToVoteFor.getName() + ":");
            currentLoggedUser.addVote(new Ratings(hotelToVoteFor.getName() + " - " + hotelToVoteFor.getCity(), rate,
                clean, service, location, quality));
            JSONParser.updateUser("resources/Users.json", currentLoggedUser);
            JSONParser.calculateHotelRating("resources/Users.json", "resources/Hotels.json", hotelToVoteFor);
            cliHandler.send("Thank you for your vote!");
            returnToPreviousState();
            break;
          case SHOWBADGES:
            cliHandler.send("Badges of " + currentLoggedUser.getUsername() + ":");
            Badge[] badges = currentLoggedUser.getBadges();
            for (int i = 0; i < badges.length; i++) {
              cliHandler.send(badges[i].toString());
            }
            cliHandler.pause();
            returnToPreviousState();
            break;
          case LOGOUT:
            currentLoggedUser = null;
            cliHandler.send("You have been logged out.");
            cliHandler.pause();
            advanceState(State.HOME);
            break;
          default:
            advanceState(State.EXIT);
            break;
        }
      }

      out.println("exit-now");

      in.close();
      out.close();
      clientSocket.close();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  private void advanceState(State newState) {
    this.prevState = this.state;
    this.state = newState;
  }

  private void returnToPreviousState() {
    this.state = this.prevState;
    this.prevState = State.NULL;
  }

}
