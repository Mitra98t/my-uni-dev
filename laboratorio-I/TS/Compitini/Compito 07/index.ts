

import * as fs from "fs";

class FileTransformer {
    private readonly WORDS: RegExp = /[!?,.;:"'\s]+/gm;
    private readonly SPACES: RegExp = /[^\S\n\r]/gm;
    private readonly LINES: RegExp = /[\n\r]/g;

    private nomeFile: string;
    private text: string | null;
    private occorrenzone: Map<string, number>;
    private wordInFile: string[] | null;

    constructor(nomeFile: string) {
        this.nomeFile = nomeFile;
        this.occorrenzone = new Map<string, number>();
        try {
            this.text = fs.readFileSync(this.nomeFile).toString();
        }
        catch (e) {
            this.text = null;
        }
        this.wordInFile = this.text == null ? null : this.text.split(this.WORDS);
    }

    contaParole(): number {
        return this.wordInFile == null ? -1 : this.wordInFile.length - 1;
    }

    contaSpazi(): number {
        return this.text == null ? -1 : this.text.split(this.SPACES).length - 1;
    }

    contaRighe(): number {
        return this.text == null ? -1 : this.text.split(this.LINES).length;
    }

    occorrenze(s: string): number | undefined {
        if (this.wordInFile == null) return -1;
        if (s in this.occorrenzone) return this.occorrenzone.get(s);

        let n: number = this.wordInFile.filter((x) => x == s).length;

        this.occorrenzone.set(s, n);
        return n;
    }

    cifra(n: number): number {
        if (this.text == null) return -1

        let charList: string[] = this.text.split('').map((x) => String.fromCharCode(x.charCodeAt(0) + n % 1024));

        fs.writeFileSync(`${this.nomeFile}-${n}.cy`, charList.join(''));

        return charList.length
    }

    decifra(f: string): number {
        let textToDecifra :string | null = '';
        try {
            textToDecifra = fs.readFileSync(f).toString();
        }
        catch (e) {
            textToDecifra = null;
        }

        if (textToDecifra == null) return -1

        let section: RegExp = /-[\d]+\./gm;
        let number: RegExp = /[\d]+/gm;

        let tmp1: RegExpMatchArray | null = f.match(section);
        let tmp2: RegExpMatchArray | null = null;
        let n: number;

        if (tmp1 != null) tmp2 = tmp1[0]?.match(number);
        if (tmp2 != null) n = Number(tmp2[0]);

        let charList: string[] = textToDecifra.split('').map((x) => String.fromCharCode(Math.abs(x.charCodeAt(0) - n) % 1024));

        fs.writeFileSync(`${f}.decy`, charList.join(''));

        return charList.length
    }

    comprimi(): number {
        let compresso: string = "";
        if (this.text == null) return -1
        let charList: string[] = this.text.split('');
        if (charList.length > 0) {
            let tmpChar: string = charList[0];
            let count: number = 0;
            for (let e of charList) {
                if (e == tmpChar) count++;
                else {
                    compresso += (count > 1 ? count : "") + tmpChar
                    count = 1;
                    tmpChar = e;
                }
            }

            compresso += (count > 1 ? count : "") + tmpChar
        }

        fs.writeFileSync(`${this.nomeFile}.comp`, compresso)
        return compresso.split('').length
    }

    decomprimi(f: string): number {
        let compositCompresso: string = "";
        let result: string = "";
        try {
            compositCompresso = fs.readFileSync(f).toString();
        }
        catch (e) {
            return -1
        }

        let compressoChar: RegExpMatchArray | null = compositCompresso.match(/([\d]+[\D\n\r]|[\D\n\r])/gm);
        if (compressoChar != null) {
            for (let e of compressoChar) {
                let count: RegExpMatchArray | null = e.match(/[\d]+/);
                let char: RegExpMatchArray | null = e.match(/[\D\n\r]/);

                if (char != null) {
                    for (let i: number = 0; i < (count != null ? Number(count[0]) : 1); i++)
                        result += char[0];
                }
            }
            fs.writeFileSync(`${f}.decomp`, result);
            return result.split('').length
        }
        else
            return -1
    }
}

let ft = new FileTransformer('cantoInf1.txt')
console.log(ft.contaParole()); //1004
console.log(ft.contaSpazi()); //924
console.log(ft.contaRighe()); //144
console.log(ft.occorrenze("fui")); //4
console.log(ft.occorrenze("sono")); //0
console.log(ft.cifra(5)); //5149
console.log(ft.decifra("cantoInf1.txt-5.cy")); //5149
console.log(ft.cifra(256)); //5149
console.log(ft.decifra("cantoInf1.txt-256.cy")); //5149

ft = new FileTransformer('testC.txt')
console.log("SECONDA PARTE")
console.log(ft.contaParole()); //2
console.log(ft.contaSpazi()); //10
console.log(ft.contaRighe()); //9
console.log(ft.comprimi()); //37
console.log(ft.decomprimi("testC.txt.comp")); //75


ft = new FileTransformer('TestTesto.txt')
console.log(ft.contaParole())
console.log(ft.contaSpazi())
console.log(ft.contaRighe())
console.log(ft.cifra(8))
console.log(ft.decifra('TestTesto.txt-8.cy'))
console.log(ft.comprimi())
console.log(ft.decomprimi('TestTesto.txt.comp'))
//console.log(ft.decomprimi('TestTesto.txt.comp'))