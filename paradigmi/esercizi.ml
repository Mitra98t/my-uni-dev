open Printf
let printList lis = List.iter (printf "%d ") lis; printf "\n";;

(*
Es 2.1
 *)
let rec genList n =
  match n with
    _ when n <= 0 -> [] 
    | _ -> genList (n-1) @ [n];;

printList(genList(5));;

(*
 Es 2.2
 *)

let rec average ?(avg = 0.0) ?(count = 1) = function
  | [] -> avg
  | hd::tl -> average
                ~avg:((avg*.(float (count-1))+.hd)/.(float (count)))
                ~count:(count+1)
                tl;;

print_float(average [1.;2.;3.]);;
printf "\n";;

