import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import java.lang.reflect.Type;

public class JSONParser {
  public static User getUserByUsername(String jsonPath, String username) {
    String data = JSONParser.readJSONFromFile(jsonPath);
    Gson gson = new Gson();
    Type userListType = new TypeToken<ArrayList<User>>() {
    }.getType();
    ArrayList<User> users = gson.fromJson(data, userListType);
    for (int i = 0; i < users.size(); i++) {
      User user = users.get(i);
      if (user.getUsername().equals(username)) {
        return user;
      }
    }
    return null;
  }

  public static void updateUser(String jsonPath, User user) {
    String data = JSONParser.readJSONFromFile(jsonPath);
    Gson gson = new Gson();
    Type userListType = new TypeToken<ArrayList<User>>() {
    }.getType();
    ArrayList<User> users = gson.fromJson(data, userListType);
    for (int i = 0; i < users.size(); i++) {
      User userFromJson = users.get(i);
      if (userFromJson.getUsername().equals(user.getUsername())) {
        users.set(i, user);
        JSONParser.writeJSONToFile(jsonPath, gson.toJson(users));
        return;
      }
    }
    users.add(user);
    JSONParser.writeJSONToFile(jsonPath, gson.toJson(users));
  }

  public static void updateHotel(String jsonPath, Hotel hotel) {
    Gson gson = new Gson();
    String data = JSONParser.readJSONFromFile(jsonPath);
    Type hotelListType = new TypeToken<ArrayList<Hotel>>() {
    }.getType();
    ArrayList<Hotel> hotels = gson.fromJson(data, hotelListType);
    for (int i = 0; i < hotels.size(); i++) {
      Hotel hotelJSON = hotels.get(i);
      if (hotelJSON.getName().equals(hotel.getName())
          && hotelJSON.getCity().equals(hotel.getCity())) {
        hotels.set(i, hotel);
        JSONParser.writeJSONToFile(jsonPath, gson.toJson(hotels));
        return;
      }
    }
  }

  synchronized public static Hotel getHotelByNameAndCity(String jsonPath, String name, String city) {
    Gson gson = new Gson();
    String json = JSONParser.readJSONFromFile(jsonPath);
    Type hotelListType = new TypeToken<ArrayList<Hotel>>() {
    }.getType();
    ArrayList<Hotel> hotels = gson.fromJson(json, hotelListType);
    for (int i = 0; i < hotels.size(); i++) {
      Hotel hotelJSON = hotels.get(i);
      if (hotelJSON.getName().equals(name) && hotelJSON.getCity().equals(city)) {
        return hotelJSON;
      }
    }
    return null;
  }

  public static ArrayList<Hotel> getAllHotelsByCity(String jsonPath, String city) {
    Gson gson = new Gson();
    String json = JSONParser.readJSONFromFile(jsonPath);
    Type hotelListType = new TypeToken<ArrayList<Hotel>>() {
    }.getType();
    ArrayList<Hotel> hotelsJSON = gson.fromJson(json, hotelListType);
    ArrayList<Hotel> hotels = new ArrayList<Hotel>();
    for (int i = 0; i < hotelsJSON.size(); i++) {
      Hotel hotelJSON = hotelsJSON.get(i);
      if (hotelJSON.getCity().equals(city)) {
        hotels.add(hotelJSON);
      }
    }
    return hotels;
  }

  private static String readJSONFromFile(String path) {
    try {
      FileInputStream fis = new FileInputStream(path);
      byte[] data = new byte[(int) fis.getChannel().size()];
      fis.read(data);
      fis.close();
      return new String(data, "UTF-8");
    } catch (Exception e) {
      System.out.println(e);
      return null;
    }
  }

  private static void writeJSONToFile(String path, String data) {
    BufferedWriter bw = null;
    try {
      bw = new BufferedWriter(new FileWriter(path));
      bw.write(data);
    } catch (IOException e) {
      System.out.println(e);
    } finally {
      if (bw != null) {
        try {
          bw.close();
        } catch (IOException e) {
          System.out.println(e);
        }
      }
    }
  }

  public static Hotel getBestHotel(String jsonPath) {
    Gson gson = new Gson();
    String json = JSONParser.readJSONFromFile(jsonPath);
    Type hotelListType = new TypeToken<ArrayList<Hotel>>() {
    }.getType();
    ArrayList<Hotel> hotelsJSON = null;
    hotelsJSON = gson.fromJson(json, hotelListType);
    Hotel bestHotel = null;
    double bestRanking = 0;
    for (int i = 0; i < hotelsJSON.size(); i++) {
      Hotel hotelJSON = hotelsJSON.get(i);
      if (hotelJSON.getLocalRanking() > bestRanking) {
        bestRanking = hotelJSON.getLocalRanking();
        bestHotel = hotelJSON;
      }
    }
    if (bestHotel == null) {
      return hotelsJSON.get(0);
    }
    return bestHotel;
  }

}
