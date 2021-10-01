"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
exports.__esModule = true;
var fs = require("fs");
var EccezioneDisponibilità = /** @class */ (function (_super) {
    __extends(EccezioneDisponibilità, _super);
    function EccezioneDisponibilità() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    return EccezioneDisponibilità;
}(Error));
var Libro = /** @class */ (function () {
    function Libro(titolo, isbn, autore, dispo) {
        if (dispo === void 0) { dispo = 0; }
        this.titolo = titolo;
        this.isbn = isbn;
        this.autore = autore;
        this.disponibilità = dispo;
    }
    Libro.prototype.sell = function (nCopie) {
        if (nCopie === void 0) { nCopie = 1; }
        if (this.disponibilità >= nCopie)
            this.disponibilità -= nCopie;
        else
            throw new EccezioneDisponibilità;
    };
    Libro.prototype.stock = function (nCopie) {
        this.disponibilità += nCopie;
    };
    return Libro;
}());
var l = new Libro("Il buio oltre la siepe", "978-8807881558", "Harper Lee");
console.log(l);
l.stock(10);
l.sell(11);
var Graph = /** @class */ (function () {
    function Graph(edges) {
        this.n = edges.length;
        this.edges = edges;
    }
    Graph.prototype.complement = function () {
        var res = new Array(this.n);
        console.log(res);
        for (var e in this.edges) {
            res[e] = new Array();
            for (var i = 0; i < this.n; i++) {
                if (!this.edges[e].includes(i))
                    res[e].push(i);
            }
        }
        return new Graph(res);
    };
    Graph.prototype.getSecondNeighbours = function (i) {
        var close = this.edges[i];
        var res = [];
        for (var _i = 0, close_1 = close; _i < close_1.length; _i++) {
            var e = close_1[_i];
            for (var _a = 0, _b = this.edges[e]; _a < _b.length; _a++) {
                var inner = _b[_a];
                if (!res.includes(inner))
                    res.push(inner);
            }
        }
        res.sort();
        return res;
    };
    return Graph;
}());
var Square = /** @class */ (function () {
    function Square(x, y, lato) {
        if (lato <= 0)
            this.lato = 1;
        else
            this.lato = lato;
        this.x = x;
        this.y = y;
    }
    Square.prototype.area = function () { return this.lato * this.lato; };
    ;
    Square.prototype.getName = function () { return 'Square'; };
    ;
    Square.prototype.translate = function (x, y) { this.x = x, this.y = y; };
    ;
    return Square;
}());
var Circle = /** @class */ (function () {
    function Circle(x, y, raggio) {
        if (raggio <= 0)
            this.raggio = 1;
        else
            this.raggio = raggio;
        this.x = x;
        this.y = y;
    }
    Circle.prototype.area = function () { return (this.raggio * this.raggio) * Math.PI; };
    ;
    Circle.prototype.getName = function () { return 'Circle'; };
    ;
    Circle.prototype.translate = function (x, y) { this.x = x, this.y = y; };
    ;
    return Circle;
}());
function sommaArray(a, somma) {
    var res = a[0];
    for (var i = 1; i < a.length; i++) {
        res = somma(res, a[i]);
    }
    return res;
}
var Studente = /** @class */ (function () {
    function Studente(nome, cognome, citta, votoLaurea) {
        this.nome = nome;
        this.cognome = cognome;
        this.citta = citta;
        this.votoLaurea = votoLaurea;
    }
    return Studente;
}());
function leggiStudenti(file) {
    var testo = fs.readFileSync(file, 'utf-8');
    var studenti = testo.split(/[\n\r]/g);
    var res = new Array(studenti.length);
    for (var i in studenti) {
        var tmp = studenti[i].split(',');
        res[i] = new Studente(tmp[0], tmp[1], tmp[2], Number(tmp[3]));
    }
    return res;
}
var GenericFileToArray = /** @class */ (function () {
    function GenericFileToArray(nomeFile, parse) {
        var testo = fs.readFileSync(nomeFile, 'utf-8');
        var splitted = testo.split(/[\n\r]/g);
        this.arr = new Array();
        for (var _i = 0, splitted_1 = splitted; _i < splitted_1.length; _i++) {
            var e = splitted_1[_i];
            this.arr.push(parse(e));
        }
    }
    GenericFileToArray.prototype.toString = function () {
        var tmp = new Array;
        for (var _i = 0, _a = this.arr; _i < _a.length; _i++) {
            var e = _a[_i];
            tmp.push(JSON.stringify(e));
        }
        return tmp.join('\\n') + '\\n';
    };
    GenericFileToArray.prototype.cerca = function (o, equals) {
        for (var i = 0; i < this.arr.length; i++)
            if (equals(o, this.arr[i]))
                return i;
        return -1;
    };
    return GenericFileToArray;
}());
