# Esercizi Lezioni 22-33

## SpitOut JS

Si scriva una funzione `spitOut(a,p)` che, dati come argomenti un array a e una funzione p, stampi tramite `console.log()` tutti gli elementi e di a tali che l’invocazione di `p(e)` restituisca `true` o un valore che viene promosso a `true`

Esempi:
`spitOut([12,7,14,0,561],e=>(e%3==0)) → stampa 12, 0, 561`
`spitOut([“la”,”vispa”,”teresa”,”solea”],e=>e.indexOf(“s”)) → stampa la, vispa, teresa`
`spitOut([31,3.1415, 1.4142, 7],e=>e==Math.round(e)) → stampa 31, 7`

## Spit Out TS

Si risolva l’esercizio SpitOut precedente, scrivendo però codice in TypeScript con tutti i tipi pienamente annotati.

Attenzione: risolvete l’esercizio indicando tutti i tipi, senza usare il tipo any

Suggerimento: si ripassino in particolare i tipi generici (generics)

## Multi Set JS

Si scriva una classe MultiSet che implementi un multiinsieme (ovvero, un insieme che può contenere più volte lo stesso elemento).

La classe deve implementare i seguenti metodi:

- `add(e)` - inserisce l’elemento e nel multiinsieme
- `remove(e)` - rimuove un elemento e dal multiinsieme; lancia un’eccezione `NoSuchElementException` se e non è presente nel multiinsieme
- `size()` - restituisce il numero di elementi contenuti nel multiinsieme (si implementi come una proprietà di sola lettura)
- `union(S)` - restituisce un nuovo multiinsieme contenente l’unione del multiinsieme con l’altro multiinsieme S (si usi il metodo add)
- `diff(S)` - restituisce un nuovo multiinsieme contenente la differenza fra il multiinsieme e l’altro multiinsieme S (si usi il metodo remove)

## Multi Set TS

Si ripeta l’esercizio MultiSet, scrivendo però il codice in TypeScript. Come già in SpitOut.ts, si abbia cura di dichiarare correttamente tutti i tipi dei metodi e delle proprietà, usando dove necessario i generics.

Si ricordi che anche le eccezioni lanciate andranno opportunamente adattate.

## Complex TS

Si definisca in TypeScript una classe Complex che rappresenta i numeri complessi (a+bi), con le relative operazioni. La classe deve implementare:

- Un costruttore con due argomenti (parte reale e parte immaginaria, ciascuna delle quali può essere un numero reale, oppure un numero razionale come definito nella classe Rational vista a lezione)
- Un costruttore con un argomento, che può essere un numero o un Rational (nel qual caso, si assume che l’argomento sia la parte reale e che la parte immaginaria sia 0i), oppure un Complex (nel qual caso, il costruttore restituisce lo stesso valore dell’argomento)
- Le operazioni di somma e moltiplicazione fra Complex, definite come (a,b)+(c,d) = (a+c,b+d) e (a,b)∙(c,d) = (ac-bd,bc+ad)
- Opportune funzioni di accesso che consentano di recuperare le proprietà a (parte reale) e bi (parte immaginaria), nonché le corrispondenti proprietà r (modulo) e phi (angolo), ricordando che per un Complex z, si ha z = a+bi = r(cos(phi) + i sin(phi))

Si curi di definire in maniera rigorosa tutti i tipi coinvolti.
