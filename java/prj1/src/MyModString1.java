public class MyModString1 implements ModString{
    String s=null;

    public MyModString1(String s){
        this.s = s;
    }

    public int size(){
        return this.s.length();
    }

    public void update (char c, int num){
        if(num < 0 || num >= this.size())
            throw new IndexOutOfBoundsException();

        this.s=this.s.substring(0, num) + c + this.s.substring(num+1);
    }

    public void remove(int num){
        if(num < 0 || num >= this.size())
            throw new IndexOutOfBoundsException();

        this.s=this.s.substring(0, num)+this.s.substring(num+1);
    }

    public String toString(){
        return this.s;
    }

}