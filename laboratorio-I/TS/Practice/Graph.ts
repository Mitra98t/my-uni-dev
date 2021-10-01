interface node<T>{
    id :number
    value :T;
}

interface graph<T>{
    nodes: T[],
    em: number[][],
}

class Graph <T>{
    nodes: node<T>[];
    edgeMat: number[][];
    dimension:number;

    constructor(G?:graph<T>){
        this.nodes = [];
        this.edgeMat = [];
        this.dimension = 0;
        if(G != undefined){
            G.nodes.map(x => this.addNodeByValue(x))
            G.em.map(x => this.addOrientedEdgeByID(x[0], x[1]))
        }
    }

    addNodeByValue(n:T):void{
        this.nodes.push({id: this.nodes.length, value: n});
        for(let e of this.edgeMat){
            e.push(0)
        }
        this.dimension ++;
        this.edgeMat.push(Array<number>(this.dimension).fill(0))
    }

    addNode(n:node<T>):void{
        if(n.id < 0){
            console.log("ID out of bound. Ti attacchi al cazzo cit. Botta")
        }
        if(n.id < this.nodes.length){
            this.nodes[n.id] = n
        }
        else if(n.id == this.nodes.length){
            this.addNodeByValue(n.value)
        }
        else{
            console.log("ID out of bound. Ti attacchi al cazzo cit. Botta")
        }
    }

    getNodeByID(n:number):node<T>{
        return this.nodes[n]
    }


    addOrientedEdgeByID(from:number, to:number):void{
        this.edgeMat[from][to] = 1;
    }

    addOrientedEdge(from:node<T>, to:node<T>):void{
        this.edgeMat[from.id][to.id] = 1;
    }

    next(id:number):number[]{
        let res :number[] = [];
        for(let c = 0; c < this.edgeMat[id].length; c++){
            if(this.edgeMat[id][c] == 1 && id != c){
                res.push(c)
            }
        }
        return res
    }

    // findPathByID(idS :number, e? :number):node<T>[]{
    //     let start :number = idS;
    //     let end :number = 0;

    //     if(e == undefined)
    //         end = idS;
    //     else
    //         end = e;

        
    //     if(this.next(start).length > 0){ 
    //         }
    //     }
    //     return []
    // }

    fancyPrint():void{
        console.log("Node List");
        console.log(this.nodes);
        console.log("\nMatrix");
        for(let e of this.edgeMat)
            console.log(e)
    }
}

let testG:graph<number> = {
    nodes: [7,4,6,8],
    em:[[0,1],[1,2],[2,3],[3,0]]
}

let g:Graph<number> = new Graph<number>(testG);

g.fancyPrint()

console.log(g.next(2))