class NoSuchElementException extends Error{}

class MultiSet <T>{
    arr :Array<T>

    constructor (){
        this.arr = []
    }

    add(e) :void{
        this.arr.push(e)
    }

    remove(e) :void{
        if(this.arr.indexOf(e) == -1){
            throw new NoSuchElementException(`non esiste`)
        }
        this.arr = this.arr.filter(x => x != e)
    }

    get size() :number{
        return this.arr.length;
    }

    union(S: MultiSet<T>) :Array<T>{
        let res = new MultiSet<T>();
        for(let e of this.arr){
            res.add(e)
        }

        for(let e of S.arr){
            res.add(e)
        }

        return res.arr
    }
    
    diff(S):Array<T>{
        let res = new MultiSet<T>();
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

let ms = new MultiSet<number>();

let ms1 = new MultiSet<number>();

ms.add(1)
ms.add(2)
ms.add(3)

ms1.add(2)
ms1.add(3)
ms1.add(4)


console.log(ms.union(ms1))
// console.log(ms.diff(ms1))