# Esercizi OCaml - 02 - Liste e Pattern Matching

## 1. Inferenza di tipi con le liste

Esercizio 1.1. Che tipo hanno le seguenti espressioni? Cercare di inferirlo a mente (o su carta) 
e poi controllare se la risposta è corretta facendo valutare l'espressione all'interprete:

1. [(3,4);(2,1)]
  - (int * int) list
2. fun x lis -> x::lis
  - ('a -> 'a list) -> 'a list
3. fun x lis -> let b=x>0 in if b then lis else [b]
  - (int -> bool list) -> bool list
4. fun x -> []::x
  - 'a list list -> 'a list list
5. let f n = n+1 in if true then [f] else [(fun x -> x); (fun x-> x-1)]
  - (int -> int) list = [<fun>]




## 2. Funzioni ricorsive su liste

ATTENZIONE:

* Per risolvere i seguenti esercizi provare innanzitutto a definire delle funzioni ricorsive in modo 
esplicito (per intenderci con let rec`) e poi provare a dare una soluzione diversa non utilizzando la ricorsione esplicita,
ma ricorrendo alle funzioni higher-order viste a lezione (`List.map,List.filter,List.fold_right,List.fold_left, eccetera...)
* Nella soluzione è possibile (e in alcuni casi, consigliato) definire funzioni ausiliarie usando il 
costrutto let ...  in. Nelle soluzioni che si basano su ricorsione esplicita la funzione ricorsiva può essere 
quella principale o una (o più) di quelle ausiliarie.

Esercizio 2.1. Scrivere una funzione genera_lista che prende un intero positivo n e restituisce una 
lista contenente la lista [1; 2; ... n]. Nel caso in cui n sia minore o uguale di zero restituisce la lista vuota.



Esercizio 2.2. Scrivere una funzione media che prende una lista di interi e calcola la media dei suoi elementi.



Esercizio 2.3. Scrivere una funzione take che prende una lista lis e un intero n e restituisce la lista 
contenente i primi n elementi di lis. Se n è minore di 0 resituisce la lista vuota.



Esercizio 2.4. Scrivere una funzione drop che prende una lista lis e un intero n e restituisce una lista 
contenente gli elementi di lis ad eccezione dei primi n. Se n è minore di 0 restituisce lis.



Esercizio 2.5. Scrivere una funzione somma_costante che prende una lista di coppie di interi e verifica 
(restituendo true o `false`) se tutte le coppie hanno elementi la cui somma è sempre lo stesso valore.



Esercizio 2.6. Scrivere una funzione ord che prende una lista e verifica (restituendo true o `false`) 
se i suoi elementi sono ordinati in modo crescente.



Esercizio 2.7. Scrivere una funzione min che prende un elemento x e una lista lis e restituisce il minore 
tra x e il minimo della lista lis.



Esercizio 2.8. Scrivere una funzione remove che prende un elemento x e una lista lis e restituisce una 
lista uguale a lis ma senza la prima occorrenza dell'elemento x.



Esercizio 2.9. Scrivere una funzione sort che prende una lista di elementi di qualunque tipo e restituisce 
una lista con gli stessi elementi ordinati in modo crescente. (Suggerimento: possono essere utili le funzioni 
min e remove degli esercizi precedenti).



Esercizio 2.10. Scrivere una funzione (o meglio, un predicato) set che prende una lista e verifica 
(restituendo true o false`) se i suoi elementi sono tutti diversi tra loro, cioè se la lista è una corretta 
rappresentazione di un insieme. La funzione deve avere tipo `'a -> bool, in modo da poter essere essere 
applicata ad insiemi con elementi di qualunque tipo.



Esercizio 2.11. Un multi-insieme (o multiset) estende il concetto di insieme consentendo la possibilità di 
avere più occorrenze dello stesso elemento. Un multiset può essere definito come una lista di coppie (x,n) 
in cui x è l'elemento considerato e n è il numero di occorrenze di quell'elemento. Scrivere una funzione multiset 
che, data una lista di coppie di tipo 'a*int, verifica se è una corretta rappresentazione di un multiset 
(contentente coppie che sono tutte diverse tra loro nel primo elemento). 



Esercizio 2.12. Scrivere una funzione crea_multiset che, data una lista di qualunque tipo anche con elementi 
ripetuti, la trasforma in un multiset verificabile tramite la funzione multiset dell'esercizio precedente.
