(**

   - We want to reach the step n
   - We can do 1 step, 2 steps, or 3 steps at a time.


 **)

let findCombinaisonOfSteps n =
  let mySetOfTriplets = ref [] in
  let iterateOnSteps n =
    for z = 0 to n do
      for y = 0 to n do
	(let x = n-y*2-z*3 in
	
	(if (x>=0) then
	mySetOfTriplets := (x,y,z)::!mySetOfTriplets));
      done;
    done;
    !mySetOfTriplets
  in
  iterateOnSteps n;;


let generateAsequenceFullOfx x thelength =
  let rec myIter mylist mylength =
    if mylength == 0 then
      mylist
    else
      myIter (x::mylist) (mylength-1) in
  myIter [] thelength;;


let generateProductSeqAndVal mySequence myValue =
  
     
let print_triplet myTriplet =
match myTriplet with
  (x,y,z) -> print_string "(";
	     print_int x;
	     print_string ",";
	     print_int y;
	     print_string ",";
	     print_int z;
	     print_string ")";;

let theResults = findCombinaisonOfSteps 5;;

let rec printMyResult myResults =
  match myResults with
    [] -> print_string "Vide"
  | head::tail -> print_triplet head;print_string ",";printMyResult tail;;

printMyResult theResults;;
