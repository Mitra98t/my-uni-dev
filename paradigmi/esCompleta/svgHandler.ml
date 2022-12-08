type colors = White | Black | Red | Blue | Green ;;
let string_of_colors c =
  match c with
  | Red -> "red"
  | Blue -> "blue"
  | Green -> "green"
  | Black -> "black"
  | White -> "white" ;;
type style = { stroke: colors option; fill: colors option } ;;
type figure =
| Rect of { x: int; y:int; width:int; height: int; style: style}
| Circle of { cx: int; cy: int; r: int; style: style } ;;
type svg_img = {width: int; height: int; figures: figure list} ;;
let init_svg_img w h = { width=w; height=h; figures=[] } ;;
let add_fig img fig = { img with figures=fig::img.figures } ;;
let rec add_figure_list img figures =
    match figures with
    | [] -> img
    | c::figures' -> add_figure_list (add_fig img c) figures';;
let img0 = init_svg_img 600 400 ;;
let circle1 = Circle { cx= 100; cy= 100; r=50; style= {stroke= Some Red; fill= Some Green }} ;;
let rect1 = Rect {x=10; y=10; width=100; height=50; style={stroke= Some Red; fill= Some Green } };;
let img1 = add_fig img0 circle1 ;;
let img2 = add_fig img1 rect1 ;;
let generate_svg_code img = 
    let generate_head img =
        "<svg width=\"" ^ (string_of_int img.width) ^ "\" " ^
        "height=\"" ^ (string_of_int img.height) ^ "\" " ^ 
        "xmlns=\"http://www.w3.org/2000/svg\">\n"
    in
    let rec generate_figures figs =
        let generate_style s =
            match (s.stroke,s.fill) with
            | (None,None) -> ""
            | (Some c1,None) -> "stroke:" ^ (string_of_colors c1)
            | (None, Some c2) -> "fill:" ^ (string_of_colors c2)
            | (Some c1,Some c2) -> "stroke:" ^ (string_of_colors c1) ^ ";" ^ "fill:" ^ (string_of_colors c2)
        in 
        match figs with
        | [] -> ""
        | (Circle c)::figs' -> "  <circle cx=\"" ^ (string_of_int c.cx) ^ "\" " ^
                               "cy=\"" ^ (string_of_int c.cy) ^ "\" " ^
                               "r=\"" ^ (string_of_int c.r) ^ "\" " ^
                               "style=\"" ^ (generate_style  c.style) ^ "\"" ^
                               "/>\n" ^ 
                               generate_figures figs'
        | (Rect r)::figs' -> "  <rect x=\"" ^ (string_of_int r.x) ^ "\" " ^
                               "y=\"" ^ (string_of_int r.y) ^ "\" " ^
                               "width=\"" ^ (string_of_int r.width) ^ "\" " ^
                               "height=\"" ^ (string_of_int r.height) ^ "\" " ^
                               "style=\"" ^ (generate_style  r.style) ^ "\"" ^
                               "/>\n" ^ 
                               generate_figures figs'
    in
    let generate_tail = "</svg>"
    in
        (generate_head img) ^ (generate_figures img.figures) ^ (generate_tail) ;;
print_endline (generate_svg_code img2) ;;
let rec pairs_to_circles lis =
    match lis with
    | [] -> []
    | (x,y)::lis' -> Circle {cx=x; cy=y; r=50; style={stroke=Some Black; fill=Some Red }} :: pairs_to_circles lis';;
    
let pairs_to_circles lis =
    List.map (fun (x,y) -> Circle {cx=x; cy=y; r=50; style={stroke=Some Black; fill=Some Red }} ) lis ;;
let circles = pairs_to_circles [(200,200); (100,100); (300,100); (250,150)] ;;
let img = add_figure_list img0 circles;;
print_endline (generate_svg_code img);;
let find compare lis =
    let rec find_rec ris lis =
        match lis with
        | [] -> ris
        | x::lis' -> if compare x ris 
                     then find_rec x lis'
                     else find_rec ris lis'
    in
        match lis with
        | [] -> failwith "lista vuota"
        | x::lis' -> find_rec x lis' ;;
find (<) [3;4;2;6;1;2] ;; (* deve restituire 1 *)
find (>) [3;4;2;6;1;2] ;; (* deve restituire 6 *)
(* nota: 6 risulta essere "minimo" perchè è il "più a sinistra"
nell'ordinamento ..>..>..>..>.. *)
find (fun s1 s2 -> String.length s1 < String.length s2) ["abc";"ee";"gdws";"bgs"] ;;
(* deve restituire "ee" *)

let compare_cerchi fig1 fig2 =
    match (fig1,fig2) with
    | (Circle c1,Circle c2) -> c1.cx<c2.cx
    | (_,_) -> failwith "figure non cerchi" ;;
    
let c = find compare_cerchi img.figures ;; 
(* deve restituire il cerchio più a sinistra *)


type color_tree = 
  | Node of color_tree * color_tree
  | Leaf of colors 
;;

let ct = Node (Leaf Red,(Node (Leaf Green,Leaf Blue))) ;;

let rec lista_bandiera (al:color_tree) (x:int) (width:int) =
  match al with
  | Leaf c -> [(x, width, c)]
  | Node(a1,a2) -> lista_bandiera a1 x (width/2) @ lista_bandiera a2 (x+width/2) (width/2)
;;

let lis_b = lista_bandiera ct 0 600;;

let rec pairs_to_rectangles lis h=
  match lis with
  | (pos, wid, col)::res -> Rect {x=pos; y=0; width=wid; height=h; style={stroke=None; fill= Some col}}::pairs_to_rectangles res h
  | [] -> []
;;

let rectangles  = pairs_to_rectangles lis_b 400;;

let img = add_figure_list img0 rectangles ;;

print_endline (generate_svg_code img);;
