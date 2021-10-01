function crocette(a){

    function check(a, i, j){
        if(a[i-1][j] == 1 && a[i+1][j] == 1 && a[i][j-1] == 1 && a[i][j+1] == 1 && a[i-1][j-1] == 0 && a[i-1][j+1] == 0 && a[i+1][j-1] == 0 && a[i+1][j+1] == 0)
            return true;
        else
            return false;
    }

    let res = []

    for (let i = 1; i < a.length-1; i++){
        for (let j = 1; j < a[i].length-1; j++){
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