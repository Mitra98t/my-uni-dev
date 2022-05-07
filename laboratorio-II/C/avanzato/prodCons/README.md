---

RW-simple.c: versione base, con precedenza sempre ai lettori
             (gli scrittori possono rimanere in attesa infinita).

RW-simple2.c: versione base, con precedenza sempre agli scrittori
             (i lettori possono rimanere in attesa infinita).

RW-fair.c: versione fair non fifo. 

RW-fifosem.c: come la precedente ma implementata con i semafori. Anche in questo caso non
	      e' garantito essere FIFO per via che la coda dei semafori non e' garantita
	      essere FIFO.

RW-fifo.c (dentro queue): versione FIFO un po' complessa fatta con una coda concorrente.
