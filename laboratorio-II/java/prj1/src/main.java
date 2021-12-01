class Main {
    public static void main(String[] args) {
        MyModString1 s1 = new MyModString1("Ciao come va?");

        try{

            System.out.println("Stringa inizio " + s1.toString());

            s1.update('e', 2);
            System.out.println("Stringa dopo: " + s1.toString());

            s1.remove(2);
            System.out.println("Stringa dopo Cancellazione: " + s1.toString());

        } catch(Exception e){
            System.out.println("Errore s1");
        }

        MyModString2 s2 = new MyModString2("Ciao come va?");

        try{

            System.out.println("Stringa inizio " + s2.toString());

            s2.update('e', 2);
            System.out.println("Stringa dopo: " + s2.toString());

            s2.remove(2);
            System.out.println("Stringa dopo Cancellazione: " + s2.toString());

        } catch(Exception e){
            System.out.println("Errore s2");
        }
    }
}