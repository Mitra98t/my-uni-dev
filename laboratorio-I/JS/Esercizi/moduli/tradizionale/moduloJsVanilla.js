/**
 * Raddoppia il numero
 * @param {Number} n Numero da raddoppiare
 * @returns {Number} 2*n
 */
function dop(n){
    return 2*n;
}

/**
 * Funzione non esportata
 */
function insult (){
    return "questo non lo esporto >.<"
}

/**
 * Un complimento per te <3
 */
const comp = "Sei bello <3";

exports.complimento = comp;
exports.doppio = dop;