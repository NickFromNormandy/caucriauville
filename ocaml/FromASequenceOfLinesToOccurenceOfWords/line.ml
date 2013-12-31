
(* #load "str.cma";; *)
 
(** The goal is to:
  - read a text file
  - parse it and read each word.
  - a word is a sequence of letters 
  - print a list of occurence of each word
 *)

module StringMap = Map.Make(String);;
module SetOfInt = Set.Make(struct type t = int let compare = compare end);;

(** Get a set of 3 smallest values
*)
let find_max my_map =
  let max_values = ref SetOfInt.empty in
  let min_elem = SetOfInt.min_elt !max_values in
  let find_max my_key my_value =
    max_values :=  SetOfInt.add my_value !max_values in
  StringMap.iter find_max my_map;
  !max_values;;


(** If the word does not belong to the map's domain then
    add an association (word, 1)
    else add 1 to the counter associated with the word.
*)        
let compute_new_map my_key my_map = 
  if (StringMap.mem my_key my_map) then 
    (let value = (StringMap.find my_key my_map) in 
     StringMap.add my_key (value+1) my_map)
  else (StringMap.add my_key 1 my_map);;

(** Create a map from a list of words
   each words that belong to the list will be part of the domain of the map
   the number of occurence the word in the list will be part of the range of the map.
   the map will have a word and its number of occurence
*)
let my_word_to_count my_list_of_words =
  let rec compute_word_to_count my_list_of_words my_map =
    match my_list_of_words with
      [] -> my_map
    | head::tail -> compute_word_to_count tail (compute_new_map head my_map)  in
  compute_word_to_count my_list_of_words StringMap.empty;;


(** Read a file denoted by the variable filename
   return a list of words
   each word belong to one of the lines.
   a word is a sequence of letter (lower or upper case)
 *)  
let read_file filename = 
  let lines = ref [] in
  let chan = open_in filename in
  try
    while true; do
      lines := (List.append (Str.split (Str.regexp "[^A-Z^a-z]+") (input_line chan))  !lines);
      flush stdout;
    done; []
  with End_of_file ->
    print_string "**************************************************End of file\n";
    flush stdout;
    close_in chan;
    List.rev !lines ;;

(** This function is not used  
 *)
let rec print_my_list myStringMap myString =
  match myString with
    [] -> print_string "The list is empty"; myStringMap
  | head::tail -> print_string head; print_string "...\n"; print_my_list (StringMap.add "titi" "toto" myStringMap) tail;;
  
(** Print a list of words to the console 
 *)
let print_my_list_of_words my_list = 
  print_string "[";
  let counter = ref 0 in
  let rec print_it my_list_of_words =
    match my_list_of_words with 
      [] -> print_string "\n"
    | head::tail -> print_string head;
		    print_string ",";
		    counter := !counter+1;
		    if ((!counter mod 10)= 0) then print_string "\n";
		    print_it tail 
  in
  print_it my_list;;

(** Print word to count *)
let rec print_word_to_count my_map =
  print_string "word to count s";
  let 
    print_key_value my_key my_value = print_string "coucou:";
    print_string my_key;print_string "->";
    (print_string (string_of_int(my_value)));
    print_string "\n"; 
  in
  StringMap.iter print_key_value my_map;;
  
(** Helper function to print an int value used with iter *)
let print_myint my_int = 
  print_int my_int; print_string ",";;

(** print each int value that belong to the passed-in set*)
let print_my_set my_set =
  SetOfInt.iter print_myint my_set;;

(**  Create the list of words*)
let my_list_of_words = read_file "toto.txt" in
    print_int (List.length(my_list_of_words));
    print_my_list_of_words my_list_of_words;
    let myWordToCount = (my_word_to_count my_list_of_words) in
    print_word_to_count myWordToCount;print_my_set (find_max myWordToCount);;
