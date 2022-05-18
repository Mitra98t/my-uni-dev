# Prova intermedia Lab2 CorsoA

## Bash e chiamate di sistema per l’I/O

Si consideri una cartella di nome dir in un sistema Linux. La cartella dir viene utilizzata da alcune applicazioni per scrivervi file temporanei (non ci sono altre directory nella cartella dir). Tali applicazioni scrivono i file una sola volta nella directory dir, non li aggiornano, e non li rimuovono ma li leggono più volte dopo averli scritti. Se l’applicazione non trova il file che aveva precedentemente scritto nella directory dir, lo ricrea nuovamente. Il sistemista che amministra la macchina Linux, vuole gestire la cartella dir assegnando una quota virtuale di spazio Q (ad esempio, Q=10MB) e vuole monitorare ad intervalli regolari la cartella dir per accertarsi che la quota assegnata non venga superata. Il sistemista quindi prepara uno script Bash con i seguenti parametri:

- `-d <dir>` nome della directory da monitorare
- `-s <size>` dimensione in MB corrispondente alla quota virtuale Q che vuole assegnare a dir
- `-f <warning-factor>` valore compreso tra 0 ed 1 per determinare la soglia di warning
- `-n <maxnum>` massimo numero di file da rimuovere, se 0 non c’è alcun limite

Lo script opera nel modo seguente: all’avvio controlla la dimensione corrente della directory dir (currdirsize), se risulta che size – currdirsize è minore di size*warningfactor, allora vengono eliminati dalla cartella dir al più maxnum file considerando quelli che hanno il tempo dall’ultimo accesso minore (cioè i file più vecchi). Il numero di file che viene effettivamente eliminato (minore o uguale a maxnum, se maxnum diverso da 0) è il numero minimo tale che lo spazio libero virtuale della cartella risulti maggiore della soglia di warning.

Esempio: supponiamo che dir contenga 3 file, file1 (atime=10, size=5MB), file2 (atime=6, size=3MB) file3 (atime=8, size=5MB); size=14MB, warning-factor=0.1 ed maxnum=0. Lo script eliminerà solo il file2 (lo spazio libero sarà 4MB>(0.1*14MB)). Se warning-factor fosse stato 0.35, allora lo script avrebbe eliminato file2 e file3.

Si chiede di realizzare lo script Bash descritto precedentemente e un analogo programma scritto in C che operi esattamente come lo script. Lo script Bash non può far uso dei comandi “sed” ed “awk”. Il programma C, deve utilizzare chiamate POSIX per la lettura dei metadati dei file e della directory dir.
Lo studente dovrà consegnare, caricando su Classroom, un file in formato .tar.gz contenente: lo script Bash; il codice sorgente del programma C (e gli eventuali include files), un Makefile per compilare il programma C e per eseguire i test; una o più directory contenenti i file per eseguire i test e dimostrare la funzionalità dello script e del programma C. **Limitare la dimensione di tali directory a non più di 15MB**.
Il comando make se lanciato senza argomenti, deve compilare il programma C (senza warnings né errori). Il Makefile deve avere inoltre almeno i seguenti target fittizi (PHONY): test1 e test2. Il primo target manda in esecuzione lo script Bash su una delle directory di test fornite e dovrà stampare sullo standard output messaggi di diagnostica che descrivono le azioni intraprese ed i file selezionati per la rimozione. Il secondo target fittizio (test2) manda in esecuzione il programma C su una delle directory di test fornite e stamperà sullo standard output il resoconto delle azioni intraprese. I valori dei parametri passati allo script ed al programma C (-d, -s, -f, -n) per i due test, sono scelti dallo studente.

**Suggerimento Bash**: Il seguente comando find stampa l’access time (atime), la size, ed il nome dei file contenuti nella directory dir passata come argomento: `find dir -type f -printf '%A@ %s %p\n'`
