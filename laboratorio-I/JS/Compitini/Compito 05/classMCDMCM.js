class MCDMCM {
    constructor(num1, num2) {
        this.num1 = num1;
        this.num2 = num2;
    }

    mcm() {
        let fattoriPrimi = (n) => {
            const fattori = [];
            let divisore = 2;

            while (n >= 2) {
                if (n % divisore == 0) {
                    fattori.push(divisore);
                    n = n / divisore;
                }
                else
                    divisore++;
            }
            return fattori;
        }

        let fattA = fattoriPrimi(this.num1);
        let fattB = fattoriPrimi(this.num2);
        let mcm = 1;
        const countOccor = (arr, val) => arr.reduce((a, v) => (v === val ? a + 1 : a), 0);

        for (let e of fattA) {
            if (fattB.includes(e)) {
                let occur = 0;

                if (countOccor(fattA, e) >= countOccor(fattB, e))
                    occur = countOccor(fattA, e)
                else
                    occur = countOccor(fattB, e)

                for (let i = 0; i < occur; i++) {
                    mcm = mcm * e;
                }

                fattB = fattB.filter(function (v, i, ar) { return v != e })
                fattA = fattA.filter(function (v, i, ar) { return v != e })
            }
            for (let i = 0; i < countOccor(fattA, e); i++) {
                mcm = mcm * e;
            }
            fattA = fattA.filter(function (v, i, ar) { return v != e })
        }
        if (fattB.length > 0) {
            for (e of fattB) {
                mcm = mcm * e;
            }
        }
        return mcm
    }

    mcd() {
        let fattoriPrimi = (n) => {
            const fattori = [];
            let divisore = 2;

            while (n >= 2) {
                if (n % divisore == 0) {
                    fattori.push(divisore);
                    n = n / divisore;
                }
                else
                    divisore++;
            }
            return fattori;
        }

        let fattA = fattoriPrimi(this.num1);
        let fattB = fattoriPrimi(this.num2);
        let mcd = 1;
        const countOccor = (arr, val) => arr.reduce((a, v) => (v === val ? a + 1 : a), 0);
        
        for (let e of fattA) {
            if (fattB.includes(e)) {
                let occur = 0;
                if (countOccor(fattA, e) <= countOccor(fattB, e))
                    occur = countOccor(fattA, e)
                else
                    occur = countOccor(fattB, e)

                for (let i = 0; i < occur; i++) {
                    mcd = mcd * e;
                }

                fattB = fattB.filter(function (v, i, ar) { return v != e })
                fattA = fattA.filter(function (v, i, ar) { return v != e })
            }
        }
        return mcd
    }
}

let obj = new MCDMCM(30, 40)

console.log(obj.mcm())

console.log(obj.mcd())

//FUNONZIA <3