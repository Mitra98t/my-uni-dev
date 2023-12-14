public class ServerSaver implements Runnable {

  @Override
  public void run() {
    save();
  }

  public static void save() {
    ServerCache cache = ServerCache.getInstance();
    try {
      for (Hotel hotel : cache.getAllHotels()) {
        JSONParser.updateHotel(ServerMain.getHotelsPath(), hotel);
      }
      for (User user : cache.getAllUsers()) {
        JSONParser.updateUser(ServerMain.getUsersPath(), user);
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

}
