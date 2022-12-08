open Printf;;
type ide = string;;

type tname = TInt | TBool | TString | TClosure | TRecClosure | TUnBound

type exp =
  | EInt of int
  | CstTrue
  | CstFalse
  | EString of string
  | Den of ide
  | Sum of exp * exp
  | Diff of exp * exp
  | Prod of exp * exp
  | Div of exp * exp
  | IsZero of exp
  | Eq of exp * exp
  | LessThan of exp * exp
  | GraterThan of exp * exp
  | And of exp * exp
  | Or of exp * exp
  | Not of exp
  | IfThenElse of exp * exp * exp
  | Let of ide * exp * exp
  | Letrec of ide * ide * exp * exp
  | Fun of ide * exp
  | Apply of exp * exp


type 't env = ide -> 't

type evT = 
  | Int of int
  | Bool of bool
  | String of string
  | Closure of ide * exp * evT env
  | RecClosure of ide * ide * exp * evT env
  | UnBound

let emptyenv = function x -> UnBound

let bind (s: evT env) (x: ide) (v: evT) = 
  function (i: ide) ->  if (i = x) then v else (s i)


(* Type checking *)

let getType (x: evT) : tname = 
  match x with
    | Int(n) -> TInt
    | Bool(b) -> TBool
    | String(s) -> TString
    | Closure(i,e,en) -> TClosure
    | RecClosure(i,j,e,en) -> TRecClosure
    | UnBound -> TUnBound

let typeCheck ((x,y) : (tname * evT)) = 
  match x with
    | TInt -> (match y with
                | Int(n) -> true
                | _ -> false
              )
    | TBool -> (match y with
                | Bool(n) -> true
                | _ -> false
              )
    | TString -> (match y with
                | String(n) -> true
                | _ -> false
              )
    | TClosure -> (match y with
                | Closure(i,e,n) -> true
                | _ -> false
              )
    | TRecClosure -> (match y with
                | RecClosure(i,j,e,n) -> true
                | _ -> false
              )
    | TUnBound -> (match y with
                | UnBound -> true
                | _ -> false
              )

exception RunTimeError of string

(* Operazioni Primitive *)

let isZero(x) = 
  match (typeCheck(TInt, x), x) with
    | (true, Int(v)) -> Bool(v = 0)
    | (_, _) -> raise( RunTimeError "Wrong Type")
let intEq(x,y) =
  match (typeCheck(TInt, x), typeCheck(TInt, y), x, y) with
    | (true,true,Int(v),Int(w)) -> Bool(v = w)
    | (_,_,_,_) -> raise( RunTimeError "Wrong Type")
let intPlus(x,y) =
  match (typeCheck(TInt,x), typeCheck(TInt, y), x, y) with
    | (true, true, Int(v), Int(w)) -> Int(v+w)
    | (_,_,_,_) -> raise( RunTimeError "Wrong Type")
let intSub(x,y) =
  match (typeCheck(TInt, x), typeCheck(TInt,y), x,y) with
    | (true, true, Int(v), Int(w)) -> Int(v - w)
    | (_, _, _, _) -> raise( RunTimeError "Wrong Type")
let intTimes(x,y) =
  match (typeCheck(TInt, x), typeCheck(TInt, y), x, y) with
    | (true,true,Int(v),Int(w)) -> Int(v * w)
    | (_,_,_,_) -> raise( RunTimeError "Wrong Type")
let intDiv(x,y) =
  match (typeCheck(TInt,x), typeCheck(TInt, y), x, y) with
    | (true, tue, Int(v), Int(w)) -> if w <> 0 then Int(v/w) else raise(RunTimeError "Division By Zero")
    | (_,_,_,_) -> raise( RunTimeError "Wrong Type")
let lessThan(x,y) = 
  match (typeCheck(TInt, x), typeCheck(TInt, y), x, y) with
    | (true, true, Int(v), Int(w)) -> Bool(v<w)
    | (_,_,_,_) -> raise( RunTimeError "Wrong Type")
let graterThan(x,y) = 
  match (typeCheck(TInt, x), typeCheck(TInt, y), x, y) with
    | (true, true, Int(v), Int(w)) -> Bool(v>w)
    | (_,_,_,_) -> raise( RunTimeError "Wrong Type")
let boolAnd(x,y) = 
  match (typeCheck(TBool, x), typeCheck(TBool, y), x, y) with
    | (true, true, Bool(v), Bool(w)) -> Bool(v&&w)
    | (_,_,_,_) -> raise( RunTimeError "Wrong Type")
let boolOr(x,y) = 
  match (typeCheck(TBool, x), typeCheck(TBool, y), x, y) with
    | (true, true, Bool(v), Bool(w)) -> Bool(v||w)
    | (_,_,_,_) -> raise( RunTimeError "Wrong Type")
let boolNot(x) = 
  match (typeCheck(TBool, x), x) with
    | (true, Bool(v)) -> Bool(not(v))
    | (_,_) -> raise( RunTimeError "Wrong Type")


(* Interprete *)
let rec eval (e:exp) (s:evT env) :evT = 
  match e with
    | EInt(n) -> Int(n)
    | CstTrue -> Bool(true)
    | CstFalse -> Bool(false)
    | EString(s) -> String(s)
    | Den(i) -> (s i)

    | Prod(e1,e2) -> intTimes((eval e1 s), (eval e2 s))
    | Sum(e1,e2) -> intPlus((eval e1 s), (eval e2 s))
    | Diff(e1,e2) -> intSub((eval e1 s), (eval e2 s))
    | Div(e1,e2) -> intDiv((eval e1 s), (eval e2 s))

    | IsZero(e1) -> isZero (eval e1 s)
    | Eq(e1, e2) -> intEq((eval e1 s), (eval e2 s))
    | LessThan(e1,e2) -> lessThan((eval e1 s), (eval e2 s))
    | GraterThan(e1,e2) -> graterThan((eval e1 s), (eval e2 s))

    | And(e1, e2) -> boolAnd((eval e1 s), (eval e2 s))
    | Or(e1, e2) -> boolOr((eval e1 s), (eval e2 s))
    | Not(e1) -> boolNot(eval e1 s)

    | IfThenElse(e1, e2, e3) -> 
        let g = eval e1 s in 
          (match (typeCheck(TBool,g),g) with
            | (true, Bool(true)) -> eval e2 s
            | (true, Bool(false)) -> eval e3 s
            | (_,_) -> raise (RunTimeError "Wrong Type")
          )
    | Let(i, e, eBody) -> eval eBody(bind s i (eval e s))
    | Fun(arg, eBody) -> Closure (arg, eBody, s)
    | Letrec(f, arg, fBody, leBody) -> 
        let benv = bind (s) (f) (RecClosure (f, arg, fBody, s)) in 
          eval leBody benv
    | Apply (eF, eArg) ->
        let fClosure = eval eF s in 
          (match fClosure with
            | Closure (arg, fBody, fDecEnv) -> 
                let aVal = eval eArg s in 
                let aenv = bind fDecEnv arg aVal in 
                eval fBody aenv
            | RecClosure(f, arg, fBody, fDecEnv) ->
                let aVal = eval eArg s in 
                let rEnv = bind fDecEnv f fClosure in 
                let aenv = bind rEnv arg aVal in 
                eval fBody aenv
            | _ -> raise ( RunTimeError "Wrong Type" )
          )


let myRP = 
  Letrec("fact", "n",
          IfThenElse(Eq(Den("n"), EInt(0)),
                  EInt(1),
                  Prod(Den("n"),
                      Apply(Den("fact"), 
                          Diff(Den("n"), EInt(1))
                      )
                  )
          ),
          Apply(Den("fact"), EInt(3))
  );;

let x = eval myRP emptyenv;;
