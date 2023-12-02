public class Ratings {
  private double synthetic;
  private double position;
  private double clean;
  private double service;
  private double priceQuality;

  public Ratings(double synthetic, double position, double clean, double service, double priceQuality) {
    if (synthetic < 0 || synthetic > 5 || position < 0 || position > 5 || clean < 0 || clean > 5 || service < 0
        || service > 5 || priceQuality < 0 || priceQuality > 5) {
      throw new IllegalArgumentException("All rating values must be between 0 and 5.");
    }
    this.synthetic = synthetic;
    this.position = position;
    this.clean = clean;
    this.service = service;
    this.priceQuality = priceQuality;
  }

  public double getSynthetic() {
    return synthetic;
  }

  public double getPosition() {
    return position;
  }

  public double getClean() {
    return clean;
  }

  public double getService() {
    return service;
  }

  public double getPriceQuality() {
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

  public String toString() {
    return "Synthetic: " + synthetic + "\nPosition: " + position + "\nClean: " + clean + "\nService: " + service
        + "\nPrice/Quality: " + priceQuality;
  }

}
