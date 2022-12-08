# Esercitazione complessiva su OCaml

## Introduzione al formato grafico SVG

SVG è un formato di grafica vettoriale basato su XML. Una immagine in formato SVG è un file di testo che contiene informazioni sulle figure che devono essere rappresentate. In questo esempio, una immagine di dimensione 600x400 che contiene un rettangolo e un cerchio:

```
<svg width="600" height="400" xmlns="http://www.w3.org/2000/svg">
  <rect x="10" y="10" width="100" height="50" style="stroke:red;fill:green"/>
  <circle cx="100" cy="100" r="50" style="stroke:red;fill:green"/>
</svg>
```

Salvando il testo riportato qui sopra in un file con estensione `.svg` sarà possibile visualizzare l'immagine tramite un browser o un programma di grafica. Maggiori dettagli su questo formato grafico possono essere facilmente trovate in rete.

## Scopo di questa esercitazione

In questa esercitazione useremo OCaml per generare alcune semplici immagini in formato SVG.

## Tipi di dato

Innanzitutto abbiamo bisogno di definire un po' di tipi che ci consentano di trattare (parti di) file svg come dati processabili dalle funzioni che andremo a definire.

Iniziamo definendo un tipo di dato `colors` che descriva possibili colori da usare nell'attributo "style" dei tag `<rect>` e `<circle>`.

```OCaml
type colors = White | Black | Red | Blue | Green ;;
```

**Esercizio 1.** Definiamo una funzione `string_of_colors` che converte valori di tipo `colors` in stringhe contenenti il nome del colore in inglese (scritto tutto in minuscolo).

```OCaml
let string_of_colors c =
    match c with
        | White -> "white"
        | Black -> "black"
        | Red -> "red"
        | Blue -> "blue"
        | Green -> "green";;
        
```

**Esercizio 2.** Definiamo un tipo record `style` per descrivere il contenuto dell'attributo `style` dei tag `<rect>` e `<circle>`. Questo tipo record deve avere due campi, `stroke` e `fill` entrambi di tipo `colors` ma con la possibilità di essere indefinito (tramite un *tipo opzione*).

```OCaml
type style = { stroke: colors option; fill: colors option};;
```

**Esercizio 3.** Definiamo un tipo `figure` che descrive possibili figure da inserire all'interno dell'immagine svg. Questo tipo è l'unione di due tipi che descrivono rispettivamente i tag `<rect>` e `<circle>`. I tipi da unire dovranno essere record i cui campi corrispondono agli attributi dei tag `<rect>` e `<circle>`, rispettivamente. Usare `Rect` e `Circle` come costruttori.

```OCaml
type figure = 
    | Rect of {x: int; y:int; width:int, height: int, style:style}
    | Circle of {cx: int; cy:int; r:int, style:style};;
```

Definiamo ora un tipo `svg_img` che descrive un'intera immagine svg. Anche questo sarà un tipo record questa volta corrispondente al tag `<svg>`, e dovrà avere due campi per memorizzare larghezza e altezza dell'immagine, e un campo per memorizzare una lista di figure di tipo `figure` che corrispondono ai rettangoli e ai cerchi contenuti nell'immagine.

```OCaml
type svg_img = {width: int; height: int; figures: figure list} ;;
```

## Funzioni per la creazione di immagini

Definiamo una funzione `init_svg_img` che prende come parametri una larghezza e un'altezza e restituisce un elemento di tipo `svg_img` con quelle dimensioni e lista di figure vuota.

```OCaml
let init_svg_img w h = { width=w; height=h; figures=[] } ;;
```

**Esercizio 4.** Definiamo una funzione `add_fig` che prende una immagine di tipo `svg_img`, una figura di tipo `figure` e restituisce una nuova immaigine uguale alla precedente ma con la nuova figura aggiunta in testa alla lista di figure dell'immagine di partenza.

```OCaml
let add_fig img fig = { img with figures = fig::img.figures} ;;
```

**Esercizio 5.** Definiamo una funzione `add_figure_list` che prende una immagine e una lista di figure di tipo `figure` e restituisce una nuova immagine uguale alla precedente, ma con in più tutte le figure della lista. (nota: usare `add_fig` dell'esercizio precedente).

```OCaml
let rec add_figures_list img figures=
    match figures with
        | [] -> img
        | x::xs -> add_figures_list
```

Cerchiamo ora di riprodurre il file svg presentato come esempio all'inizio. Partiamo da creare un'immagine vuota di dimensione 600x400:

```OCaml
let img0 = init_svg_img 600 400 ;;
```

Creiamo il cerchio e il rettangolo come nell'esempio iniziale:

```OCaml
let circle1 = Circle { cx= 100; cy= 100; r=50; style= {stroke= Some Red; fill= Some Green }} ;;
let rect1 = Rect {x=10; y=10; width=100; height=50; style={stroke= Some Red; fill= Some Green } };;
```

Aggiungiamoli uno dopo l'altro all'immagine vuota `img0` tramite la funzione `add_fig`:

```OCaml
let img1 = add_fig img0 circle1 ;;
let img2 = add_fig img1 rect1 ;;
```

## Generazione del codice SVG

**Esercizio 6.** La funzione `generate_svg_code` prende una immagine di tipo `svg_img` e restituisce una stringa con la rappresentazione testuale del codice svg. Purtoppo la definizione seguente non funziona correttamente. Comprendiamo il codice e correggiamo l'errore:

```OCaml
let generate_svg_code img = 
    let generate_head img =
        "<svg width=\"" ^ (string_of_int img.width) ^ "\" " ^
        "height=\"" ^ (string_of_int img.height) ^ "\" " ^ 
        "xmlns=\"http://www.w3.org/2000/svg\">\n"
    in
    let rec generate_figures figs =
        let generate_style s =
            match (s.stroke,s.fill) with
            | (None,None) -> ""
            | (Some c1,None) -> "stroke:" ^ (string_of_colors c1)
            | (None, Some c2) -> "fill:" ^ (string_of_colors c2)
            | (Some c1,Some c2) -> "stroke:" ^ (string_of_colors c1) ^ ";" ^ "fill:" ^ (string_of_colors c2)
        in 
        match figs with
        | [] -> ""
        | (Circle c)::figs' -> "  <circle cx=\"" ^ (string_of_int c.cx) ^ "\" " ^
                               "cy=\"" ^ (string_of_int c.cy) ^ "\" " ^
                               "r=\"" ^ (string_of_int c.r) ^ "\" " ^
                               "style=\"" ^ (generate_style  c.style) ^ "\"" ^
                               "/>\n"
        | (Rect r)::figs' -> "  <rect x=\"" ^ (string_of_int r.x) ^ "\" " ^
                               "y=\"" ^ (string_of_int r.y) ^ "\" " ^
                               "width=\"" ^ (string_of_int r.width) ^ "\" " ^
                               "height=\"" ^ (string_of_int r.height) ^ "\" " ^
                               "style=\"" ^ (generate_style  r.style) ^ "\"" ^
                               "/>\n"
    in
    let generate_tail = "</svg>"
    in
        (generate_head img) ^ (generate_figures img.figures) ^ (generate_tail) ;;
        
        
```

Generiamo ora il codice dell'immagine `img2`. Il risultato dovrebbe corrispondere al codice svg di esempio mostrato all'inizio.

```OCaml
print_endline (generate_svg_code img2) ;;
```

## Da liste di coppie a immagini

**Esercizio 7.** Scrivere una funzione `pairs_to_circles` che prende una lista di coppie di interi e genera una lista di cerchi (di tipo `figure`) in cui ogni cerchi corrisponde a un elemento della lista di coppie, e i due interi di ogni coppia sono usati come coordinate del centro del cerchio corrispondente. Tutti i cerchi hanno raggio 50 e nello stile hanno `stroke` nero e `fill` rosso. (nota: questa funzione può essere esplicitamente ricorsiva oppure usare le funzioni higher-order su liste)

```OCaml

```

Usiamo la funzione per creare un po' di cerchi:

```OCaml
let circles = pairs_to_circles [(200,200); (100,100); (300,100); (250,150)] ;;
```

Creiamo una immagine con tutti i cerchi appena creati (aggiungendoli all'immagine vuota `img0`):

```OCaml
let img = add_figure_list img0 circles;;
```

Generiamo il codice dell'immagine (nota: copiando il codice in un file separato salvato come svg lo possiamo visualizzare nel browser):

```OCaml
print_endline (generate_svg_code img)
```

## Cerchiamo un cerchio

Prossimo obiettivo è trovare un modo per identificare il cerchio più a sinistra in una immagine svg. Questo sostanzialmente corrisponde a trovare una sorta di minimo (il cerchio con la minima distanza dal lato sinistro dell'immagine). Raggiungeremo questo risultato definendo una funzione di ricerca molto generale...

**Esercizio 8.** Definire la funzione `find` che prende come parametri una funzione `compare` e una lista `lis`. Assumiamo che la funzione `compare` ricevuta dalla `find` sia in grado di confrontare due elementi `x` e `y` restituendo `true` se `x` precede `y` secondo un certo ordinamento totale conosciuto dalla `compare`. La funzione `find` deve restituire l'elemento della lista `lis` che è minimo rispetto a tale ordinamento. Se la lista è vuota deve sollevare un'eccezione. (nota: vedere gli esempi d'uso sotto per farsi un'idea)

```OCaml

```

```OCaml
find (<) [3;4;2;6;1;2] ;; (* deve restituire 1 *)
```

```OCaml
find (>) [3;4;2;6;1;2] ;; (* deve restituire 6 *)
(* nota: 6 risulta essere "minimo" perchè è il "più a sinistra"
nell'ordinamento ..>..>..>..>.. *)
```

```OCaml
find (fun s1 s2 -> String.length s1 < String.length s2) ["abc";"ee";"gdws";"bgs"] ;;
(* deve restituire "ee" *)
```

```OCaml
let compare_cerchi fig1 fig2 =
    match (fig1,fig2) with
    | (Circle c1,Circle c2) -> c1.cx<c2.cx
    | (_,_) -> failwith "figure non cerchi" ;;
    
let c = find compare_cerchi img.figures ;; 
(* deve restituire il cerchio più a sinistra *)
```

## Un linguaggio per bandiere

Consideriamo la seguente grammatica che descrive alberi con foglie colorate (color trees):

```
ctree ::= ctree + ctree | color
color ::= white | black | red | blue | green
```

**Esercizio 9.** Definire il tipo `color_tree` che rappresenta l'albero di sintassi astratta di `ctree` usando costruttori `Node` e `Leaf`, e il tipo `colors` già visto per i colori.

```OCaml

```

Esempio di valore di tipo `color_tree`:

```OCaml
let ct = Node (Leaf Red,(Node (Leaf Green,Leaf Blue))) ;;
```

**Esercizio 10.** Definire una funzione ricorsiva `lista_bandiera` che prende un albero `color_tree`, un valore intero `x` e una larghezza `width` e costruisce una lista di tuple con un elemento per ogni foglia dell'albero. L'idea è che ogni elemento della lista rappresenta un rettangolo di una ipotetica bandiera a strisce verticali. `x` è la coordinata da cui inizia l'area in cui disegnare le strisce (nella prima chiamata della funzione solitamente è 0) e `width` è la larghezza di tale area. Scendendo in profondità nell'albero, la larghezza da dedicare ai rettangoli da disegnare si dimezza. Ossia: l'albero corrispondente a "red + blue" porterà ad una bandiera per metà rossa e metà blu, mentre quello di "red + (green + blue)" porterà ad una bandiera per metà rossa, un quarto verde e un quarto blu. Nella lista da generare, ogni tupla dirà, per ogni rettangolo colorato da generare, la sua coordinata `x` di partenza, la sua larghezza e il suo colore. Ad esempio, partendo da un `x` pari a 0 e una larghezza complessiva di 600, l'albero di "red + (green + blue)" dovrà portare alla lista `[(0, 300, Red); (300, 150, Green); (450, 150, Blue)]`.

```OCaml

```

```OCaml
let lis_b = lista_bandiera ct 0 600;;
```

**Esercizio 11.** Definire una funzione `pairs_to_rectangle` che, analogamente alla funzione `pairs_to_circles` definita in un esercizio precedente, genera una lista di rettangoli di tipo `figure` a partire da una lista di tuple come restituite dalla funzione `lista_bandiera`.

```OCaml

```

Ora traduciamo la lista di tuple `lis_b` in rettangoli:

```OCaml
let rectangles  = pairs_to_rectangles lis_b 400;;
```

Creiamo una nuova immagine con dentro i rettangoli creati (usando come base l'immagine vuota `img0`):

```OCaml
let img = add_figure_list img0 rectangles ;;
```

Generiamo il codice svg dell'immagine ottenuta (ma prima per ottenere un risultato corretto dobbiamo aver svolto l'esercizio 6):

```OCaml
print_endline (generate_svg_code img);;
```
