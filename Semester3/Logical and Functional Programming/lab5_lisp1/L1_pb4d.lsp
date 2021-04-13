; d) Write a list to return the maximum value of the numerical atoms from a list, at superficial level.

; max_value(l1..ln) = -9999999, l=[]
;                     l1, if numberp(l1) and n=1
;                     max( l1, max_value(l2..ln) ), numberp(l1) 
;                     max_value(l2..ln), otherwise

(defun max_value(l)
    (cond
        ((null l) -9999999)
        ((and (numberp (car l)) (null (cdr l))) (car l))
        ((numberp (car l)) (max (car l) (max_value (cdr l))))
        (t (max_value (cdr l)))
    )
)

;(max_value '(A 4 B 6 2 7 C F 5)) => 7
;(max_value '(A 4 (B 8 2) 7 C 5)) => 7
;(max_value '(A 4 B 6 2 7 C F)) => 7