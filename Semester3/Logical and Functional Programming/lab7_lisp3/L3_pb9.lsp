
;9. Write a function that removes all occurrences of an atom from any level of a list.

;removeOccurences(elem,remove_elem) = list(elem) , if elem is atom, n!=remove_elem
;                                  U removeOccurences(elem_i, remove_elem) , if elem is list, where i=1,k

(defun removeOccurences(elem remove_elem)
    (cond
        (
            (and (atom elem) (not (eq elem remove_elem))) 
            (list elem)
        )
        (
            (listp elem) 
            (list
                (mapcan #'
                (lambda (new_elem)
                    (removeOccurences new_elem remove_elem)
                )    
                elem
            ))
        )
    )
)

(defun wrapperRemove(elem remove_elem)
    (car (removeOccurences elem remove_elem) ))
    

    
(print (wrapperRemove '(1 3 (3 A 3) 4 (3) 5 8 3) 3))
(print (wrapperRemove '(A B 1 (Z 2 C Z D 3) 4 Z Z) 'Z))