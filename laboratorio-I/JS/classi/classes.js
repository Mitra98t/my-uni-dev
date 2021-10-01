class Persona {
    /**
     * Le variabili private vanno specificate all'inizio
     */
    #mood
    /**
     * Costruttore, assegna nome e età senza controlli.
     * @param {String} nome Nome della persona
     * @param {Number} eta Età della persona
     */
    constructor(nome, eta) {
        this.nome = nome;
        this.eta = eta
        this.#mood = (Math.floor(Math.random() * 2) + 1) == 1 ? true : false
    }

    /**
     * Aumenta eta di 1 e fa gli Auguri
     */
    compleanno(){
        this.eta++;
        return `tanti auguri ${this.eta}enne`
    }

    fancyPrint(){
        return `Ciao, mi chiamo ${this.nome} e ho ${this.eta}... ${this.#mood ? "Evvivaa!" : "Che palle-.-"}!`
    }

    /**
     * get rende annoNasc utilizzabile come se fosse una proprietà
     */
    get annoNasc(){
        return 2021 - this.eta;
    }

    /**
     * Richiamata quando si fa Persona.isMaggiorenne(p) 
     * @param {Persona} p persona da controllare
     */
    static isMaggiorenne(p){
        return p.eta >= 18 ? true : false;
    }
    /**
     * Come quello statico ma per la persona specifica
     * Richiamata con p.isMaggiorenne
     */
    isMaggiorenne(){
        return this.eta >= 18 ? true : false;
    }
}

class Studente extends Persona {
    constructor(nome, eta, scuola){
        super(nome, eta);
        this.scuola = scuola;
    }

    /**
     * Sovrascrive il compleanno banale di persona e inoltre regala un 10 <3
     */
    compleanno(){
        this.eta++;
        return `tanti auguri ${this.eta}enne. Ti darò un 10!`;
    }
}

let p = new Persona("Fede", 18);
let s = new Studente("Luca", 19, "IIS")
console.log(p.fancyPrint());
console.log(p.annoNasc);
console.log(Persona.isMaggiorenne(p));

console.log(p.compleanno())
console.log(s.compleanno())