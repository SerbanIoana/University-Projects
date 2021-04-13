; b) Write a function to get from a given list the list of all atoms, on any level, but on the same order. 
; Example:(((A B) C) (D E)) ==> (A B C D E)

; list_atoms(l1..ln) = () , l=()
;                       l1 U list_atoms(l2..ln), l1 is atom
;                       list_atoms(l1) U list_atoms(l2..ln), l1 is list

(defun list_atoms(l)
    (cond
        ((null l) nil)
        ((atom (car l)) (cons (car l) (list_atoms (cdr l))))
        ((listp (car l)) (append (list_atoms (car l)) (list_atoms (cdr l))))
    )
)

;(list_atoms '(((A B) C) (D E))) => (A B C D E)
;(list_atoms '(((A B) C) D E (F))) => (A B C D E F)
;(list_atoms '(A (B C) D (E F))) => (A B C D E F)