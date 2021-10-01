function check(o, f){

    let res = {...o}
    for(k in res)
        if(typeof res[k] == 'string')
            res[k] = f(res[k])
    
    return res
}

let obj = {name: "nome", eta: 91, desc: "ciao come stai io sto molto bene"}
let objMod = check(obj, (x) => x + " added")

console.log(obj)
console.log(objMod)