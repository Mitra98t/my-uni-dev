const { performance } = require('perf_hooks');
/*Si scriva una funzione extend(a,b) che, dati due oggetti a e b, restituisca un nuovo oggetto che ha tutte le proprietà di a e tutte
quelle di b. Se a e b hanno qualche proprietà con lo stesso nome, prevale il valore contenuto in b.*/
// function extend(a, b) {
//     let gigi = { ...a }
//     for (k in b) {
//         gigi[k] = b[k];
//     }
//     return gigi
// }
// // console.log(extend({nome: 'federico', cognome: 'miraglia'}, {cognome: 'valente', eta: 19}))

// function extendF(a, b) {
//     let gigi = { ...a }
//     for (k in b) {
//         if (!gigi.hasOwnProperty(k))
//             gigi[k] = b[k];
//     }
//     return gigi
// }
// console.log(extendF({nome: 'federico', cognome: 'miraglia'}, {cognome: 'valente', eta: 19}))

// function floydS(i) {
//     let res = [1]
//     if (i == 0) {
//         return res
//     }

//     let tmp = []
//     for (let k = 0; k < i; k++) {
//         tmp.push(res[res.length - 1] + 1)
//         for (let j = 0; j <= k; j++) {
//             tmp.push(tmp[j] + 1)
//         }
//         res = tmp.slice(0)
//         tmp = []
//     }
//     return res
// }

// function floydF(i) {
//     let start = 0
//     let res = []
//     for (let z = 1; z <= i; z++) {
//         start += z
//     }

//     for (let z = 1; z < i + 2; z++) {
//         res.push(start + z)
//     }
//     return res
// }

// function moda(a) {
//     let obj = {}
//     let max = 0
//     let val = 0
//     for (e of a) {
//         if (obj.hasOwnProperty(e))
//             obj[e]++
//         else
//             obj[e] = 1
//     }


//     for(k in obj)
//         if(obj[k] >= val){
//             max = k
//             val = obj[k]
//         }

//         return max
// }
// let array = [1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 5, 6, 6, 6, 6, 6, 6, 7, 8, 8, 8, 8, 9, 9, 9, 9]
// console.log(moda(array))

// function first(a, f) {
//     let arr = a.map(x => f(x))
//     return (z) => arr.map(x => x + z)
// }

// console.log(first([1, 2, 3, 4, 5], (x) => 2 * x)(3))


// let array = [1, 2, 3, 4, 5]
// let reduced = array.reduce((a, b)=> a+b)
// let reduced2 = array.reduce((a,b) => a+b, 3)

// console.log(reduced)
// console.log(reduced2)

// class Coda {
//     constructor(arr){
//         if(!arr || arr.length <= 0)
//             throw new Error("Coda non fornita")

//         this.arr = arr
//     }

//     queue(v){
//         this.arr.push(v)
//         return this.arr
//     }

//     dequeue(){
//         return this.arr.shift()
//     }

//     print(){
//         console.log(this.arr)
//     }
// }

// class CodaFiglio extends Coda{
//     constructor(arr){
//         super(arr)
//     }
// }

// let coda = new Coda([1])
// let codaFiglio = new CodaFiglio([3])

// console.log(coda instanceof CodaFiglio)
// console.log(codaFiglio instanceof Coda)

// function sommaFoglie(t){
//     if(t == undefined)
//         return 0

//     if(t.sx == undefined && t.dx==undefined)
//         return t.val
//     else{
//         return 0 + sommaFoglie(t.sx) + sommaFoglie(t.dx)
//     }
// }

// let obj = {val:7,sx:{val: 4, sx: {val: 3}, dx: {val:12, sx: {val: 4, dx:{val:3}, sx:{val: 8}}}}, dx:{val: 11, dx: {val: 3}, sx: {val:8, sx: {val: 6}}}}
// console.log(sommaFoglie(obj))

// function findLonger(a) {
//     let res = {}
//     let lengths = a.map(x => x.length)
//     let max = lengths.reduce((a, b) => { return Math.max(a, b) })
//     let index = lengths.indexOf(max)
//     res[a[index]] = max
//     return res
// }

// let array = ['spray', 'limit', 'elite', 'exuberant', 'destruction', 'present']
// console.log(findLonger(array))


// function maxOccur(a) {
//     let obj = {}
//     for (e of a) {
//         if (!obj.hasOwnProperty(e))
//             obj[e] = 0
//         else
//             obj[e]++
//     }

//     let max = { key: 0, occur: 0 }
//     for (k in obj) {
//         if (max.occur < obj[k]) {
//             max.key = k
//             max.occur = obj[k]
//         }
//     }
//     return max.key
// }

// let array = [1, 1, 2, 2, 2, 2, 2, 5, 6, 6, 6, 3, 3, 3, 3, 3, 4]
// console.log(maxOccur(array))

// function* getElement(a) {
//     for(i = 0; i < a.length; i++){
//         yield a[i]
//     }
// }

// let array = [1, 2, 3, 4, 5]
// const iterator = getElement(array)

// console.log(iterator.next().value)
// console.log(iterator.next().value)
// console.log(iterator.next().value)
// console.log(iterator.next().value)
// console.log(iterator.next().value)
// console.log(iterator.next().value)

// let array = [1, 2, 3, 4, 5]
// function onlyDispari(a, f){
//     let res = a.slice(0)
//     for(let i = 0; i < res.length; i++){
//         if(i%2 != 0)
//             res[i] = f(res[i])
//     }
//     return res
// }

// console.log(onlyDispari(array, x => 2*x))

// function torreDiControllo(a){
//     return a.sort((a, b) => a.car - b.car)
// }

// let aerei = [{car: 15}, {car:89}, {car:9}, {car:51}]
// console.log(torreDiControllo(aerei))

// function f(f, arr){
//     return (x) =>{
//         let res = []
//         for(e of arr){
//             if(f(e) == x)
//                 res.push(e)
//         }
//         return res
//     }
// }
// function f1(f, arr){
//     return (x) => arr.filter(e => f(e) == x) 
// }

// console.log(f((x) => 2*x, [1,1,2,3,1,3])(5))
// console.log(f1((x) => 2*x, [1,1,2,3,1,3])(8))

function isEssen(m) {
    let inf = true
    for (let i = 2; i < m.length; i++) {
        for (let j = 0; j < i-1; j++) {
            console.log(m[i][j])
            if (m[i][j] != 0) {
                inf = false
                break
            }
        }
    }

    let sup = true
    for (let i = 2; i < m.length; i++) {
        for (let j = 0; j < i-1; j++) {
            console.log(m[j][i])
            if (m[j][i] != 0) {
                sup = false
                break
            }
        }
    }

    return inf || sup
}


let m = [
    [1, 2, 1, 3],
    [1, 2, 1, 5],
    [0, 2, 3, 2],
    [0, 0, 3, 2]
]
console.log(isEssen(m))
