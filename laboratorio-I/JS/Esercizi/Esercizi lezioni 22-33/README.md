# Esercizi Lezioni 22-33

## SpitOut

Si scriva una funzione `spitOut(a,p)` che, dati come argomenti un array a e una funzione p, stampi tramite `console.log()` tutti gli elementi e di a tali che l’invocazione di `p(e)` restituisca `true` o un valore che viene promosso a `true`

Esempi:
`spitOut([12,7,14,0,561],e=>(e%3==0)) → stampa 12, 0, 561`
`spitOut([“la”,”vispa”,”teresa”,”solea”],e=>e.indexOf(“s”)) → stampa la, vispa, teresa`
`spitOut([31,3.1415, 1.4142, 7],e=>e==Math.round(e)) → stampa 31, 7`

## Crocette

Si consideri una matrice A di m×n interi, ciascuno dei quali può essere 0 o 1, rappresentata come un array di m righe (ogni riga è un array di n interi).
All’interno di A, una posizione (x,y) si dice contenere una “crocetta” se la cella (x,y) vale 1, come anche quelle subito sopra, sotto, a destra e a sinistra, mentre le quattro celle poste in diagonale valgono 0.
Si scriva una funzione crocette(A) che, ricevuta una matrice come descritto sopra, restituisca un array di tutte le coordinate (x,y) in A che contengono crocette, in cui ogni coordinata è rappresentata come un vettore di due elementi [x, y]. L’origine è (0,0) e corrisponde all’angolo in alto a sinistra; l’asse Y va verso il basso.

Esempi:

```js
A = [  
    [ 1,0,0,1,1 ],
    [ 0,1,0,1,0 ],
    [ 1,1,1,1,1 ],
    [ 0,1,0,1,0 ],
    [ 1,1,1,1,1 ],
    [ 0,1,0,1,1 ] 
]

crocette(A) → [[1,2],[3,2],[1,4]]
```

## Crocettex

Si scriva una funzione crocettex che si comporti esattamente come crocette dell’esercizio precedente, ma che in più verifichi che la matrice ricevuta come argomento abbia il formato corretto, e in caso contrario lanci le seguenti eccezioni:

- TooSmallException - se la matrice è più piccola di 3x3
- InvalidFormatException - se la matrice ha righe di lunghezza diversa
- BadContentException - se la matrice contiene qualunque valore diverso da 0 e 1

Le eccezioni vanno realizzate come oggetti di tipo diverso; gli oggetti lanciati possono contenere ulteriori informazioni di dettaglio, a vostra discrezione.

## MultiSet

Si scriva una classe MultiSet che implementi un multiinsieme (ovvero, un insieme che può contenere più volte lo stesso elemento).

La classe deve implementare i seguenti metodi:

- `add(e)` - inserisce l’elemento e nel multiinsieme
- `remove(e)` - rimuove un elemento e dal multiinsieme; lancia un’eccezione `NoSuchElementException` se e non è presente nel multiinsieme
- `size()` - restituisce il numero di elementi contenuti nel multiinsieme (si implementi come una proprietà di sola lettura)
- `union(S)` - restituisce un nuovo multiinsieme contenente l’unione del multiinsieme con l’altro multiinsieme S (si usi il metodo add)
- `diff(S)` - restituisce un nuovo multiinsieme contenente la differenza fra il multiinsieme e l’altro multiinsieme S (si usi il metodo remove)

## Reverse2

Il metodo reverse() chiamato su un array a, modifica a invertendo l’ordine dei suoi elementi.
Si aggiunga un metodo reverse2() a tutti gli array del vostro programma, che chiamato su un array a, restituisca un nuovo array contenente gli stessi elementi di a, in ordine inverso.

Attenzione: per questo esercizio, non potete usare reverse() per definire reverse2().

Variante: svolgete l’esercizio su una sola riga, senza chiamare nessun metodo predefinito degli array

## Group Anagrams

Si scriva una funzione groupAnagrams(a) che, dato un array di stringhe a, raggruppi tutte le stringhe in a che sono anagrammi l’una dell’altra, e restituisca un array contenente i vari gruppi (rappresentati a loro volta come array di stringhe). L’ordine del risultato non è rilevante.

Esempi:
`groupAnagrams([“scarabeo”, “arabo”, “noob, “arabesco”, “bono”]) → [ [ 'scarabeo', 'arabesco' ], [ 'arabo' ], [ 'noob', 'bono' ] ]`
`groupAnagrams([]) → []`

## Group Anagrams *

Si scriva una versione di groupAnagrams(), dall’esercizio precedente, implementata come generatore.

Esempi:

```js
var x=groupAnagrams([“scarabeo”, “arabo”, “noob, “arabesco”, “bono”])
x.next().value → ['scarabeo', 'arabesco']
x.next().value → ['arabo']
x.next().value → ['noob', 'bono']
x.next().value → undefined
```

## Single

Si scriva una funzione single(a) che, dato come argomento un array a di interi di lunghezza dispari n, ordinato in ordine crescente e in cui tutti gli elementi tranne uno appaiono esattamente due volte, restituisca il valore dell’unico elemento “single” che appare una sola volta.
Attenzione: dovete risolvere questo problema in O(log n).

Esempi:

```js
single([3,3,5,5,7,10,10,12,12]) → 7
single([1,2,2,5,5,8,8]) → 1
single([1,1,4,4,5,5,9,9,12,12,15,18,18]) → 15
```
