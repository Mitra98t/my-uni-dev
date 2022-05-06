// //Copiare anche l'enum
// enum Fuel {Diesel, Gasoline, Electric};
// class NoFuelException extends Error { }
// class Car{
//     fuelType :Fuel;
//     fuelCapacity :number; // capacità max
//     consumption :number; // consumo medio 1 carburante su km
//     fuelLevel :number // rimanenza tra 0 e fuelCapacity
//     constructor(fuelType :Fuel, fuelCapacity :number, consumption :number, fuelLevel :number = 0) {
//         this.fuelType = fuelType
//         this.fuelCapacity = fuelCapacity
//         this.consumption = consumption
//         this.fuelLevel = fuelLevel
//     }
//     refillFuel(f:number = this.fuelCapacity):number{
//         if(this.fuelLevel + f >= this.fuelCapacity){
//             this.fuelLevel = this.fuelCapacity
//             return this.fuelLevel
//         }
//         this.fuelLevel += f
//         return this.fuelLevel
//     }
//     drive (km :number):number{
//         if(this.fuelLevel - this.consumption*km < 0){
//             throw new NoFuelException()
//         }
//         this.fuelLevel -= this.consumption*km
//         return this.fuelLevel
//     }
// }
// let c1=new Car(Fuel.Diesel,30,0.5)
// console.log(c1)
// console.log(c1.drive(10))
// console.log(c1.refillFuel(20))
// console.log(c1.drive(10))
// console.log(c1.drive(30))
// console.log(c1.refillFuel())
function unique(a, equals) {
    var res = [a[0]];
    var same = false;
    for (var i = 1; i < a.length; i++) {
        same = false;
        for (var _i = 0, res_1 = res; _i < res_1.length; _i++) {
            var e = res_1[_i];
            if (equals(e, a[i]))
                same = true;
        }
        if (!same)
            res.push(a[i]);
    }
    return res;
}
console.log(unique([3, 5, 3, 2, 8, 5], (function (x, y) { return x == y; })));
console.log(unique([0, 0, 0, 0, 0, 0, 0], (function (x, y) { return x == y; })));
console.log(unique(['hello', 'hello', 'how', 'are', 'you'], (function (x, y) { return x == y; })));
