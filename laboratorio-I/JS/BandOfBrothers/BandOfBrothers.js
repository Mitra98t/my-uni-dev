function contaCoppia(t, val1, val2) {
    //MANCANO entrambi i figli
    if (t.sx == null && t.dx == null) {
        return 0
    }
    //MANCA solo il sx => controlla se l'albero continua nel destro
    else if (t.sx == null) {
        return contaCoppia(t.dx, val1, val2)
    }
    //MANCA solo il dx => controlla se l'albero continua nel sinistro
    else if (t.dx == null) {
        return contaCoppia(t.sx, val1, val2)
    }
    //ESISTONO entrambi i figli del nodo T e SONO quelli che stiamo cercando
    else if (t.sx.val == val1 && t.dx.val == val2) {
        return contaCoppia(t.sx, val1, val2) + contaCoppia(t.dx, val1, val2) + 1
    }
    //ESISTONO entrambi i figli del nodo T e NON SONO quelli che stiamo cercando
    else {
        return contaCoppia(t.sx, val1, val2) + contaCoppia(t.dx, val1, val2)
    }
}

console.log(contaCoppia({ val: 7, sx: { val: 4, sx: { val: 3 }, dx: { val: 12, sx: { val: 4, dx: { val: 3 }, sx: { val: 8 } } } }, dx: { val: 11, dx: { val: 3 }, sx: { val: 8, sx: { val: 6 } } } }, 3, 12))

console.log(contaCoppia({ val: 7, sx: { val: 4, sx: { val: 3 }, dx: { val: 12, sx: { val: 4, dx: { val: 3 }, sx: { val: 8 } } } }, dx: { val: 11, dx: { val: 3 }, sx: { val: 8, sx: { val: 6 } } } }, 8, 3))

console.log(contaCoppia({ val: 7, sx: { val: 4, sx: { val: 3 }, dx: { val: 12, sx: { val: 4, dx: { val: 3 }, sx: { val: 8 } } } }, dx: { val: 11, dx: { val: 3 }, sx: { val: 8, sx: { val: 6 } } } }, 4, 12))
