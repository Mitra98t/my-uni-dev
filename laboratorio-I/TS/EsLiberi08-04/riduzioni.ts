function redG<T>(a :T[], f :(a :T, b :T) => T) :T{
    let res :T = a[0];
    for (let i = 0; i < a.length; i++){
        res = f(a[i], res);
    }
    return res;
}

function redGReduce<T>(a :T[], f :(a :T, b :T) => T) :T{
    return a.reduce(f);
}

function minimo(x, y){
    if(x > y)
        return y
    else if(y > x)
        return x
    else
        return x
}

console.log(minimo(4, 19))
console.log(redG<number>([90,-20,1,4], minimo))
console.log(redG<string>(["p","qwer","pppp","azasa","i"], minimo))
console.log(redGReduce<number>([90,-20,1,4], minimo))
console.log(redGReduce<string>(["p","qwer","pppp","azasa","i"], minimo))