import com.google.gson.Gson;

public class HotelRating {
  // "ratings": {
  // "cleaning": 0,
  // "position": 0,
  // "services": 0,
  // "quality": 0
  // }
  private double cleaning;
  private double position;
  private double services;
  private double quality;

  public HotelRating(double cleaning, double position, double services, double quality) {
    this.cleaning = cleaning;
    this.position = position;
    this.services = services;
    this.quality = quality;
  }

  public double getCleaning() {
    return this.cleaning;
  }

  public double getPosition() {
    return this.position;
  }

  public double getServices() {
    return this.services;
  }

  public double getQuality() {
    return this.quality;
  }

  public void setCleaning(double cleaning) {
    this.cleaning = cleaning;
  }

  public void setPosition(double position) {
    this.position = position;
  }

  public void setServices(double services) {
    this.services = services;
  }

  public void setQuality(double quality) {
    this.quality = quality;
  }

  @Override
  public String toString() {
    return "{" +
        " cleaning='" + getCleaning() + "'" +
        ", position='" + getPosition() + "'" +
        ", services='" + getServices() + "'" +
        ", quality='" + getQuality() + "'" +
        "}";
  }

  public String toJson() {
    Gson gson = new Gson();
    return gson.toJson(this);
  }
}
