; a) Write a function to return the sum of two vectors.

;vectors_sum(l1..ln,p1..pm) = (), length(l) != length(p)
;                                (), l=() or p=()
;                               l1+p1 U vectors_sum(l2..ln,p2..pm), otherwise

;mylength(l1..ln) = 0, l=[]
;                   1+mylength(l2..ln), otherwise
;
(defun mylength(l)
    (cond
        ((null l) 0)
        (t (+ 1 (mylength (cdr l))))
    )
)

(defun vectors_sum(v1 v2)
    (cond
        ((not (equal (mylength v1) (mylength v2))) nil)
        ((or (null v1) (null v2)) nil)
        (t (cons (+ (car v1) (car v2)) (vectors_sum (cdr v1) (cdr v2))))
    )
)

;(vectors_sum '(1 2 3) '(6 7 8)) => (7 9 11)
;(vectors_sum '(1 2 3) '(2)) => NIL
