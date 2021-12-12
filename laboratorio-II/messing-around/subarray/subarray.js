let a = [1, 2, 3, 4, 5, 6]

let b = [4, 5]

let c = [3, 5]

/**
 * Cerca a1 come subarray di a2
 * @param {*} a1 Array da trovare in a2
 * @param {*} a2 Array che dovrebbe contenere a1
 * @returns 0 se non trovato 1 se trovato
 */
function subarray(a1, a2) {
    for (let el = 0; el < a2.length; el++)
        if (a2[el] == a1[0]) {
            for (let i = 0; i < a1.length; i++)
                if (a1[i] != a2[el + i])
                    return 0;
            return 1
        }
}

console.log(subarray(b, a) + "\n");
console.log(subarray(c, a) + "\n");