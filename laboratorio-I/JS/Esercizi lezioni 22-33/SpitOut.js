function spitOut(a, p){
    a.forEach(x => {
        if(!!(p(x)))
            console.log(x)
    })
}

spitOut([12,7,14,0,561], e=>(e%3==0))

spitOut(["la","vispa","teresa","solea"],(e=>e.indexOf("s")))

spitOut([31,3.1415, 1.4142, 7],e=>e==Math.round(e))

