Array.prototype.reverse2 = function(){
    return this.map(this.pop, [...this]);
}