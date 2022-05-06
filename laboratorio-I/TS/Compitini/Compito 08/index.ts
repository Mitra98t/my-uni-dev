import * as fs from "fs"

 

class EccezioneDisponibilità extends Error { }

class Libro {
    private titolo: string;
    private isbn: string;
    private autore: string;
    private disponibilità: number;

    constructor(titolo: string, isbn: string, autore: string, dispo: number = 0) {
        this.titolo = titolo;
        this.isbn = isbn;
        this.autore = autore;
        this.disponibilità = dispo;
    }

    sell(nCopie: number = 1): void {
        if (this.disponibilità >= nCopie)
            this.disponibilità -= nCopie;
        else
            throw new EccezioneDisponibilità
    }

    stock(nCopie: number) {
        this.disponibilità += nCopie;
    }
}

class Graph {
    public n: number;
    public edges: Array<Array<number>>;

    constructor(edges: Array<Array<number>>) {
        this.n = edges.length;
        this.edges = edges;
    }

    complement(): Graph {
        let res: Array<Array<number>> = new Array(this.n);
        console.log(res)
        for (let e in this.edges) {
            res[e] = new Array();
            for (let i = 0; i < this.n; i++) {
                if (!this.edges[e].includes(i))
                    res[e].push(i)
            }
        }

        return new Graph(res)
    }

    getSecondNeighbours(i: number): Array<number> {
        let close: Array<number> = this.edges[i];
        let res: Array<number> = [];

        for (let e of close) {
            for (let inner of this.edges[e])
                if (!res.includes(inner))
                    res.push(inner)
        }

        res.sort()

        return res
    }

}

// ESERCIZIO Shape
interface Shape {
    x: number;
    y: number;
    area(): number;
    getName(): string;
    translate(x: number, y: number): void;
}


class Square implements Shape {
    x: number;
    y: number;
    lato: number;

    constructor(x: number, y: number, lato: number,) {
        if (lato <= 0)
            this.lato = 1
        else
            this.lato = lato

        this.x = x
        this.y = y
    }

    area(): number { return this.lato * this.lato };

    getName(): string { return 'Square' };

    translate(x: number, y: number): void { this.x = x, this.y = y };
}

class Circle implements Shape {
    x: number;
    y: number;
    raggio: number;

    constructor(x: number, y: number, raggio: number,) {
        if (raggio <= 0)
            this.raggio = 1
        else
            this.raggio = raggio

        this.x = x
        this.y = y
    }

    area(): number { return (this.raggio * this.raggio) * Math.PI };

    getName(): string { return 'Circle' };

    translate(x: number, y: number): void { this.x = x, this.y = y };

}

function sommaArray<T>(a: T[], somma: (x: T, y: T) => T): T {
    let res: T = a[0];
    for (let i = 1; i < a.length; i++) {
        res = somma(res, a[i])
    }
    return res
}

class Studente {
    nome: string;
    cognome: string;
    citta: string;
    votoLaurea: number;

    constructor(nome: string, cognome: string, citta: string, votoLaurea: number) {
        this.nome = nome
        this.cognome = cognome
        this.citta = citta
        this.votoLaurea = votoLaurea
    }

}
function leggiStudenti(file: string): Array<Studente> {
    let testo: string = fs.readFileSync(file, 'utf-8')
    let studenti: Array<string> = testo.split(/[\n\r]/g)
    let res: Array<Studente> = new Array(studenti.length)
    for (let i in studenti) {
        let tmp: Array<string> = studenti[i].split(',')
        res[i] = new Studente(tmp[0], tmp[1], tmp[2], Number(tmp[3]))
    }
    return res
}

class GenericFileToArray<T> {
    arr: Array<T>;

    constructor(nomeFile: string, parse: (s: string) => T) {
        let testo: string = fs.readFileSync(nomeFile, 'utf-8');
        let splitted: Array<string> = testo.split(/[\n\r]/g);

        this.arr = new Array()
        for (let e of splitted)
            this.arr.push(parse(e))

    }

    toString(): string {
        let tmp: Array<string> = new Array;
        for (let e of this.arr) {
            tmp.push(JSON.stringify(e))
        }
        return tmp.join('\\n') + '\\n'
    }

    cerca(o: T, equals: (a: T, b: T) => boolean): number {
        for (let i = 0; i < this.arr.length; i++)
            if (equals(o, this.arr[i]))
                return i;

        return -1
    }
}