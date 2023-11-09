import java.util.Random;

public class Potion {
  private double quantity;

  public Potion() {
    Random rand = new Random();
    this.quantity = rand.nextDouble() * (100-50)+50; // generates a random double between 0 and 100
    // round quantity
    this.quantity = Math.round(this.quantity * 100.0) / 100.0;
  }

  public double getQuantity() {
    return this.quantity;
  }

  public double drink() {
    Random rand = new Random();

    double quantityToDrink = rand.nextDouble() * (this.quantity - 10) + 10; // generates a random double between 10 and
                                                                            // the current quantity of the potion
    if (quantityToDrink > this.quantity)
      quantityToDrink = this.quantity;
    this.quantity -= quantityToDrink;
    return calculateHealthRegen(quantityToDrink);
  }

  private double calculateHealthRegen(double quantity) {
    double healthRegen = quantity * 0.8f; // 80% of the quantity
    // round healthRegen
    healthRegen = Math.round(healthRegen * 100.0) / 100.0;
    return healthRegen;
  }
}
