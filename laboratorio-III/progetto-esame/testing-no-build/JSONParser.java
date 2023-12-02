import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import org.apache.commons.io.IOUtils;
import org.json.*;

public class JSONParser {
  // parse the JSON file and return an array of Hotel objects
  public static Hotel[] parseHotels(String jsonPath) {
    String json = JSONParser.readJSONFromFile(jsonPath);
    JSONArray jsonArray = new JSONArray(json);
    Hotel[] hotels = new Hotel[jsonArray.length()];

    for (int i = 0; i < jsonArray.length(); i++) {
      JSONObject jsonObject = jsonArray.getJSONObject(i);
      hotels[i] = new Hotel(jsonObject);
    }

    return hotels;
  }

  public static User getUserByUsername(String jsonPath, String username) {
    String data = JSONParser.readJSONFromFile(jsonPath);
    JSONArray jsonArray = new JSONArray(data);
    for (int i = 0; i < jsonArray.length(); i++) {
      JSONObject userJSON = jsonArray.getJSONObject(i);
      if (userJSON.getString("username").equals(username)) {
        return new User(userJSON);
      }
    }
    return null;
  }

  public static boolean registerUser(String jsonPath, User user) {
    String data = JSONParser.readJSONFromFile(jsonPath);
    JSONArray jsonArray = new JSONArray(data);
    for (int i = 0; i < jsonArray.length(); i++) {
      JSONObject userJSON = jsonArray.getJSONObject(i);
      if (userJSON.getString("username").equals(user.getUsername())) {
        return false;
      }
    }
    jsonArray.put(user.toJSON());
    JSONParser.writeJSONToFile(jsonPath, jsonArray.toString());
    return true;
    
  }

  public static void updateUser(String jsonPath, User user) {
    String data = JSONParser.readJSONFromFile(jsonPath);
    JSONArray jsonArray = new JSONArray(data);
    for (int i = 0; i < jsonArray.length(); i++) {
      JSONObject userJSON = jsonArray.getJSONObject(i);
      if (userJSON.getString("username").equals(user.getUsername())) {
        jsonArray.put(i, user.toJSON());
        JSONParser.writeJSONToFile(jsonPath, jsonArray.toString());
        return;
      }
    }
  }

  public static User[] getAllUsers(String jsonPath) {
    String data = JSONParser.readJSONFromFile(jsonPath);
    JSONArray jsonArray = new JSONArray(data);
    User[] users = new User[jsonArray.length()];
    for (int i = 0; i < jsonArray.length(); i++) {
      JSONObject userJSON = jsonArray.getJSONObject(i);
      users[i] = new User(userJSON);
    }
    return users;
  }

  public static void calculateHotelRating(String userJsonPath, String hotelJsonPath, Hotel hotelToUpdate) {
    User[] userList = JSONParser.getAllUsers(userJsonPath);
    double rate = 0;
    double cleaning = 0;
    double position = 0;
    double services = 0;
    double quality = 0;
    ArrayList<Ratings> allRatings = new ArrayList<Ratings>();

    for (int i = 0; i < userList.length; i++) {
      Ratings[] ratings = userList[i].getRatings();
      for (int j = 0; j < ratings.length; j++) {
        if (ratings[j].getTargetHotel().equals(hotelToUpdate.getName() + " - " + hotelToUpdate.getCity())) {
          rate += ratings[j].getRate();
          cleaning += ratings[j].getClean();
          position += ratings[j].getPosition();
          services += ratings[j].getServices();
          quality += ratings[j].getQuality();
          allRatings.add(ratings[j]);
        }
      }
    }

    rate /= allRatings.size();
    cleaning /= allRatings.size();
    position /= allRatings.size();
    services /= allRatings.size();
    quality /= allRatings.size();

    rate = Math.round(rate * 100.0) / 100.0;
    cleaning = Math.round(cleaning * 100.0) / 100.0;
    position = Math.round(position * 100.0) / 100.0;
    services = Math.round(services * 100.0) / 100.0;
    quality = Math.round(quality * 100.0) / 100.0;

    hotelToUpdate.setRate(rate);
    hotelToUpdate.setCleaning(cleaning);
    hotelToUpdate.setPosition(position);
    hotelToUpdate.setServicesRate(services);
    hotelToUpdate.setQuality(quality);

    allRatings.sort((a, b) -> b.getDate().compareTo(a.getDate()));

    System.out.println("most recent vote: " + allRatings.get(0));
    System.out.println("time evaluation local ranking: " + (System.currentTimeMillis() - allRatings.get(0).getDate().getTime()) / 1000); // seconds

    double localRanking = allRatings.size() - ((System.currentTimeMillis() - allRatings.get(0).getDate().getTime()) / 1000 / 10) + hotelToUpdate.getRate();
    localRanking = Math.round(localRanking * 100.0) / 100.0;
    hotelToUpdate.setLocalRanking(localRanking);


    JSONParser.updateHotel(hotelJsonPath, hotelToUpdate);
  }

  public static void updateHotel(String jsonPath, Hotel hotel) {
    String data = JSONParser.readJSONFromFile(jsonPath);
    JSONArray jsonArray = new JSONArray(data);
    for (int i = 0; i < jsonArray.length(); i++) {
      JSONObject hotelJSON = jsonArray.getJSONObject(i);
      if (hotelJSON.getString("name").equals(hotel.getName())
          && hotelJSON.getString("city").equals(hotel.getCity())) {
        jsonArray.put(i, hotel.toJSON());
        JSONParser.writeJSONToFile(jsonPath, jsonArray.toString());
        return;
      }
    }
  }

  public static Hotel getHotelByNameAndCity(String jsonPath, String name, String city) {
    String json = JSONParser.readJSONFromFile(jsonPath);
    JSONArray jsonArray = new JSONArray(json);
    for (int i = 0; i < jsonArray.length(); i++) {
      JSONObject hotelJSON = jsonArray.getJSONObject(i);
      if (hotelJSON.getString("name").equals(name) && hotelJSON.getString("city").equals(city)) {
        return new Hotel(hotelJSON);
      }
    }
    return null;
  }

  public static ArrayList<Hotel> getAllHotelsByCity(String jsonPath, String city) {
    String json = JSONParser.readJSONFromFile(jsonPath);
    JSONArray jsonArray = new JSONArray(json);
    ArrayList<Hotel> hotels = new ArrayList<Hotel>();
    for (int i = 0; i < jsonArray.length(); i++) {
      JSONObject hotelJSON = jsonArray.getJSONObject(i);
      if (hotelJSON.getString("city").equals(city)) {
        hotels.add(new Hotel(hotelJSON));
      }
    }
    return hotels;
  }

  private static String readJSONFromFile(String path) {
    try {
      FileInputStream fis = new FileInputStream(path);
      String data = IOUtils.toString(fis, "UTF-8");
      return data;
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

}
