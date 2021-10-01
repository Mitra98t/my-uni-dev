// function filterMio1(a) {
//     let sol = [];
//     for (i = 0; i < a.length; i++) {
//         if (a[i] % 2 == 0) {
//             sol.push(a[i]);
//         }
//     }
//     return sol;
// }

// function filterMio2(a, fun) {
//     let sol = [];
//     for (i = 0; i < a.length; i++) {
//         if (fun(a[i])) {
//             sol.push(a[i]);
//         }
//     }
//     return sol
// }

// function filterF(a, fun) {
//     return a.filter(e => fun(e))
// }

// function mapM(a, fun) {
//     return a.map(e => fun(e));
// }

// function mapMio(a, fun) {
//     let b=[];
//     for(i=0;i<a.length;i++) {
//         b.push(fun(a[i]));
//     }
//     return b;
// }

// console.log(mapMio([1, 2, 3, 4, 5, 6, 7, 8, 9], (x) => x*2))

/*
Classe con attrbiuti: val (numero)
metodi:
isOk(fun) restituisce booleano valutando val in fun
*/

// class Ok1 {
//     constructor (n) {
//         this.val = n;
//     }
//     isOk(fun) {
//         if (fun(this.val) == true) {
//             return true;
//         }
//         else return false;
//     }
// }

// let a = new Ok1(7);
// console.log(a.isOk(x => x%2 == 0));

class Ok2 {
    constructor (n) {
        if (n < 0) {
            this.val = 0;
        }
        else this.val = n;
    }
    isOk(fun) {
        if (fun(this.val) == true) {
            return true;
        }
        else return false;
    }
    fancyPrint(fun){
        console.log("il risultato è " + this.isOk(fun))
    }
}

// let t = new Ok2 (-44);
// console.log(t)
// console.log(t.isOk(x=> x%2 == 0));

class ZeroException extends Error{
    
}

class NotOk extends Ok2{
    constructor(n,m) {
        super(n);

        if(m == 0)
            throw new ZeroException("0 non è ammesso")
        
        this.valson = m;
    }
    isNotOk() {
        return (this.valson == this.val) ? true : false
    }
}

let k
try{
    k = new NotOk(4, 0)
}
catch(e){
    console.error(e)
    k = new NotOk(4, 1)
}

console.log(k)
console.log(k.isNotOk())