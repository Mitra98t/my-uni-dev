function spitOut<T>(a :Array<T>, p :Function):void{
    a.forEach(x => {
        if(!!(p(x)))
            console.log(x)
    })
}