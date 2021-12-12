/**
 * @param {number} x
 * @return {boolean}
 */
var isPalindrome = function (x) {
    if(x < 0) return false
    let y = x
    let revNum = 0
    let devider = 10

    let multiplicator = Math.floor(Math.log(y) / Math.LN10 + 0.000000001)
    multiplicator = Math.pow(10, multiplicator)

    let tmp = 0
    do {
        tmp = Math.floor(y / devider)
        let cifra = (y - ((tmp) * devider))
        y = Math.floor(y / devider)
        revNum += multiplicator * cifra
        multiplicator /= 10
    } while (y != 0)

    return x == revNum
};


console.log(isPalindrome(0))