import java.util.Random;

public abstract class Entity {
  public double health;

  public Entity() {
    Random rand = new Random();
    this.health = rand.nextDouble() * (20 - 10) + 10; // generates a random float between 10 and 20
    //round healt
    this.health = Math.round(this.health * 100.0) / 100.0;
  }

  public double receiveDamage() {
    Random rand = new Random();
    double damage = rand.nextDouble() * (this.health-3)+3;
    //round damage
    damage = Math.round(damage * 100.0) / 100.0;
    this.health -= damage;
    return damage;
  }

  public double getHealth() {
    return this.health;
  }

  public boolean isDead() {
    return this.health <= 0;
  }

  
}
