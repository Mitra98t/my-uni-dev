class Complex{
    real :number;
    imma :number;

    constructor(r :number, i? :number){
        this.real = r;
        if(i !== undefined)
            this.imma = i;
        else
            this.imma = r;
    }

}