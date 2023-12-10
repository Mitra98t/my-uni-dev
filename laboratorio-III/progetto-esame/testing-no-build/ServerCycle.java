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
    ServerCache cache = ServerCache.getInstance();
    try {
      out = new PrintWriter(clientSocket.getOutputStream(), true);
      in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
      CliHandlerServer cliHandler = new CliHandlerServer(out, in);
      // usage loop
      while (!state.isState("Exit")) {
        cliHandler.sendClearScreen();
        if (currentLoggedUser != null) {
          cliHandler.send("You are logged in as " + currentLoggedUser.getUsername() + "\n\n");
        }
        switch (state) {
          case HOME:
            homeState(cliHandler);
            break;
          case HOMELOGGEDIN:
            homeLoggedInState(cliHandler);
            break;
          case LOGIN:
            loginState(cache, cliHandler);
            break;
          case REGISTER:
            registerState(cache, cliHandler);
            break;
          case SEARCHHOTEL:
            searchHotelState(cache, cliHandler);
            break;
          case SEARCHALLHOTELS:
            searchAllHotelsState(cache, cliHandler);
            break;
          case VOTEHOTEL:
            voteHotelState(cache, cliHandler);
            break;
          case SHOWBADGES:
            showBadgesState(cliHandler);
            break;
          case LOGOUT:
            logoutState(cliHandler);
            break;
          default:
            advanceState(State.EXIT);
            break;
        }
      }

      ServerSaver.save();

      out.println("exit-now");

      in.close();
      out.close();
      clientSocket.close();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  private void logoutState(CliHandlerServer cliHandler) {
    currentLoggedUser = null;
    cliHandler.send("You have been logged out.");

    cliHandler.send("logout-now");

    cliHandler.pause();
    advanceState(State.HOME);
  }

  private void showBadgesState(CliHandlerServer cliHandler) {
    cliHandler.send("Badges of " + currentLoggedUser.getUsername() + ":\n");

    if (currentLoggedUser.getBadges().length == 0) {
      cliHandler.send("No badges yet.\nVote some hotels to get some badges!");
    }

    Badge[] badges = currentLoggedUser.getBadges();
    for (int i = 0; i < badges.length; i++) {
      cliHandler.send(badges[i].toString());
      cliHandler.send("---");
    }

    cliHandler.send("");
    cliHandler.pause();
    returnToPreviousState();
  }

  private void searchAllHotelsState(ServerCache cache, CliHandlerServer cliHandler) {
    String cityToSearch = cliHandler.prompt("Enter the city of the hotel you want to search for: ");

    ArrayList<Hotel> hotels = cache.getAllHotelsByCity(cityToSearch);

    hotels.sort((h1, h2) -> h1.getLocalRanking() > h2.getLocalRanking() ? 1 : -1);

    cliHandler.sendClearScreen();
    for (int i = 0; i < hotels.size(); i++) {
      cliHandler.send(hotels.get(i).toString());
      cliHandler.send("---");
    }

    cliHandler.pause();
    returnToPreviousState();
  }

  private void registerState(ServerCache cache, CliHandlerServer cliHandler) {
    String username2 = cliHandler.prompt("Enter your username: ");
    String password2 = cliHandler.passwordPrompt("Enter your password: ");

    User userToRegister = new User(username2, password2);

    boolean registerResult = cache.registerUser(userToRegister);
    if (registerResult) {
      cliHandler.send("You have been registered.");
    } else {
      cliHandler.send("Username already taken.");
    }

    advanceState(State.HOME);
    cliHandler.pause();
  }

  private void loginState(ServerCache cache, CliHandlerServer cliHandler) {
    String username = cliHandler.prompt("Enter your username: ");
    String password = cliHandler.passwordPrompt("Enter your password: ");

    User userToCheck = cache.getUserByUsername(username);
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

    cliHandler.send("login-now");
    cliHandler.pause();
  }

  private void homeLoggedInState(CliHandlerServer cliHandler) {
    String[] options2 = { State.SEARCHHOTEL.getState(), State.SEARCHALLHOTELS.getState(),
        State.SHOWBADGES.getState(), State.VOTEHOTEL.getState(), State.LOGOUT.getState(),
        State.EXIT.getState() };

    String selection2 = options2[cliHandler.selection(options2)];

    State chosenState = State.valueOf(selection2.toUpperCase());

    advanceState(chosenState);

    cliHandler.pause();
  }

  private void homeState(CliHandlerServer cliHandler) {
    String[] options = { State.LOGIN.getState(), State.REGISTER.getState(), State.SEARCHHOTEL.getState(),
        State.SEARCHALLHOTELS.getState(), State.EXIT.getState() };

    String selection = options[cliHandler.selection(options)];

    advanceState(State.valueOf(selection.toUpperCase()));

    cliHandler.pause();
  }

  private void voteHotelState(ServerCache cache, CliHandlerServer cliHandler) {
    String hotelToVote = cliHandler.prompt("Enter the name of the hotel you want to vote for:");
    String hotelCityToVote = cliHandler.prompt("Enter the city of the hotel you want to vote for:");

    Hotel hotelToVoteFor = cache.getHotelByNameAndCity(hotelToVote, hotelCityToVote);

    if (hotelToVoteFor == null) {
      cliHandler.send("Hotel not found.");
      returnToPreviousState();
      cliHandler.pause();
      return;
    }

    double rate = cliHandler.voting("Vote your experience with " + hotelToVoteFor.getName() + ":");

    double clean = cliHandler.voting("Vote the cleanliness of " + hotelToVoteFor.getName() + ":");

    double service = cliHandler.voting("Vote the service of " + hotelToVoteFor.getName() + ":");

    double location = cliHandler.voting("Vote the location of " + hotelToVoteFor.getName() + ":");

    double quality = cliHandler.voting("Vote the price to quality ratio of " + hotelToVoteFor.getName() + ":");

    hotelToVoteFor
        .addVote(new Ratings(rate, location, clean, service, quality, currentLoggedUser.getUsername()));

    hotelToVoteFor.calculateRatings();

    cache.updateHotel(hotelToVoteFor);

    currentLoggedUser.addExperience(50);
    cache.updateUser(currentLoggedUser);

    cliHandler.send("Thank you for your vote!");

    returnToPreviousState();
    cliHandler.pause();
  }

  private void searchHotelState(ServerCache cache, CliHandlerServer cliHandler) {
    String hotelName = cliHandler.prompt("Enter the name of the hotel you want to search for: ");
    String hotelCity = cliHandler.prompt("Enter the city of the hotel you want to search for: ");

    Hotel hotelToSearch = cache.getHotelByNameAndCity(hotelName, hotelCity);

    if (hotelToSearch == null) {
      cliHandler.send("Hotel not found.");
      returnToPreviousState();
      cliHandler.pause();
      return;
    }

    cliHandler.sendClearScreen();
    cliHandler.send(hotelToSearch.toString());

    cliHandler.pause();
    returnToPreviousState();
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
