import java.util.ArrayList;

import org.json.JSONArray;
import org.json.JSONObject;

public class Hotel {
  int id;
  String name;
  String description;
  String city;
  String phone;
  ArrayList<String> services;
  ArrayList<Ratings> ratingList;
  double rate;
  double cleaning;
  double position;
  double servicesRate;
  double quality;
  double localRanking;

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

    this.ratingList = new ArrayList<Ratings>();
    if (jsonObject.has("ratingList")) {
      for (int i = 0; i < jsonObject.getJSONArray("ratingList").length(); i++) {
        this.ratingList.add(new Ratings(jsonObject.getJSONArray("ratingList").getJSONObject(i)));
      }
    }
  }

  public String getName() {
    return this.name;
  }

  public String getCity() {
    return this.city;
  }

  public double getLocalRanking() {
    return this.localRanking;
  }

  public String getPhone() {
    return this.phone;
  }

  public ArrayList<String> getServices() {
    return this.services;
  }

  public double getRate() {
    return this.rate;
  }

  public double getCleaning() {
    return this.cleaning;
  }

  public double getPosition() {
    return this.position;
  }

  public double getServicesRate() {
    return this.servicesRate;
  }

  public double getQuality() {
    return this.quality;
  }

  public ArrayList<Ratings> getRatingList() {
    return this.ratingList;
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

  public void addRating(Ratings rating) {
    this.ratingList.add(rating);
  }

  public void addService(String service) {
    this.services.add(service);
  }

  public void addVote(Ratings rating) {
    this.ratingList.add(rating);
  }

  public void calculateRatings() {
    double rate = 0;
    double cleaning = 0;
    double position = 0;
    double services = 0;
    double quality = 0;
    for (int i = 0; i < this.ratingList.size(); i++) {
      rate += this.ratingList.get(i).getRate();
      cleaning += this.ratingList.get(i).getClean();
      position += this.ratingList.get(i).getPosition();
      services += this.ratingList.get(i).getServices();
      quality += this.ratingList.get(i).getQuality();
    }
    rate /= this.ratingList.size();
    cleaning /= this.ratingList.size();
    position /= this.ratingList.size();
    services /= this.ratingList.size();
    quality /= this.ratingList.size();
    rate = Math.round(rate * 100.0) / 100.0;
    cleaning = Math.round(cleaning * 100.0) / 100.0;
    position = Math.round(position * 100.0) / 100.0;
    services = Math.round(services * 100.0) / 100.0;
    quality = Math.round(quality * 100.0) / 100.0;
    this.rate = rate;
    this.cleaning = cleaning;
    this.position = position;
    this.servicesRate = services;
    this.quality = quality;

    this.ratingList.sort((a, b) -> b.getDate().compareTo(a.getDate()));
    long oldestRating = this.ratingList.get(this.ratingList.size() - 1).getDate().getTime();

    double localRanking = (this.getRate() * 2) * (this.ratingList.size() / 10.0);
    if (this.ratingList.size() >= 2) {
      double normalized = Hotel.normalizeValue(this.ratingList.get(1).getDate().getTime(), oldestRating,
          System.currentTimeMillis());
      localRanking *= (normalized + 1) * 10;
    }
    localRanking = Math.round(localRanking * 100.0) / 100.0;
    this.setLocalRanking(localRanking);
    ServerCache.getInstance().updateHotel(this);
  }

  public boolean equals(Hotel hotel) {
    return this.name.equals(hotel.getName()) && this.city.equals(hotel.getCity());
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
    JSONArray ratingList = new JSONArray();
    for (int i = 0; i < this.ratingList.size(); i++) {
      ratingList.put(this.ratingList.get(i).toJSON());
    }
    json.put("ratingList", ratingList);
    json.put("localRanking", this.localRanking);
    return json;
  }

  public String toString() {
    return "Name: " + this.name + "\nDescription: " + this.description + "\nCity: " + this.city + "\nPhone: "
        + this.phone + "\nservices: " + this.services + "\nRate: " + this.rate + "\nRatings:\nCleaning: "
        + this.cleaning + "\nPosition: " + this.position + "\nServices: " + this.servicesRate + "\nQuality: "
        + this.quality + "\nLocal Ranking: " + this.localRanking;
  }

  private static double normalizeValue(long value, long minValue, long maxValue) {
    return Double.parseDouble(String.valueOf((value - minValue) / (maxValue - minValue)));
  }

}
