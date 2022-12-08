open Printf;;
open List;;

(** Prova 3 | Esercizio 3 *)

let split list pred =
  let rec aux xs (z1,z2) =
    match xs with
    | w::ws -> if pred w then aux ws (z1@[w], z2) else aux ws (z1, z2@[w])
    | [] -> (z1,z2)
  in
  aux list ([], [])
;;

let f x = x = 'a' ;;
split ['a';'b';'c';'a';'d';'a'] f ;;

let p x = x >= 0;;
split [1;5;-6;2;-4;-9;0;-1] p;;
