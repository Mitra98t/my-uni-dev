function shuffle(array) {
    var currentIndex = array.length, temporaryValue, randomIndex;

    // While there remain elements to shuffle...
    while (0 !== currentIndex) {

        // Pick a remaining element...
        randomIndex = Math.floor(Math.random() * currentIndex);
        currentIndex -= 1;

        // And swap it with the current element.
        temporaryValue = array[currentIndex];
        array[currentIndex] = array[randomIndex];
        array[randomIndex] = temporaryValue;
    }

    return array;
}

function check(a){
    for(let i = 1; i < a.length; i++){
        if(a[i] < a[i-1]){
            return false;
        }
    }
    return true;
}

function bogo(arr){
    let tmp = false
    let cont = 0
    do{
        tmp = check(arr)
        if(!tmp){
            shuffle(arr)
        }
        cont++
    }while(!tmp)
    return cont
}

function factorial(num) {
    if (num < 0) 
          return -1;
    else if (num == 0) 
        return 1;
    else {
        return (num * factorial(num - 1));
    }
  }

let arr = [1,7,3,5,9,100,36,4,20,300,2,10]
console.log(factorial(arr.length))
console.time("oh no")
console.log(bogo(arr))
console.timeEnd("oh no")