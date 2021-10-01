"use strict";
exports.__esModule = true;
var fs = require("fs");
var FileTransformer = /** @class */ (function () {
    function FileTransformer(nomeFile) {
        this.WORDS = /[!?,.;:"'\s]+/gm;
        this.SPACES = /[^\S\n\r]/gm;
        this.LINES = /[\n\r]/g;
        this.nomeFile = nomeFile;
        this.occorrenzone = new Map();
        try {
            this.text = fs.readFileSync(this.nomeFile).toString();
        }
        catch (e) {
            this.text = null;
        }
        this.wordInFile = this.text == null ? null : this.text.split(this.WORDS);
    }
    FileTransformer.prototype.contaParole = function () {
        return this.wordInFile == null ? -1 : this.wordInFile.length - 1;
    };
    FileTransformer.prototype.contaSpazi = function () {
        return this.text == null ? -1 : this.text.split(this.SPACES).length - 1;
    };
    FileTransformer.prototype.contaRighe = function () {
        return this.text == null ? -1 : this.text.split(this.LINES).length;
    };
    FileTransformer.prototype.occorrenze = function (s) {
        if (this.wordInFile == null)
            return -1;
        if (s in this.occorrenzone)
            return this.occorrenzone.get(s);
        var n = this.wordInFile.filter(function (x) { return x == s; }).length;
        this.occorrenzone.set(s, n);
        return n;
    };
    FileTransformer.prototype.cifra = function (n) {
        if (this.text == null)
            return -1;
        var charList = this.text.split('').map(function (x) { return String.fromCharCode(x.charCodeAt(0) + n % 1024); });
        fs.writeFileSync(this.nomeFile + "-" + n + ".cy", charList.join(''));
        return charList.length;
    };
    FileTransformer.prototype.decifra = function (f) {
        var _a;
        var textToDecifra = '';
        try {
            textToDecifra = fs.readFileSync(f).toString();
        }
        catch (e) {
            textToDecifra = null;
        }
        if (textToDecifra == null)
            return -1;
        var section = /-[\d]+\./gm;
        var number = /[\d]+/gm;
        var tmp1 = f.match(section);
        var tmp2 = null;
        var n;
        if (tmp1 != null)
            tmp2 = (_a = tmp1[0]) === null || _a === void 0 ? void 0 : _a.match(number);
        if (tmp2 != null)
            n = Number(tmp2[0]);
        var charList = textToDecifra.split('').map(function (x) { return String.fromCharCode(Math.abs(x.charCodeAt(0) - n) % 1024); });
        fs.writeFileSync(f + ".decy", charList.join(''));
        return charList.length;
    };
    FileTransformer.prototype.comprimi = function () {
        var compresso = "";
        if (this.text == null)
            return -1;
        var charList = this.text.split('');
        if (charList.length > 0) {
            var tmpChar = charList[0];
            var count = 0;
            for (var _i = 0, charList_1 = charList; _i < charList_1.length; _i++) {
                var e = charList_1[_i];
                if (e == tmpChar)
                    count++;
                else {
                    compresso += (count > 1 ? count : "") + tmpChar;
                    count = 1;
                    tmpChar = e;
                }
            }
            compresso += (count > 1 ? count : "") + tmpChar;
        }
        fs.writeFileSync(this.nomeFile + ".comp", compresso);
        return compresso.split('').length;
    };
    FileTransformer.prototype.decomprimi = function (f) {
        var compositCompresso = "";
        var result = "";
        try {
            compositCompresso = fs.readFileSync(f).toString();
        }
        catch (e) {
            return -1;
        }
        var compressoChar = compositCompresso.match(/([\d]+[\D\n\r]|[\D\n\r])/gm);
        if (compressoChar != null) {
            for (var _i = 0, compressoChar_1 = compressoChar; _i < compressoChar_1.length; _i++) {
                var e = compressoChar_1[_i];
                var count = e.match(/[\d]+/);
                var char = e.match(/[\D\n\r]/);
                if (char != null) {
                    for (var i = 0; i < (count != null ? Number(count[0]) : 1); i++)
                        result += char[0];
                }
            }
            fs.writeFileSync(f + ".decomp", result);
            return result.split('').length;
        }
        else
            return -1;
    };
    return FileTransformer;
}());
var ft = new FileTransformer('cantoInf1.txt');
console.log(ft.contaParole()); //1004
console.log(ft.contaSpazi()); //924
console.log(ft.contaRighe()); //144
console.log(ft.occorrenze("fui")); //4
console.log(ft.occorrenze("sono")); //0
console.log(ft.cifra(5)); //5149
console.log(ft.decifra("cantoInf1.txt-5.cy")); //5149
console.log(ft.cifra(256)); //5149
console.log(ft.decifra("cantoInf1.txt-256.cy")); //5149
ft = new FileTransformer('testC.txt');
console.log("SECONDA PARTE");
console.log(ft.contaParole()); //2
console.log(ft.contaSpazi()); //10
console.log(ft.contaRighe()); //9
console.log(ft.comprimi()); //37
console.log(ft.decomprimi("testC.txt.comp")); //75
ft = new FileTransformer('TestTesto.txt');
console.log(ft.contaParole());
console.log(ft.contaSpazi());
console.log(ft.contaRighe());
console.log(ft.cifra(8));
console.log(ft.decifra('TestTesto.txt-8.cy'));
console.log(ft.comprimi());
console.log(ft.decomprimi('TestTesto.txt.comp'));
//console.log(ft.decomprimi('TestTesto.txt.comp'))
