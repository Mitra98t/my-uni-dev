# Compito3 Lab II Java

## Esercizio 1

In questo esercizio dovete scrivere un programma per la gestione di articoli da campeggio.

### Gli articoli

Come prima cosa si deve definire la classe Articolo. Gli oggetti di tale classe sono caratterizzati da una stringa che ne indica il tipo (ad esempio "tenda", "bussola", etc), da un intero che ne indica il peso, e da un secondo intero che ne indica il volume.

Due articoli sono considerati uguali se e solo se hanno lo stesso tipo, peso e volume. Notare che esistono articoli dello stesso tipo ma peso e volume diversi (ad esempio una tenda di peso 5 e volume 8 e una seconda tenda di peso 10 e volume 12).

Ogni tipo di oggetto ha assegnato un valore (notare il valore è assegnato al tipo quindi se il tipo "tenda" ha valore 10 tutte le tende, indipendentemente da peso e volume avranno quel valore). Nella classe Articolo esiste quindi una variabile di classe che associa ad ogni tipo un valore. Tale valore di default è 1, ma deve poter essere cambiato mediante il metodo di classe:

`static void assegna_valore(String tipo, int nuovo_valore);`

Nota: è possibile assegnare un valore anche a dei tipi per i quali non esiste nessun articolo, quindi questo metodo non deve fare nessun controllo sul parametro tipo.

Oltre a questo metodo di classe, la classe deve contenere almeno il costruttore:

`Articolo(String t, int p, int v)`

che costruisce un articolo di tipo t, peso p e volume v.

### Il magazzino

Come secondo compito si deve implementare una classe Magazzino che permetta di gestire una collezione di articoli (cioè istanze della classe Articolo). Per ogni articolo si deve tenere traccia di quanti esemplari ci sono in magazzino. In particolare la classe Magazzino deve supportare i seguenti metodi:

`Magazzino()`

Costruttore: costruisce un magazzino inizialmente vuoto, cioè senza nessun articolo.

`int aggiungi(Articolo a, int q)`

Aggiunge al magazzino q esemplari dell'articolo a; restituisce il numero di esemplari di a disponibili dopo l'aggiunta

`void rifornisci(String filename)`

Aggiunge al magazzino gli articoli che sono indicati nel file di testo filename. Ogni riga del file si riferisce ad un articolo e contiene tipo, peso, volume, e quantità separati dalla virgola. Ad esempio, la riga:

`pannello solare,3,2,10`

fa aggiungere al magazzino 10 articoli di tipo "pannello solare" di peso 3 e volume 2. Per semplicità assumete che non ci siano spazi prima e dopo la virgola. Per estrarre i dati da una linea in questo formato usate il metodo split della classe String e il metodo statico Integer.parseInt.

`boolean disponibile(Articolo a)`

Restituisce true se almeno un esemplare dell'articolo a è in magazzino

`int prendi1(Articolo a)`

Cerca di prendere un esemplare dell'articolo a se il magazzino non contiene l'articolo lancia l'eccezione OutOfStock, altrimenti l'articolo viene rimosso dal magazzino e viene restituito il numero di articoli disponibili dopo la rimozione

`List<Articolo> disponibili()`

Restituisce una lista degli articoli attualmente disponibili in magazzino (cioè una lista degli articoli di cui il magazzino ne contiene almeno un esemplare). La lista deve essere ordinata lessicograficamente per tipo, a parità di tipo per peso crescente, a parità di tipo e peso per volume crescente.

`int volume_tot()`

Restituisce il volume totale di tutti gli articoli in magazzino (ricordare che ogni articolo ha un attributo volume)

### Lo zaino

Infine dovete implementare una classe Zaino. Anche uno zaino è semplicemente un qualcosa che può contenere degli articoli, ma i metodi richiesti sono diversi. Uno zaino è caratterizzato da due costanti pmax e vmax che indicano rispettivamente il peso massimo che può essere inserito nello zaino e il volume massimo che può essere contenuto nello zaino.

Nella classe Zaino devono essere implementati i seguenti metodi:

`Zaino(int p, int v)`

Costruttore: costruisce uno zaino inizalmente vuoto con peso massimno p e volume massimo v.

`boolean puo_contenere(Articolo a)`

Restituisce true se lo zaino può contenere l'articolo a (cioe' se mettendo a nello zaino non si superano il peso o il volume massimi) false altrimenti

`void aggiungi(Articolo a)`

se lo zaino può contenere l'articolo a lo aggiunge, altrimenti, se vengono superati i limiti di peso o volume, deve essere lanciata l'eccezione NoWay

`void svuota()`

vuota lo zaino eliminando tutti gli articoli in esso contenuto

`int peso()`

restituisce il peso totale degli articoli nello zaino

`int volume()`

restituisce il volume totale degli articoli nello zaino

`int valore()`

restituisce il valore totale degli articoli nello zaino

`boolean contiene_tipo(String t)`

Restituisce true se lo zaino contiene un articolo di tipo t, false altrimenti. Notate che t è un tipo (ad esempio "tenda") non un'istanza di Articolo

`void riempi(Magazzino m)`

Aggiunge allo zaino degli articoli presi dal magazzino m secondo il seguente procedimento:

Crea una lista di tutti gli articoli disponibili nel magazzino m; la lista deve essere ordinata per valore decrescente, a parità di valore per peso crescente, a parità di valore e peso per volume crescente
Fino a quando la lista non è vuota prendi l'articolo in testa alla lista e inseriscilo nello zaino se:
l'articolo è di un tipo che non è già presente nello zaino, e
può essere inserito senza superare i limiti di peso e volume
altrimenti scarta l'articolo e considera il successivo. Gli articoli inseriti nello zaino devo essere rimossi dal magazzino.
Importante

Tutti le variabili di istanza delle classi Magazzino e Zaino devonno essere private
Vi è lasciata la scelta delle strutture dati da utilizzare per rappresentare gli articoli presenti dentro i magazzini e gli zaini: saranno apprezzate soluzioni che favoriscono l'efficienza. Metette un commento nel codice che giustifichi le vostre scelte
Oltre ai metodi indicati potete definirne degli altri. Per il debugging cosiglio di definire almeno i metodi toString.
Il file elenco.csv è un esempio di file in un formato che deve essere accettato dal metodo riempi. NON MODIFICARE questo file in quanto è usato per i test.
