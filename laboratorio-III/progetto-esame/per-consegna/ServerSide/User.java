import java.util.ArrayList;

import com.google.gson.Gson;

public class User {
  private String username;
  private String password;
  private ArrayList<Badge> badges;
  private int experience;

  public User(String username, String password) {
    this.username = username;
    this.password = password;
    this.badges = new ArrayList<Badge>();
    this.experience = 0;
  }

  public User(String json) {
    Gson gson = new Gson();
    User user = gson.fromJson(json, User.class);
    this.username = user.username;
    this.password = user.password;
    this.badges = user.badges;
    this.experience = user.experience;
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

  public int getExperience() {
    return this.experience;
  }

  public void addExperience(int experience) {
    this.experience += experience;
    this.addBadge(this.experience);
  }

  public void addBadge(int totalExp) {
    if (totalExp == 100) {
      this.badges.add(new Badge("Recensore", "I primi passi!"));
    }
    if (totalExp == 300) {
      this.badges.add(new Badge("Recensore Esperto", "Che traguardo!"));
    }
    if (totalExp == 500) {
      this.badges.add(new Badge("Contributore", "Senza di te non siamo niente!"));
    }
    if (totalExp == 700) {
      this.badges.add(new Badge("Contributore Esperto", "Diventi inestimabile!"));
    }
    if (totalExp == 1000) {
      this.badges.add(new Badge("Contributore Super", "Sei il migliore!"));
    }
  }

  public String toJSON() {
    // JSONObject json = new JSONObject();
    // json.put("username", this.username);
    // json.put("password", this.password);
    // json.put("experience", this.experience);
    // JSONObject[] badges = new JSONObject[this.badges.size()];
    // for (int i = 0; i < this.badges.size(); i++) {
    // badges[i] = this.badges.get(i).toJSON();
    // }
    // json.put("badges", badges);
    // return json;
    Gson gson = new Gson();
    return gson.toJson(this);
  }

  @Override
  public String toString() {
    return "Username: " + this.username + "\nPassword: " + this.password + "\nExperience: " + this.experience
        + "\nBadges: " + this.badges.toString();
  }
}
