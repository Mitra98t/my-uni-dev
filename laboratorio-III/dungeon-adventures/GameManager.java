public class GameManager {
  private Player player;
  private Monster monster;

  public GameManager() {
    this.player = new Player();
    this.monster = new Monster();
  }

  public int doTurn(int choice){
    if (choice == 1) {
      this.attackRound();
    } else if (choice == 2) {
      this.playerCure();
    } else if (choice == 3) {
      this.playerFlee();
      return -1;
    } else {
      System.out.println("Invalid choice");
    }
    return this.checkWinCondition();
  }

  public void attackRound() {
    monster.receiveDamage();
    player.receiveDamage();
  }

  public int checkWinCondition() {
    if (player.getHealth() <= 0) {
      System.out.println("You died");
      return -1;
    } else if (monster.getHealth() <= 0) {
      System.out.println("You won");
      return 1;
    } else {
      return 0;
    }
  }

  public void playerCure() {
    player.drinkPotion();
  }

  public void playerFlee() {

  }

  public String getGameState() {
    return "Player health: " + player.getHealth() + "\nMonster health: " + monster.getHealth() + "\nInventory: " + player.getInventory() + "\n";
  }


}
