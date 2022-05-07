class NoSuchElementException extends Error{}

class MultiSet {
    constructor (){
        this.arr = []
    }

    add(e){
        this.arr.push(e)
    }

    remove(e){
        if(!this.arr.includes(e)){
            throw new NoSuchElementException(`non esiste`)
        }
        this.arr = this.arr.filter(x => x != e)
    }

    get size(){
        return this.arr.length;
    }

    union(S){
        let res = new MultiSet();
        for(let e of this.arr){
            res.add(e)
        }

        for(let e of S.arr){
            res.add(e)
        }

        return res.arr
    }
    
    diff(S){
        let res = new MultiSet();
        for(let e of this.arr){
            res.add(e)
        }

        for(let e of S.arr){
            try {
                res.remove(e)
            } catch (error) {
                continue;
            }
        }

        return res.arr
    }
}

let ms = new MultiSet();

let ms1 = new MultiSet();

ms.add(1)
ms.add(2)
ms.add(3)

ms1.add(2)
ms1.add(3)
ms1.add(4)


// console.log(ms.union(ms1))
console.log(ms.diff(ms1))