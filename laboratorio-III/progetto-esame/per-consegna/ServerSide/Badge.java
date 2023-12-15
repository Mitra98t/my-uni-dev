import com.google.gson.Gson;

public class Badge {
  private String title;
  private String description;

  public Badge(String title, String description) {
    this.title = title;
    this.description = description;
  }

  public Badge(String title) {
    this.title = title;
    this.description = "";
  }

  public String getTitle() {
    return this.title;
  }

  public String getDescription() {
    return this.description;
  }

  public void setTitle(String title) {
    this.title = title;
  }

  public void setDescription(String description) {
    this.description = description;
  }

  public String toJSON() {
    // JSONObject json = new JSONObject();
    // json.put("title", this.title);
    // json.put("description", this.description);
    // return json;
    Gson gson = new Gson();
    return gson.toJson(this);
  }

  @Override
  public String toString() {
    return "Title: " + this.title + (this.description.equals("") ? "" : "\nDescription: " + this.description);
  }

}
