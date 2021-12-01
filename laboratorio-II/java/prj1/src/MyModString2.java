public class MyModString2 implements ModString{

    private char[] chars;
    private int dim;

    public MyModString2(String s){
        this.dim = s.length();
        this.chars = s.toCharArray();
    }

    public int size(){
        return dim;
    }

    public void update (char c, int num){
        if(num < 0 || num >= this.size())
            throw new IndexOutOfBoundsException();
        chars[num] = c;
    }

    public void remove(int num){
        if(num < 0 || num >= this.size())
            throw new IndexOutOfBoundsException();
        for( int i = num; i < dim-1; i++){
            this.chars[i] = this.chars[i+1];
        }
        dim--;
    }

    public String toString(){
        return new String(this.chars, 0, this.dim);
    }
}