function find<T>(a :T[], f :(a :T) => boolean) :number[]{
    let res :number[] = []
    for(let e in a){
        if(f(a[e]))
            res.push(Number(e));
    }
    return res
}

console.log(find<number>([0,1,2,3,4,5,6,7,8,9,10,11,12,13], (x) => x % 2 == 0))

function mapG<T>(a :T[], f:(a :T, b :T) => T, v :T) :T[]{
    let res :T[] = [];
    for(let e of a){
        res.push(f(e, v))
    }
    return res;
}

function square(v, v1) { return v * v + v1 }
console.log(mapG<number>([1,2,3,4],square,1))