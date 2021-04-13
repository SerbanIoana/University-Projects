;2. Return the list of nodes on the k-th level of a binary tree of type (1).
;(node no-subtrees list-subtree-1 list-subtree-2 ...) (1)
;(A 2 B 0 C 2 D 0 E 0) (1)
;
;ex1: (A 2 B 2 D 0 E 2 G 0 H 0 C 1 F 0)
;ex2: (A 2 B 2 C 0 D 1 E 2 F 0 G 1 H 1 I 2 J 0 K 0 L 1 M 2 N 0 P 1 Q 1 R 2 S 0 T 0)
;
;A - radacina
;stanga - de la B 2

;getSubtrees(l1..ln,nrV,nrM,stanga) = list(stanga, ()), l=[]
;                                       list(stanga, l1..ln), nrV>nrM
;                                      getSubtrees(l3..ln, nrV+1, nrM+l2, stanga U l1 U l2), otherwise

(defun getSubtrees(l nrV nrM leftTree)
    (cond
        ((null l) (list leftTree nil))
        ((> nrV nrM) (list leftTree l))
        (t (getSubtrees (cddr l) (+ nrV 1) (+ nrM (cadr l)) (append leftTree (list (car l) (cadr l)))))
    )
)

;leftSubtree(l1..ln) = m1, m = getSubtrees(l3..ln, 0, 0, ())
(defun leftSubtree (l) (car (getSubtrees (cddr l) 0 0 nil)))

;rightSubtree(l1..ln) = m2, m = getSubtrees(l3..ln, 0, 0, ())
(defun rightSubtree (l) (cadr (getSubtrees (cddr l) 0 0 nil)))


;kthLevel(l1..ln,current_lvl,k) = [], l=[]
;                                  l1, current_lvl = k
;                                  kthLevel(leftSubtree(l1..ln),current_lvl+1,k) U kthLevel(rightSubtree(l1..ln),current_lvl+1,k), otherwise
;                                  

(defun kthLevel (l current_lvl k)
    (cond
        ((null l) nil)
        ((equal current_lvl k) (list (car l)))
        (t (append (kthLevel (leftSubtree l) (+ current_lvl 1) k) (kthLevel (rightSubtree l) (+ current_lvl 1) k)))
    )
)


;(kthLevel '(A 2 B 2 D 0 E 2 G 0 H 0 C 1 F 0) 0 2) => (D E F)
;(kthLevel '(A 2 B 2 C 0 D 1 E 2 F 0 G 1 H 1 I 2 J 0 K 0 L 1 M 2 N 0 P 1 Q 1 R 2 S 0 T 0) 0 2) => (C D M)
;(kthLevel '(A 2 B 2 C 0 D 1 E 2 F 0 G 1 H 1 I 2 J 0 K 0 L 1 M 2 N 0 P 2 Q 0 R 0) 0 4) => (F G Q R)

