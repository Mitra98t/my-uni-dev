class Vector {
    constructor(coord){
        this.coord = coord;
    }

    somma(vet2) {
        if(this.coord.length != vet2.coord.length)
            return undefined;
        
        let res = [];
        for(let i = 0; i < this.coord.length; i++){
            res.push(this.coord[i] + vet2.coord[i])
        }
        return new Vector(res)
    }

    prodotto(vet2){
        if(this.coord.length != vet2.coord.length)
            return undefined;

        let res = 0;
        for(let i = 0; i < this.coord.length; i++){
            res += this.coord[i] * vet2.coord[i]
        }
        return res;
    }

    prodottoS(n){
        let res = [];
        for(let e of this.coord){
            res.push(e*n)
        }
        return new Vector(res)
    }
}

let a = new Vector([1,4,6])
let b = new Vector([5,2,3])
let c = new Vector([3,4,5,6])

console.log("SOMME")
console.log(a.somma(c))
console.log(a.somma(b))
console.log("PRODOTTI")
console.log(a.prodotto(c))
console.log(a.prodotto(b))
console.log("PRODOTTOS")
console.log(a.prodottoS(4))