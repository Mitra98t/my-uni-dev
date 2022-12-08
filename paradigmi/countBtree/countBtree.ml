open Printf;;

type btree = 
  | Void
  | Node of int * btree * btree;;


let positivoPred x = x>0

let positivoPred2 x =
  match x with
  | Void -> false
  | Node(i,_,_) -> i > 0;;


let bt =
  Node (3,
    Node(5,Void,Void),
    Node (-4,
      Node(6,Void,Void),
      Node(8,Void,Void)
    )
  );;

(*
Scrivere una funzione che determina il numero di nodi che hanno ENTRAMBI i filli che soddisfano un predicato
firma: btree -> (int -> bool) -> int
*)

let rec count albero p= 
  match albero with
  | Node(v, a1, a2) -> 
      let checkUnder (x,y) =  
        match (x, y) with
        | (Void, _) -> false
        | (_, Void) -> false
        | (Node(v1, _, _), Node(v2,_,_)) -> ((p v1) && (p v2)) 
      in
      (* if checkUnder (a1,a2) then 1 + (count a1 p) + (count a2 p) else (count a1 p) + (count a2 p) *)
      (if checkUnder(a1,a2) then 1 else 0) + (count a1 p) + (count a2 p)
  | Void -> 0
;;

let res = count bt positivoPred;;
printf "%d\n" res;;

(*
Scrivere una funzione che determina il numero di nodi che hanno ENTRAMBI i filli che soddisfano un predicato
firma: btree -> ( btree -> bool ) -> int
*)

let rec count2 albero p =
  match albero with
    | Node(v, a1, a2) ->
      (* if (p a1) && (p a2) then 1 + (count2 a1 p) + (count2 a2 p) else (count2 a1 p) + (count2 a2 p) *)
      (if (p a1) && (p a2) then 1 else 0) + (count2 a1 p) + (count2 a2 p)
    | Void -> 0
;;

let res2 = count2 bt positivoPred2;;
printf "%d\n" res2;;

