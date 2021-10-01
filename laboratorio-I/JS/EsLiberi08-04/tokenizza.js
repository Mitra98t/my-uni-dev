//import * as fs from "fs";
const fs = require('fs')
function tokenizza(s){
    return s.split('@')
}

function tokenizza2(s){
    return fs.readFileSync(s).toString().split('@')
}

let s = 'const pi = 3.14 @\nwhile (var i = 0; i< pi+15; i++) {i++} @ return ';
console.log(tokenizza(s));

let path = 'tokenizzaTesto.txt'
console.log(tokenizza2(path));