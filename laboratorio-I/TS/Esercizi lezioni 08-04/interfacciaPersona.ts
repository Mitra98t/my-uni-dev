interface Persona {
    nome: string;
    cognome: string;
    codiceFiscale: string
    getName(): string; // restituisce il contenuto di “nome” concatenato a “cognome”
    getAge(): number; // restituisce un numero random compreso tra 18 e 44
}


class Impiegato implements Persona{
    nome :string;
    cognome :string;
    codiceFiscale :string
    employeeNumber :number;

    constructor(nome: string, cognome :string, codiceFiscale :string){
        this.nome = nome;
        this.cognome = cognome;
        this.codiceFiscale = codiceFiscale;
        this.employeeNumber = (Math.floor(Math.random()*(50-5+1)+5))*2;
    }

    getEmployeeNumber() :number { return this.employeeNumber }

    getName() :string{ return this.nome + this.cognome }

    getAge() :number{ return Math.floor(Math.random()*(44-18+1)+18) }
}

let P = new Impiegato('Mirko', 'Botta', 'FrancescoGAy');

console.log(P.getEmployeeNumber());
console.log(P.getName());
console.log(P.getAge());

