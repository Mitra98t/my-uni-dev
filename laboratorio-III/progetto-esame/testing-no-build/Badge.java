

import org.json.JSONObject;

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

  public Badge(JSONObject json) {
    this.title = json.getString("title");
    this.description = json.getString("description");
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

  public JSONObject toJSON() {
    JSONObject json = new JSONObject();
    json.put("title", this.title);
    json.put("description", this.description);
    return json;
  }

  @Override
  public String toString() {
    return "Title: " + this.title + (this.description.equals("") ? "" :  "\nDescription: " + this.description);
  }
  
}
