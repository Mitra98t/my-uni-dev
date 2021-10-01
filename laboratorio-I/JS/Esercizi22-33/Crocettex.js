class TooSmallException extends Error{

}
class InvalidFormatException extends Error{
    
}
class BadContentException extends Error{
    
}

function crocette(a){

    if(a.length < 3 && a[0].length < 3)
        throw new TooSmallException("matrice piccola")

    a.forEach(x =>{
        if(x.length != a[0].length)
            throw new TooSmallException("matrice sbilenca")
    })

    function check(a, i, j){
        if(a[i-1][j] == 1 && a[i+1][j] == 1 && a[i][j-1] == 1 && a[i][j+1] == 1 && a[i-1][j-1] == 0 && a[i-1][j+1] == 0 && a[i+1][j-1] == 0 && a[i+1][j+1] == 0)
            return true;
        else
            return false;
    }

    let res = []

    for (let i = 1; i < a.length-1; i++){
        for (let j = 1; j < a[i].length-1; j++){
            if(a[i][j] != 1 && a[i][j] != 0){
                throw new BadContentException("matrice con contenuto errato")
            }
            if(a[i][j] == 1){
                if(check(a, i, j)){
                    res.push([j, i])
                }
            }
        }
    }

    return res
}

let A= [
    [ 1,0,0,1,1 ],
    [ 0,1,0,1,0 ],
    [ 1,1,1,1,1 ],
    [ 0,1,0,1,0 ],
    [ 1,1,1,1,1 ],
    [ 0,1,0,1,1 ]
]

console.log(crocette(A))