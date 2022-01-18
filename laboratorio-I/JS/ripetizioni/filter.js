function shiftCirc(a) {
    let primo = a[0];
    for (let i = 0; i < a.length - 1; i++) {
        a[i] = a[i + 1]
    }
    a[a.length - 1] = primo
    return a
}

console.log(shiftCirc([1,2,3,4,5]))