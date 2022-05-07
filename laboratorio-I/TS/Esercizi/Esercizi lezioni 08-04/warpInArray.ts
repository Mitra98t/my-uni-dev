function wrapInArray<T>(v :T, f :(a :T) => T, p :number = 1) :Array<T>{
    let res :Array<T> = [];
    for (let i = 0; i < p; i++){
        res.push(f(v))
    }
    return res;
}

console.log(wrapInArray<number>(9, (x) => x + x, 15))