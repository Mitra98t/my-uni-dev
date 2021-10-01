class AnyMatrix <T>{
    mat :T[][];
    r :number;
    c :number;
    constructor(v:T){
      this.mat = [];
      this.mat[0] = [];
  
      this.mat[0][0] = v;
      this.r = 1
      this.c = 1
    }
  
    setAll(dati :T[][]) :boolean{
      if(dati.length != this.r || dati[0].length != this.c)
        return false
  
      for(let i = 0; i < dati.length; i++){
        for(let j = 0; j < dati.length; j++){
          this.mat[i][j] = dati[i][j];
      }
      return true
    }
  
    transpose(){
      let res:AnyMatrix<T> = new AnyMatrix<T>(this.mat[0][0])

    }
  
    toString(): string {
      return `${this.r}x${this.c}:\n|${this.A.join("|\n|")}|`
    }
  }