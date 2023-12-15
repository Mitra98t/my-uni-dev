import java.sql.Date;

import com.google.gson.Gson;

public class Ratings {
  private double synthetic;
  private double position;
  private double clean;
  private double service;
  private double priceQuality;
  private long msDate;
  private String username;

  public Ratings(double synthetic, double position, double clean, double service,
      double priceQuality, String username) {
    if (synthetic < 0 || synthetic > 5 || position < 0 || position > 5 || clean < 0 || clean > 5 || service < 0
        || service > 5 || priceQuality < 0 || priceQuality > 5) {
      throw new IllegalArgumentException("All rating values must be between 0 and 5.");
    }
    this.synthetic = synthetic;
    this.position = position;
    this.clean = clean;
    this.service = service;
    this.priceQuality = priceQuality;
    this.msDate = System.currentTimeMillis();
    this.username = username;
  }

  // construct from gson
  public Ratings(String json) {
    Gson gson = new Gson();
    Ratings ratings = gson.fromJson(json, Ratings.class);
    this.synthetic = ratings.synthetic;
    this.position = ratings.position;
    this.clean = ratings.clean;
    this.service = ratings.service;
    this.priceQuality = ratings.priceQuality;
    this.msDate = ratings.msDate;
    this.username = ratings.username;
  }

  public double getRate() {
    return synthetic;
  }

  public double getPosition() {
    return position;
  }

  public double getClean() {
    return clean;
  }

  public double getServices() {
    return service;
  }

  public double getQuality() {
    return priceQuality;
  }

  public void setSynthetic(double synthetic) {
    if (synthetic < 0 || synthetic > 5) {
      throw new IllegalArgumentException("Rating value must be between 0 and 5.");
    }
    this.synthetic = synthetic;
  }

  public void setPosition(double position) {
    if (position < 0 || position > 5) {
      throw new IllegalArgumentException("Rating value must be between 0 and 5.");
    }
    this.position = position;
  }

  public void setClean(double clean) {
    if (clean < 0 || clean > 5) {
      throw new IllegalArgumentException("Rating value must be between 0 and 5.");
    }
    this.clean = clean;
  }

  public void setService(double service) {
    if (service < 0 || service > 5) {
      throw new IllegalArgumentException("Rating value must be between 0 and 5.");
    }
    this.service = service;
  }

  public void setPriceQuality(double priceQuality) {
    if (priceQuality < 0 || priceQuality > 5) {
      throw new IllegalArgumentException("Rating value must be between 0 and 5.");
    }
    this.priceQuality = priceQuality;
  }

  public Date getDate() {
    return new Date(msDate);
  }

  public String toJSON() {
    // JSONObject json = new JSONObject();
    // json.put("rate", this.synthetic);
    // json.put("cleaning", this.position);
    // json.put("position", this.clean);
    // json.put("services", this.service);
    // json.put("quality", this.priceQuality);
    // json.put("date", this.date.getTime());
    // json.put("username", this.username);
    // return json;

    Gson gson = new Gson();
    return gson.toJson(this);
  }

  public String toString() {
    return "TimeStamp: " + new Date(msDate).getTime() + "\nRate: " + synthetic + "\nPosition: " + position + "\nClean: "
        + clean
        + "\nServices: " + service
        + "\nPrice/Quality: " + priceQuality;
  }

}
