
public class Player  extends Entity{
  private Potion potion;

  public Player() {
    super();
    this.potion = new Potion();
  }

  public double drinkPotion() {
    double healingValue = this.potion.drink();
    this.health += healingValue;
    return healingValue;
  }

  public String getInventory() {
    return "Potion quantity: " + this.potion.getQuantity();
  }
}
