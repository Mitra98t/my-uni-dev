import org.json.JSONArray;
import org.json.JSONObject;

public class ServerSaver implements Runnable {

  @Override
  public void run() {
    save();
  }

  public static void save() {
    ServerCache cache = ServerCache.getInstance();
    try {
      for (Hotel hotel : cache.getAllHotels()) {
        JSONParser.updateHotel("./resources/Hotels.json", hotel);
      }
      for (User user : cache.getAllUsers()) {
        JSONParser.updateUser("./resources/Users.json", user);
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

}
