import org.json.JSONObject;

public class Hotel {
  String name;
  String location;
  String description;
  Ratings ratings;
  Double localRanking;

  public Hotel(String name, String location, String description, Ratings ratings, Double localRanking) {
    this.name = name;
    this.location = location;
    this.description = description;
    this.ratings = ratings;
    this.localRanking = localRanking;
  }

  public Hotel (String name, String location, String description, double syntheticRating, double position, double clean, double service, double priceQuality, Double localRanking) {
    this.name = name;
    this.location = location;
    this.description = description;
    this.ratings = new Ratings(syntheticRating, position, clean, service, priceQuality);
    this.localRanking = localRanking;
  }

  // constructor from json object
  public Hotel(JSONObject jsonObject) {
    this.name = jsonObject.getString("name");
    this.location = jsonObject.getString("location");
    this.description = jsonObject.getString("description");
    JSONObject specRat = jsonObject.getJSONObject("specificRatings");
    this.ratings = new Ratings(jsonObject.getDouble("syntheticRating"), specRat.getDouble("position"), specRat.getDouble("clean"), specRat.getDouble("service"), specRat.getDouble("priceQuality"));
    this.localRanking = jsonObject.getDouble("localRanking");
  }

  public String getName() {
    return name;
  }

  public String getLocation() {
    return location;
  }

  public String getDescription() {
    return description;
  }

  public Ratings getRatings() {
    return ratings;
  }

  public void setName(String name) {
    this.name = name;
  }

  public void setLocation(String location) {
    this.location = location;
  }

  public void setDescription(String description) {
    this.description = description;
  }

  public void setRatings(Ratings ratings) {
    this.ratings = ratings;
  }

  public void setRatings(double synthetic, double position, double clean, double service, double priceQuality) {
    this.ratings = new Ratings(synthetic, position, clean, service, priceQuality);
  }

  public String toString() {
    return "Name: " + name + "\nLocation: " + location + "\nDescription: " + description + "\nRatings: " + ratings;
  }

  public boolean equals(Hotel hotel) {
    return this.name.equals(hotel.name) && this.location.equals(hotel.location) && this.description.equals(hotel.description) && this.ratings.equals(hotel.ratings);
  }


}
