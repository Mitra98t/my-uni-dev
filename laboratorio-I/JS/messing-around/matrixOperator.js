class Matrix{
    constructor(m){
        this.matrix = m;
    }

    getRows(){
        return this.matrix.length;
    }

    getColumns(){
        return this.matrix[0].length;
    }

    multiplication(m){
        if(this.getColumns() != m.getRows())
            return -1;
        
        
    }
}


let mat = new MatOperations([[1,1,1],[2,2,2],[3,3,3]])

console.log(mat.getRows())
console.log(mat.getColumns())
console.log(mat.method(mat))