interface Iveicolo {
    se: number;
    cercapalla: (x) => 1 | 2;
    dimmiCiao: () => "ciao" | "buonGiorno" | "Buonasera"
}

class monovolume implements Iveicolo {
    se: number;
    constructor(se: number) {
        this.se = se;
    }
    // cercapalla:() => 1;
    cercapalla(x): 1 | 2 { return this.se ? 1 : 2; }

    // Dio mio
    dimmiCiao(): "ciao" | "buonGiorno" | "Buonasera" { return 'Buonasera' }
}