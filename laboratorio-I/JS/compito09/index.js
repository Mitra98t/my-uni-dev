// function isSorted(a){
//     for(let i = 1; i < a.length; i++){
//         if(a[i-1]>=a[i])
//             return false

//     }

//     return true
// }

// console.log(isSorted([-21,-2,0,4,6,210]))
// console.log(isSorted([2,6,8,8,9,21]))
// console.log(isSorted([2,6,8,9,10,-42]))


// function arrayfy(f){
//     return (a) => {
//         let res = []
//         for(let e of a)
//             res.push(f(e))

//         return res
//     }
// }
// let a=[5,2,4]
// console.log(arrayfy(x=>0)(a))
// console.log(arrayfy(x=>2*x)(a))

// a="pippo".split("")

// console.log(arrayfy(c=>c=="p")(a))

// console.log(typeof arrayfy(x=>0))

// function extend(a, b) {
//     let res = {}

//     for (let k in a)
//         res[k] = a[k]

//     for (let k in b)
//         if(!res[k])
//             res[k] = b[k]


//     return res
// }

// let a= {nome: "pippo", età: 35}
// let b={nome: "andrea", altezza: 200}

// console.log(extend(a,b))
// console.log(extend(a,{}))
// console.log(extend({},{}))

// function deframmenta(a) {
//     let res = a.slice(0)
//     let coordToRemove = []
//     if(res[0] != res[1])
//         coordToRemove.push(0)

//     for (let i = 1; i < res.length; i++) {
//         if (res[i - 1] != res[i]) {
//             if (res[i] != res[i + 1]){
//                 coordToRemove.push(i)
//             }
//         }
//     }

//     for(let i = coordToRemove.length-1; i>=0; i--){
//         res.splice(coordToRemove[i], 1);
//     }

//     return res
// }
// let a = [0,0,0,0,0,1,0,1,1]
// console.log(deframmenta(a))
// console.log(deframmenta([1,1,2,3,3,3,2,2,4]))
// console.log(deframmenta([1,0]))

// function angolo(d){
//     let ore = d.getHours()
//     let angOre = 0
//     let min = d.getMinutes()
//     let angMin = 0
//     let sec = d.getSeconds()
//     let angSec = 0
//     console.log(ore + ":" + min + ":" + sec)

//     if(ore >= 12)
//         ore -= 12

//     angSec = Math.round(sec * 0.1)
//     angMin = (min * 6) + angSec
//     angOre = (ore * 30) + Math.round(min*0.5)

//     if(angOre > angMin){
//         return angOre-angMin
//     }
//     else if(angMin>angOre){
//         return angMin-angOre
//     }
//     else{
//         return 0
//     }

// }

// console.log(angolo(new Date("2021-04-23 14:00:00")))
// console.log(angolo(new Date("2021-04-23 14:15:15")))
// console.log(angolo(new Date("2021-04-23 6:50:50")))

// function produci(G,s){
//     let res = ""
//     for(l of s){
//         console.log(l)
//         if(G.hasOwnProperty(l)){
//             res+=G[l]
//         }
//         else{
//             res+=l
//         }
//     }
//     return res
// }
// function multip(G,s,k){
//     let res = ""
//     res = produci(G, s)
//     for(let i = 1; i< k; i++){
//         res = produci(G,res)
//     }
//     return res
// }

// let G= {A:"aAB", B:"bb", C:"33"}
// console.log(produci(G,"CAz"))
// console.log(produci(G,"BAH!"))
// console.log(multip(G,"CAz",3))

// function contali(C) {
//     function Check() {
//         if (this instanceof C) {
//             Burrito[Burrito.counterName]++;
//         }
//     }

//     Check.counterName = Symbol();
//     Check[C.counterName] = 0;
//     C.count = () => C[C.counterName];
//     return C
// }

// let a = new contali(Array)
// console.log(a)

// let a2 = contali(Array)

// var a = new a2()

// console.log(a)

// function arrayfy(f){
//     return x => x.map(e => f(e))
// }

// a=[5,2,4]
// console.log(arrayfy(x => 0)(a))
// console.log(arrayfy(x => 2*x)(a))

// a = "pippo".split("")
// console.log(arrayfy(c=>c=="p")(a))

// console.log(typeof arrayfy(x=>0))