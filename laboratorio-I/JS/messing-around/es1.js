function confronta(x) {
    var p = (3 * (x ** 2)) + 5
    var p2 = (x ** 2) + (20 * x) + 1

    if (p > p2) {
        return true
    }
    else {
        return false
    }
}

var x = 5

console.log(confronta(x))