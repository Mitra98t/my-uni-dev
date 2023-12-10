import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import org.apache.commons.io.IOUtils;
import org.json.*;

public class JSONParser {
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
    jsonArray.put(user.toJSON());
    JSONParser.writeJSONToFile(jsonPath, jsonArray.toString());
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

  synchronized public static Hotel getHotelByNameAndCity(String jsonPath, String name, String city) {
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

  public static Hotel getBestHotel(String jsonPath) {
    String json = JSONParser.readJSONFromFile(jsonPath);
    JSONArray jsonArray = new JSONArray(json);
    Hotel bestHotel = null;
    double bestRanking = 0;
    for (int i = 0; i < jsonArray.length(); i++) {
      JSONObject hotelJSON = jsonArray.getJSONObject(i);
      if (hotelJSON.has("localRanking") && hotelJSON.getDouble("localRanking") > bestRanking) {
        bestRanking = hotelJSON.getDouble("localRanking");
        bestHotel = new Hotel(hotelJSON);
      }
    }
    if (bestHotel == null) {
      return new Hotel(jsonArray.getJSONObject(0));
    }
    return bestHotel;
  }

}
