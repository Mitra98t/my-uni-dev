(*
Funzione g : int list -> int * int
restituisce una coppia col massimo e le sue occorrenze nella lista
*)

exception EmptyString of string;;

let g xs = 
  let rec findMax lis =
    match lis with
    | x::y::rest -> if x > y then findMax (x::rest) else findMax (y::rest)
    | x::[] -> x
    | [] -> 0
  in
  let rec countOccur lis v =
    match lis with
    | x::rest -> (if x = v then 1 else 0) + (countOccur rest v)
    | [] -> 0
  in
  (findMax xs,countOccur xs (findMax xs))
;;

let res = g [1;5;3;2;5;1;5];;
let res2 = g [];;
