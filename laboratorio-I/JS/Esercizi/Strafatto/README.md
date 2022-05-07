# Strafatto

> parte degli [esercizi liberi lezioni 18-25](https://docs.google.com/presentation/d/1JLvpeU_RRGGeFIObIARFxPF6GvogEJ9u5ra7YMw9_eU)

Si scriva una funzione strafatto(n) che, dato come argomento un intero positivo n, restituisca un array contenente tutti i modi diversi di fattorizzare n, con divisori maggiori di 1 e minori di n. Ciascuna sequenza di divisori è a sua volta rappresentata come un array. Suggerimenti: notate che non ci limitiamo ai fattori primi, e ricordate che la ricorsione è vostra amica!

Esempi:
`strafatto(359) → []`
`strafatto(10) → [[2,5]]`
`strafatto(12) → [[2,2,3],[2,6],[3,4]]`
`strafatto(60) → [[2,2,3,5],[2,2,15],[2,30],[2,6,5],[2,3,10],... ]`
