import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class ServerCache {
  private static ServerCache instance;
  private ArrayList<Hotel> hotels;
  private ArrayList<User> users;
  private ArrayList<String> completedCities;
  private Hotel bestHotel;

  private ServerCache() {
    // Costruttore privato per prevenire l'istanziazione diretta
    this.hotels = new ArrayList<Hotel>();
    this.users = new ArrayList<User>();
    this.completedCities = new ArrayList<String>();
    this.bestHotel = JSONParser.getBestHotel("./resources/Hotels.json");
  }

  public static synchronized ServerCache getInstance() {
    if (instance == null) {
      instance = new ServerCache();
    }
    return instance;
  }

  synchronized public User isUserPresent(String username) {
    for (User user : this.users) {
      if (user.getUsername().equals(username)) {
        return user;
      }
    }
    return null;
  }

  synchronized public User getUserByUsername(String username) {
    User userFound = this.isUserPresent(username);
    if (userFound == null)
      userFound = addUser(username);
    return userFound;
  }

  synchronized public User addUser(String username) {
    User userFound = this.isUserPresent(username);
    if (userFound != null)
      return userFound;
    userFound = JSONParser.getUserByUsername("./resources/Users.json", username);
    if (userFound == null)
      return null;
    this.users.add(userFound);
    return userFound;
  }

  synchronized public void updateUser(User user) {
    for (int i = 0; i < this.users.size(); i++) {
      if (this.users.get(i).getUsername().equals(user.getUsername())) {
        this.users.set(i, user);
        return;
      }
    }
  }

  synchronized public boolean registerUser(User user) {
    User userFound = this.getUserByUsername(user.getUsername());
    if (userFound != null)
      return false;
    this.users.add(user);
    return true;
  }

  public Hotel isHotelPresent(String name, String city) {
    for (Hotel hotel : this.hotels) {
      if (hotel.getName().equals(name) && hotel.getCity().equals(city)) {
        return hotel;
      }
    }
    return null;
  }

  synchronized public Hotel getHotelByNameAndCity(String name, String city) {
    Hotel hotelFound = this.isHotelPresent(name, city);
    if (hotelFound == null)
      hotelFound = addHotel(name, city);
    return hotelFound;
  }

  synchronized public Hotel addHotel(String name, String city) {
    Hotel hotelFound = this.isHotelPresent(name, city);
    if (hotelFound != null)
      return hotelFound;
    hotelFound = JSONParser.getHotelByNameAndCity("./resources/Hotels.json", name, city);
    if (hotelFound == null)
      return null;
    this.hotels.add(hotelFound);
    setBestHotel(hotelFound);
    return hotelFound;
  }

  synchronized public void addHotel(Hotel hotel) {
    Hotel hotelFound = this.isHotelPresent(hotel.getName(), hotel.getCity());
    if (hotelFound != null)
      return;
    this.hotels.add(hotel);
    setBestHotel(hotel);
  }

  synchronized public void updateHotel(Hotel hotel) {
    for (int i = 0; i < this.hotels.size(); i++) {
      if (this.hotels.get(i).getName().equals(hotel.getName())
          && this.hotels.get(i).getCity().equals(hotel.getCity())) {
        this.hotels.set(i, hotel);
        setBestHotel(hotel);
        return;
      }
    }
  }

  synchronized public ArrayList<Hotel> getAllHotelsByCity(String city) {
    if (this.completedCities.contains(city)) {
      ArrayList<Hotel> foundHotels = new ArrayList<Hotel>();
      for (Hotel hotel : this.hotels) {
        if (hotel.getCity().equals(city)) {
          foundHotels.add(hotel);
        }
      }
      return foundHotels;
    }
    ArrayList<Hotel> hotels = JSONParser.getAllHotelsByCity("./resources/Hotels.json", city);
    if (hotels == null)
      return null;

    for (Hotel hotel : hotels) {
      addHotel(hotel);
    }
    this.completedCities.add(city);
    return hotels;
  }

  synchronized public ArrayList<Hotel> getAllHotels() {
    return this.hotels;
  }

  synchronized public ArrayList<User> getAllUsers() {
    return this.users;
  }

  synchronized public Hotel getBestHotel() {
    return this.bestHotel;
  }

  synchronized public void setBestHotel(Hotel hotel) {
    System.out.println("Checking " + hotel.getName() + " " + hotel.getCity() + " " + hotel.getLocalRanking() + " vs "
        + this.bestHotel.getName() + " " + this.bestHotel.getCity() + " " + this.bestHotel.getLocalRanking());
    if (hotel.getLocalRanking() <= this.bestHotel.getLocalRanking())
      return;

    System.out.println("new hotel won");
    this.bestHotel = hotel;
    DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
    String message = "Il miglior hotel è ora " + hotel.getName() + " " + hotel.getCity() + " " + hotel.getLocalRanking()
        + "\nNotifica alle " + dateFormat.format(new Date(System.currentTimeMillis()));
    try {
      Server.broadcast(message);
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

}