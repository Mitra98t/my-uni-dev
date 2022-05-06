function* groupAnagrams(a){

    function compareArray(a, b) {
        if(a.length != b.length)
            return false;

        return a.every((v, k) => v === b[k])
    }

    let charSetG = []
    let charSet = []
    let res = []
    let groups = []

    for (e of a){
        charSet = e.split("");
        charSet.sort()
        if(!charSetG.some(cs => compareArray(cs, charSet)))
            charSetG.push(charSet)
    }
    

    for(cs of charSetG){
        groups = []
        for(s of a){
            currentCs = s.split("");
            currentCs.sort()
            if(compareArray(cs, currentCs))
                groups.push(s)
        }
        res.push(groups)
    }

    let i = 0
    while (i < res.length){
        yield res[i++]
    }
}