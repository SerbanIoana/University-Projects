; c) Write a function that, with a list given as parameter, inverts only continuous sequences of atoms. 
; Example:(a b c (d (e f)) g h i) ==> (c b a (d (f e)) i h g)

; invert_list(l1..ln, col) = col, l=[]
;                               invert_list(l2..ln, l1 U col), atom(l1) -> cons
;                               col U invert_list(l1,[]) U invert_list(l2..ln,[]), listp(l1)  -> append + cons

;invert_list '(a b) '() 
;   invert_list '(b) '(a)
;       invert_list '() '(b a) -> '(b a)


;invert_list '((d (e f)) g h i) '() -> () U invert_list '(d (e f)) '() U invert_list '(g h i) '() -> '((d (f e)) i h g))

;invert_list '(d (e f)) '() 
;   invert_list '((e f)) '(d) -> '(d) U invert_list '(e f) '() U invert_list '() '() -> '(d (f e))


(defun invert_list(l col)
    (cond
        ((null l) col)
        ((atom (car l)) (invert_list (cdr l) (cons (car l) col)))
        ((listp (car l)) (append col (cons (invert_list (car l) nil) (invert_list (cdr l) nil))))
    )
)

;(invert_list '(a b c (d (e f)) g h i) '())
;(invert_list '(a b c (d (e f) g h i)) '())
;(invert_list '(a b c d e) '()) => (E D C B A)
;(invert_list '(a b c (d) e) '()) => (C B A (D) E)