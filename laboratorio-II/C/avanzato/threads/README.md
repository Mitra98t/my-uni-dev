# Threads

> Esercizi sui threads

## Esercizio 1

Scrivere un programma C che implementa una pipeline di tre threads

- Il primo thread legge una riga alla volta da un file testuale (il cui nome è passato come argomento al programma) ed invia al secondo thread ogni riga letta dal file
- Il secondo thread "tokenizza” le parole dalla riga ricevuta dal primothread (considerare come separatore solo lo spazio) ed invia al terzothread le parole
- Il terzo thread stampa tutte le parole sullo standard output
- I tre stadi della pipeline devono lavorare in modo concorrente come inuna "catena di montaggio”
  - Il buffer di comunicazione tra due stadi della pipeline deve essereimplementata con una coda FIFO (la scelta se usare una coda dicapacita bounded o unbounded è lasciata allo studente)

## Esercizio 2

- Estendere l'esercizio precedente in modo che il terzo thread della pipeline, invece di stampare tutte le parole ricevute dallo stadio intermedio della pipeline, stampi sullo standard output ogni occorrenza di una parola una sola volta
- A tale scopo è possibile utilizzare una tabella hash in cui si usa come chiave la parola tokenizzata (provare ad utilizzare l'implementazione icl_hash di una tabella hash in C)

## Esercizio 3

- Scrivere un programma C in cui si attivano M thread produttori ed N thread consumatori che condividono una coda di capacità "illimitata"
- Il programma accetta come argomento anche un intero K che corrisponde al numero totale di messaggi che i produttori producono concorrentemente nella coda (ogni produttore produce K/M messaggi – se M divide K)
- I consumatori leggono i messaggi dalla coda in un ciclo infinito fino a quando non ricevono un messaggio speciale che li fa terminare
- Implementare la coda concorrente come lista concatenata di elementi allocati dinamicamente, ed il protocollo di terminazione senza usare la cancellazione esplicita dei threads (i.e., pthread_cancel)
- Testare la funzionalità del programma al variare di M ed N

## Esercizio 4 - 5

Sono espansioni dei 3 esercizi precedenti
In Es 5 vengono usati i Segnali
