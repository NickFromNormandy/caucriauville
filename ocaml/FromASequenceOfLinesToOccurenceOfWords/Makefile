line:	line.ml
	ocamlc -annot -g str.cma line.ml
	ocamlopt str.cmxa line.ml -o line

doc:	line.ml
	mkdir -p -v html
	ocamldoc -html line.ml -d html
