Steps:	Steps.ml
	ocamlc -annot -g str.cma Steps.ml
	ocamlopt str.cmxa Steps.ml -o Steps

doc:	Steps.ml
	mkdir -p -v html
	ocamldoc -html Steps.ml -d html
