import java.util.ArrayList;

import org.json.JSONObject;

public class User {
  private String username;
  private String password;
  private ArrayList<Ratings> givenRatings;
  private ArrayList<Badge> badges;
  private int experience;

  public User(String username, String password) {
    this.username = username;
    this.password = password;
    this.givenRatings = new ArrayList<Ratings>();
    this.badges = new ArrayList<Badge>();
    this.experience = 0;
  }

  public User(JSONObject json) {
    this.username = json.getString("username");
    this.password = json.getString("password");
    this.experience = json.getInt("experience");
    this.givenRatings = new ArrayList<Ratings>();
    for (int i = 0; i < json.getJSONArray("givenRatings").length(); i++) {
      this.givenRatings.add(new Ratings(json.getJSONArray("givenRatings").getJSONObject(i)));
    }
    this.badges = new ArrayList<Badge>();
    for (int i = 0; i < json.getJSONArray("badges").length(); i++) {
      this.badges.add(new Badge(json.getJSONArray("badges").getJSONObject(i)));
    }
  }

  public String getUsername() {
    return this.username;
  }

  public String getPassword() {
    return this.password;
  }

  public Badge[] getBadges() {
    return this.badges.toArray(new Badge[this.badges.size()]);
  }

  public Ratings[] getRatings() {
    return this.givenRatings.toArray(new Ratings[this.givenRatings.size()]);
  }

  public void addVote(Ratings vote) {
    this.givenRatings.add(vote);
    this.experience += 50;
    if(this.experience == 150) {
      this.badges.add(new Badge("Recensore"));
    }
    if(this.experience == 400) {
      this.badges.add(new Badge("Recensore esperto"));
    }
    if(this.experience == 600) {
      this.badges.add(new Badge("Contributore"));
    }
    if(this.experience == 1000) {
      this.badges.add(new Badge("Contributore esperto"));
    }
    if(this.experience == 1500) {
      this.badges.add(new Badge("Contributore super"));
    }

  }

  public JSONObject toJSON() {
    JSONObject json = new JSONObject();
    json.put("username", this.username);
    json.put("password", this.password);
    json.put("experience", this.experience);
    JSONObject[] givenRatings = new JSONObject[this.givenRatings.size()];
    for (int i = 0; i < this.givenRatings.size(); i++) {
      givenRatings[i] = this.givenRatings.get(i).toJSON();
    }
    json.put("givenRatings", givenRatings);
    JSONObject[] badges = new JSONObject[this.badges.size()];
    for (int i = 0; i < this.badges.size(); i++) {
      badges[i] = this.badges.get(i).toJSON();
    }
    json.put("badges", badges);
    return json;
  }

  @Override
  public String toString() {
    return this.toJSON().toString();
  }
}
