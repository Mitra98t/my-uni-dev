var monovolume = /** @class */ (function () {
    function monovolume(se) {
        this.se = se;
    }
    // cercapalla:() => 1;
    monovolume.prototype.cercapalla = function (x) { return this.se ? 1 : 2; };
    return monovolume;
}());
