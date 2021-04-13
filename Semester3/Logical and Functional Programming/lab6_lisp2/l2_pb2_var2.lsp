
(defun getSubtrees(l nrV nrM stanga)
    (cond
        ((null l) (list stanga nil))
        ((> nrV nrM) (list stanga l))
        (t (getSubtrees (cddr l) (+ nrV 1) (+ nrM (cadr l)) (append stanga (list (car l) (cadr l)))))
    )
)

;(defun leftSubtree (l) (car (getSubtrees (cddr l) 0 0 nil)))
;(defun rightSubtree (l) (cadr (getSubtrees (cddr l) 0 0 nil)))

;option with lambda function to avoid redundant call of getSubtrees
;kthLevel(l1..ln,current_lvl,k) = []  , l = []
;                                  l1, current_lvl = k
;                                  kthLevel(subtree,current_lvl+1,k) U kthLevel(subtree,current_lvl+1,k), otherwise 
;                                           where subtree = getSubtrees(l3..ln, 0, 0, ())
;                                  


(defun kthLevel (l current_lvl k)
    (cond
        ((null l) nil)
        ((equal current_lvl k) (list (car l)))
        (t ((lambda (subtree)
                (append 
                    (kthLevel (car subtree) (+ current_lvl 1) k) 
                    (kthLevel (cadr subtree) (+ current_lvl 1) k)
                )
            )
            (getSubtrees (cddr l) 0 0 nil)
            )
        )
    )
)