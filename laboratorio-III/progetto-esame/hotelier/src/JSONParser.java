import org.json.*;

public class JSONParser {
  // parse the JSON file and return an array of Hotel objects
  public static Hotel[] parseHotels(String json) {
    JSONArray jsonArray = new JSONArray(json);
    Hotel[] hotels = new Hotel[jsonArray.length()];
    
    for (int i = 0; i < jsonArray.length(); i++) {
      JSONObject jsonObject = jsonArray.getJSONObject(i);
      hotels[i] = new Hotel(jsonObject);
    }
    
    return hotels;
  }
}
