class TicTacToe {

  constructor() {
    this.campo = [];
    for (let i = 0; i < 3; i++) {
      this.campo[i] = new Array(3);
      for (let j = 0; j < 3; j++) {
        this.campo[i][j] = undefined
      }
    }
    this.last = "O";
  }

  move(i, j) {
    if (this.last == "O" && this.campo[i][j] == undefined) {
      this.campo[i][j] = "X"
      this.last = "X"
      if (this.checkWin()) {
        return { res: "tris", last: this.last }
      }
    }
    else if (this.last == "X" && this.campo[i][j] == undefined) {
      this.campo[i][j] = "O"
      this.last = "O"
      if (this.checkWin()) {
        return { res: "tris", last: this.last }
      }
    }
    else {
      return { res: "no", last: this.last }
    }
  }

  checkWin() {
    //horizontal
    for (let i = 0; i < 3; i++) {
      console.log(this.campo[i][0] + " == " + this.campo[i][1] + " && " + this.campo[i][1] + " == " + this.campo[i][2])
      if (this.campo[i].some((e) => e == undefined))
        continue
      if (this.campo[i][0] == this.campo[i][1] && this.campo[i][1] == this.campo[i][2])
        return true
    }

    //vertical
    for (let i = 0; i < 3; i++) {
      if ([this.campo[0][i], this.campo[1][i], this.campo[2][i]].some((e) => e == undefined))
        continue
      if (this.campo[0][i] == this.campo[1][i] && this.campo[1][i] == this.campo[2][i])
        return true
    }

    //diagonal
    let diag = true
    if (this.campo[0][0] == this.campo[1][1] && this.campo[1][1] == this.campo[2][2])
      if ([this.campo[0][0], this.campo[1][1], this.campo[2][2]].some((e) => e == undefined))
        return false
      else
        return true

    if (this.campo[0][2] == this.campo[1][1] && this.campo[1][1] == this.campo[2][0])
      if ([this.campo[0][2], this.campo[1][1], this.campo[2][0]].some((e) => e == undefined))
        return false
      else
        return true

    return false

  }

  reset() {
    this.campo = [];
    for (let i = 0; i < 3; i++) {
      this.campo[i] = new Array(3);
      for (let j = 0; j < 3; j++) {
        this.campo[i][j] = "l"
      }
    }
    this.last = "O";
    return true;
  }
}

let t = new TicTacToe();

console.table(t.campo);

console.log(t.move(0, 2))

console.table(t.campo);

console.log(t.move(1, 0))

console.table(t.campo);

console.log(t.move(1, 1))

console.table(t.campo);

console.log(t.move(2, 1))

console.table(t.campo);

console.log(t.move(2, 0))

console.table(t.campo);

console.log(t.move(1, 2))

console.table(t.campo);