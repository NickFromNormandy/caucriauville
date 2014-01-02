
(* #load "str.cma";; *)
 
(** The module is to:
  - create a list of words from a text file
  - create a map that expresses the occurence of each word
  - a word is a sequence of letters 
  - print a list of occurence of each word
 *)

module Line =
  struct

    module StringMap = Map.Make(String);;
    module SetOfStrings = Set.Make(String);;
    module SetOfInt = Set.Make(struct type t = int let compare = compare end);;
    module IntMap = Map.Make(struct type t = int let compare = compare end);;

    (** Get a set of 3 smallest values *)
    let find_max my_map =
      let max_values = ref SetOfInt.empty in
      let min_elem = SetOfInt.min_elt !max_values in
      let find_max my_key my_value =
	max_values :=  SetOfInt.add my_value !max_values in
      StringMap.iter find_max my_map;
      !max_values;;
      
      
    (** Helper function: If the word does not belong to the map's domain then
    add an association (word, 1) to the map
    else add 1 to the counter associated with the existing word.*)        
    let compute_new_map my_key my_map = 
      if (StringMap.mem my_key my_map) then 
	(let value = (StringMap.find my_key my_map) in 
	 StringMap.add my_key (value+1) my_map)
      else (StringMap.add my_key 1 my_map);;
      
    (** Create a map from a list of words
   - each words that belong to the list will be part of the domain of the map
   - the number of occurence the word in the list will be part of the range of the map.
   - the map will have a word and its number of occurence
     *)

    let create_a_map_word_occurence_from_listofwords my_list_of_words =
      let rec compute_word_to_occurence my_list_of_words my_map =
	match my_list_of_words with
	  [] -> my_map
	| 
	  head::tail -> compute_word_to_occurence tail (compute_new_map head my_map)  in
      compute_word_to_occurence my_list_of_words StringMap.empty;;


    (** Read a file d by filename
        - return a list of words
        - each word belongs to excatly one line 
        - there is duplicated word in the list
        - a word is a sequence of letters 
        - a letter is either lower or upper case
     *)  

    let create_a_list_of_words_from_a_text_file filename = 
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
      
    (** This function is not used  *)
    let rec print_my_list myStringMap myString =
      match 
	myString 
      with
	[] -> print_string "The list is empty"; myStringMap
      |
	head::tail -> print_string head; print_string "...\n"; print_my_list (StringMap.add "titi" "toto" myStringMap) tail;;
      
    (** Print a list of words to the console  *)
    let print_my_list_of_words my_list = 
      print_string "[";
      let counter = ref 0 in
      let rec print_it my_list_of_words =
	match 
	  my_list_of_words 
	with 
	  [] -> print_string "\n"
	| 
	  head::tail -> print_string head;
			match 
			  tail
			with
			  [] -> print_string "]";
			|
			  head2::tail2 -> print_string ",";
			counter := !counter+1;
			if ((!counter mod 10)= 0) then print_string "\n";
			print_it tail 
      in
      print_it my_list;;
      
    (** Print the map word to occurence *)
    let rec print_word_to_occurence my_map =
      print_string "word to occurence:";
      let print_key_value my_key my_value = 
	print_string "association word->occurence:";
	print_string my_key;print_string "->";
	(print_string (string_of_int(my_value)));
	print_string "\n"; 
      in
      StringMap.iter print_key_value my_map;;

    let print_occurence_to_word my_map =
      print_string "Occurence to word:";
      let print_key_value my_key my_value =
	print_string "association occurence->word:";
	print_int my_key;print_string "->";
	print_my_list_of_words my_value;
	print_string "\n";
      in
      IntMap.iter print_key_value my_map;my_map;;

    (** Print each int value that belongs to the passed-in set*)
    let print_my_set my_set =
      (** Helper function to print an int value used with iter *)
      let print_myint my_int = 
	print_int my_int; print_string "," in
      SetOfInt.iter print_myint my_set;;

    let helper_add_apair_occurence_word_to_the_map_occurenceToWord my_word my_occurence my_map =
      if (IntMap.mem my_occurence my_map) then 
	(let list_of_words = (IntMap.find my_occurence my_map) in 
	 IntMap.add my_occurence (my_word::list_of_words) my_map)
      else (IntMap.add my_occurence (my_word::[])  my_map);;

    let create_map_occurence_to_word word_to_occurence = 
      let occurence_to_word = ref IntMap.empty in
      let help_map my_word my_occurence = (occurence_to_word := (helper_add_apair_occurence_word_to_the_map_occurenceToWord my_word my_occurence !occurence_to_word)) in
      StringMap.iter help_map word_to_occurence;!occurence_to_word;;
      
    (** Create the list of words and then create the map that will mach each word with its occurence*)
    let my_list_of_words = create_a_list_of_words_from_a_text_file "toto.txt" in
	print_string "Length of the list of words:";
	print_int (List.length(my_list_of_words));
	print_string "\n";
	print_my_list_of_words my_list_of_words;
	let myMapWordToOccurence = (create_a_map_word_occurence_from_listofwords my_list_of_words) in
        let myMapOccurenceToWord = (create_map_occurence_to_word myMapWordToOccurence) in
	(print_word_to_occurence myMapWordToOccurence);
	(print_occurence_to_word myMapOccurenceToWord);
        myMapWordToOccurence;;

    (** Helper function: If the word does not belong to the map's domain then
    add an association (word, 1) to the map
    else add 1 to the counter associated with the existing word.*)        
    let compute_new_map_occurence my_key my_map = 
      if (StringMap.mem my_key my_map) then 
	(let value = (StringMap.find my_key my_map) in 
	 StringMap.add my_key (value+1) my_map)
      else (StringMap.add my_key 1 my_map);;
	

	
  end;;
