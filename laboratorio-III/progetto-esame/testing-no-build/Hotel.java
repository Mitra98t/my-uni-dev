import java.lang.reflect.Array;
import java.util.ArrayList;

import org.json.JSONObject;

public class Hotel {
  int id;
  String name;
  String description;
  String city;
  String phone;
  ArrayList<String> services;
  double rate;
  double cleaning;
  double position;
  double servicesRate;
  double quality;
  double localRanking;

  // constructor from json object
  public Hotel(JSONObject jsonObject) {
    id = jsonObject.getInt("id");
    this.name = jsonObject.getString("name");
    this.city = jsonObject.getString("city");
    this.phone = jsonObject.getString("phone");
    this.services = new ArrayList<String>();
    for (int i = 0; i < jsonObject.getJSONArray("services").length(); i++) {
      this.services.add(jsonObject.getJSONArray("services").getString(i));
    }
    this.description = jsonObject.getString("description");
    this.rate = jsonObject.getDouble("rate");
    JSONObject ratings = jsonObject.getJSONObject("ratings");
    this.cleaning = ratings.getDouble("cleaning");
    this.position = ratings.getDouble("position");
    this.servicesRate = ratings.getDouble("services");
    this.quality = ratings.getDouble("quality");
    if (jsonObject.has("localRanking"))
      this.localRanking = jsonObject.getDouble("localRanking");
    else
      this.localRanking = 0;
  }

  public String getName() {
    return name;
  }

  public String getCity() {
    return city;
  }

  public String getDescription() {
    return description;
  }

  // TODO get ratings

  public void setName(String name) {
    this.name = name;
  }

  public void setcity(String city) {
    this.city = city;
  }

  public void setDescription(String description) {
    this.description = description;
  }

  public void setPhone(String phone) {
    this.phone = phone;
  }

  public void setServices(ArrayList<String> services) {
    this.services = services;
  }

  public double getRate() {
    return rate;
  }

  public void setRate(double rate) {
    this.rate = rate;
  }

  public void setCleaning(double cleaning) {
    this.cleaning = cleaning;
  }

  public void setPosition(double position) {
    this.position = position;
  }

  public void setServicesRate(double servicesRate) {
    this.servicesRate = servicesRate;
  }

  public void setQuality(double quality) {
    this.quality = quality;
  }

  public void setLocalRanking(double localRanking) {
    this.localRanking = localRanking;
  }

  public double getLocalRanking() {
    return localRanking;
  }

  public JSONObject toJSON() {
    JSONObject json = new JSONObject();
    json.put("id", this.id);
    json.put("name", this.name);
    json.put("description", this.description);
    json.put("city", this.city);
    json.put("phone", this.phone);
    String[] services = new String[this.services.size()];
    for (int i = 0; i < this.services.size(); i++) {
      services[i] = this.services.get(i);
    }
    json.put("services", services);
    json.put("rate", this.rate);
    JSONObject ratings = new JSONObject();
    ratings.put("cleaning", this.cleaning);
    ratings.put("position", this.position);
    ratings.put("services", this.servicesRate);
    ratings.put("quality", this.quality);
    json.put("ratings", ratings);
    json.put("localRanking", this.localRanking);
    return json;
  }

  public String toString() {
    return "Name: " + this.name + "\nDescription: " + this.description + "\nCity: " + this.city + "\nPhone: "
        + this.phone + "\nservices: " + this.services + "\nRate: " + this.rate + "\nRatings:\nCleaning: "
        + this.cleaning + "\nPosition: " + this.position + "\nServices: " + this.servicesRate + "\nQuality: "
        + this.quality + "\nLocal Ranking: " + this.localRanking;
  }

}
