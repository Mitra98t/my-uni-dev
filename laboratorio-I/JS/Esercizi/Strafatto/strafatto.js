function primeFactors(n) {
    let res = []
    while (n % 2 == 0) {
        res.push(2)
        n = Math.floor(n / 2);
    }
    for (let i = 3; i <= n; i = i + 2) {
        while (n % i == 0) {
            res.push(i)
            n = Math.floor(n / i);
        }
    }

    return res
}



console.log(primeFactors(12))