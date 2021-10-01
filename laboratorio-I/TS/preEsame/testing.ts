function filterGenerics<T>(a: T[], f: (x: T) => boolean): T[] {
    return a.filter(e => f(e))
}
console.log(filterGenerics<string>(['a', 'e', 'i', 'o', 'u'], x => x == 'a'))
console.log(filterGenerics<number>([1, 2, 3, 4, 5], x => x % 2 == 0))

function filterNumber(a: (string|number)[], f: (x: string | number) => boolean): (string|number)[] {
    return a.filter(e => f(e))
}
console.log(filterNumber([1,2,'a', 3], (x) => typeof x == 'number'))

function filterType<T>(a: T[], f: (x: T) => boolean): T[] {
    return a.filter(e => f(e))
}

console.log(filterType<number | string>([1,2,'a', 3], (x)=> typeof x == 'string')) 
console.log(filterType<boolean | string>(['a', false, 'b', 'c', true], (x)=> typeof x == 'boolean')) 
console.log(filterType<number | boolean>([1,2,true, 3], (x)=> typeof x == 'number')) 

class Ok <T> {
    val :T;
    constructor(n: T) {
        this.val = n
    }
    isOk(fun: (x:T)=> boolean): boolean {
        return (fun(this.val));
    }
}

let a = new Ok<number>(4)

console.log(a.isOk(x => x%2 == 0))

interface Car<T>{
    annoProd :number;
    marca :string
    trattoSpeciale :T
}

let toyota :Car<boolean> = {annoProd: 2006, marca: "toyota", trattoSpeciale: true}