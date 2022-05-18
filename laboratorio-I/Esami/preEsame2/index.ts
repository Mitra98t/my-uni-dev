// function findRow<T>(m :T[][], e :T):number[]{
//     let cont :number = 0
//     let res :number[] = []
//     for(let i = 0; i < m.length; i++){
//         for(let j = 0; j < m[i].length; j++){
//             if(m[i][j] == e){
//                 cont ++
//                 if(cont >= 3){
//                     res.push(i)
//                     break
//                 }
//             }
//             else
//                 cont = 0
//         }
//         cont = 0
//     }

//     return res;
// }

// let sMat = [
//     ['a', 'a', 'b', 'd'],
//     ['a', 'a', 'a', 'a'],
//     ['c', 'a', 'a', 'a'],
// ]
// let char = 'a'

// console.log(findRow<string>(sMat, char))

// let nMat = [
//     [0, 0, 0, 4, 5],
//     [1, 2, 0, 4, 5],
//     [1, 0, 0, 4, 0],
//     [1, 2, 3, 4, 5],
//     [1, 0, 0, 0, 0],
// ]
// let val = 0

// console.log(findRow<number>(nMat, val))


// function findRC<T>(m :T[][], e :T):{}{
//     let contR :number = 0
//     let contC :number = 0
//     let res = {row: [], col: []}
//     for(let i = 0; i < m.length; i++){
//         for(let j = 0; j < m[i].length; j++){
//             if(m[i][j] == e){
//                 contR ++
//             }
//             else{
//                 contR = 0
//             }
//             if(m[j][i] == e){
//                 contC ++
//             }
//             else{
//                 contC = 0
//             }
//             if(contR >= 3 && !res.row.includes(i)){
//                 res.row.push(i)
//             }
//             if(contC >= 3 && !res.col.includes(j)){
//                 res.col.push(j)
//             }
//         }
//         contR = 0
//         contC = 0
//     }
//     return res;
// }

// console.log(findRC<number>(nMat, val))

// interface Person {
//     nome: string;
//     cognome: string;
//     eta: number;
//     gender: boolean;
// }
// interface PersonC extends Person{
//     partner:(x:Person)=>string;
// }

// class Marito implements PersonC {
//     nome: string;
//     cognome: string;
//     eta: number;
//     gender: boolean;
//     constructor(nome: string, cognome: string, eta: number, gender: boolean) {
//         this.nome = nome;
//         this.cognome = cognome;
//         this.eta = eta;
//         this.gender = gender;
//     }
//     partner(perro: Person): string {
//         return `Ecco una bellissima persona ${perro.gender}`;
//     }
// }


// function contaVocali(s: string):number{
//     const re :RegExp= /[aeiou]/gm
//     return  s.length > 0 ? (s.match(/[aeiou]/gm) || []).length : 0
// }

// function contaVocaliOne(s:string):number{ return s.length > 0 ? (s.match(/[aeiou]/gm) || []).length : 0 }

// console.log(contaVocaliOne('ciao come va?'))
// console.log(contaVocali('Io sto molto bene'))

// class Matrix {
//     matrix :number[][];
//     constructor(r:number, c:number){
//         this.matrix = []
//         for(let i = 0; i<r; i++){
//             this.matrix[i] = []
//             for(let j = 0; j<c; j++){
//                 this.matrix[i][j] = 0
//             }
//         }
//     }

//     moltiplicazione(m:Matrix):Matrix{
//         let matrix = new Matrix()
//         for(let i = 0; i<r; i++){
//             matrix[i] = []
//             for(let j = 0; j<c; j++){
//                 matrix[i][j] = m[i][j] * this.matrix[i][j]
//             }
//         }
//         return matrix
//     }
// }

function sommaArray<T>(a: T[], somma:(x:T, y:T) => T):T{
    return a.reduce(somma)
}

console.log(sommaArray<number>([1,2,3,4,5], (x, y) => x+y))