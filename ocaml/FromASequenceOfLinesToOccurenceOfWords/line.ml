
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
      
    (** Helper function: If the word does not belong to the map's domain then
    add an association (word, 1) to the map
    else add 1 to the counter associated with the existing word.*)        
    
    (** Read a file by a filename
        - create a map words -> occurence
        - create a map occurence -> words
        - each word belongs to one or severa lines
        - there is duplicated word in the list
        - a word is a sequence of letters 
        - a letter is either lower or upper case
     *)  
    let create_a_map_word_occurence_from_a_text_file filename = 
      let chan = open_in filename in
      let the_map = ref StringMap.empty in
      let my_regexp = (Str.regexp "[^A-Z^a-z]+") in
      let compute_new_map my_key = 
	(try 
	    let value = (StringMap.find my_key !the_map) in 
	    the_map := (StringMap.add my_key (value+1) !the_map);
	    ();
	  with Not_found ->
	    the_map := (StringMap.add my_key (1) !the_map);
	    ();
	) in
      try
	while true; do
	  let my_line = (input_line chan) in 
	  let list_of_words = Str.split my_regexp my_line in
	  List.iter compute_new_map list_of_words;
	done; !the_map
      with End_of_file ->
	close_in chan;
	!the_map;;      


    (** Create an association of the map word->occurence *)
    let helper_add_apair_occurence_word_to_the_map_occurenceToWord my_word my_occurence my_map =
      if (IntMap.mem my_occurence my_map) then 
	(let list_of_words = (IntMap.find my_occurence my_map) in 
	 IntMap.add my_occurence (my_word::list_of_words) my_map)
      else (IntMap.add my_occurence (my_word::[])  my_map);;

    (** Create a map occurence->word using the map word->occurence *)
    let create_map_occurence_to_word word_to_occurence = 
      let occurence_to_word = ref IntMap.empty in
      let help_map my_word my_occurence = 
	(occurence_to_word := (helper_add_apair_occurence_word_to_the_map_occurenceToWord my_word my_occurence !occurence_to_word)) in
      StringMap.iter help_map word_to_occurence;!occurence_to_word;;
      
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

    let  print_occurence_to_word my_map =
      print_string "Occurence to word:";
      let print_key_value my_key my_value =
	print_string "association occurence->words:";
	print_int my_key;print_string "->";
	print_my_list_of_words my_value;
	print_string "\n";
      in
      IntMap.iter print_key_value my_map;my_map;;

    (** Create the list of words and then create the map that will mach each word with its occurence*)
    let myMapWordToOccurence = create_a_map_word_occurence_from_a_text_file "toto.txt" in

        let myMapOccurenceToWord = create_map_occurence_to_word myMapWordToOccurence in
	let number_of_words = ref 0 in
	let count_words word occurence = number_of_words := !number_of_words + occurence in
	(print_string "Numer of words in the file");
	(print_int !number_of_words);

	(StringMap.iter count_words myMapWordToOccurence);
	(print_string "\n");
	(print_string "Number of unique words in the file");
	(print_int (StringMap.cardinal myMapWordToOccurence));
	(print_string "\n");
	(print_word_to_occurence myMapWordToOccurence);
	(print_occurence_to_word myMapOccurenceToWord);;
(*
        myMapWordToOccurence;;
 *)


  end;;
