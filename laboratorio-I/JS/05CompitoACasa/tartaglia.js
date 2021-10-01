function TTFede(i) {
    let res = [1];
    let dec = i;
    for (let inc = 1; inc < i + 1; inc++) {
        res.push(res[inc - 1] * (dec / inc));
        dec--;
    }
    return res;
}

function TTOtt(i){
    let tmp = [1];
    let inc = 1; 
    let dec = i;
    let val = 0
    for (let c = 1; inc < Math.floor(i/2) + 1; c++) {
        val = (tmp[c - 1] * (dec / inc))
        tmp[c] = val;
        tmp[dec-1] = val;
        
        dec--;
        inc++;
    }

    tmp.push(1);
    return tmp;
}
/*
function TTOtt(i){
    let sx = [1];
    let dx = [1];
    let inc = 1; 
    let dec = i;
    let val = 0
    for (let c = 1; inc < Math.floor(i/2) + 1; c++) {
        val = (sx[c - 1] * (dec / inc));
        sx.push(val)
        dx.push(val)
        
        dec--;
        inc++;
    }

    if(i%2 == 0){
        dx.pop();
        dx.reverse();
        res = sx.concat(dx);
    }
    else{
        dx.reverse();
        res = sx.concat(dx);
    }

    return res;
}
*/
function TTMezz(i) {
    let tmp = [1];
    let res = [];
    let inc = 1; 
    let dec = i;

    for (let c = 1; inc < Math.floor(i/2) + 1; c++) {
        tmp.push(tmp[c - 1] * (dec / inc));
        dec--;
        inc++;
    }

    if(i%2 == 0){
        res = tmp.slice();
        tmp.pop()
        tmp.reverse()
        res = res.concat(tmp)
    }
    else{
        res = tmp.slice();
        tmp.reverse()
        res = res.concat(tmp)
    }

    return res;
}


let n = 100000000

console.time('original')
TTFede(n)
console.timeEnd('original')

console.time('Mezzo')
TTMezz(n)
console.timeEnd('Mezzo')

console.time('Ottimizzato')
TTOtt(n)
console.timeEnd('Ottimizzato')

