%11. a. Replace all occurrences of an element from a list with another
% element e.
%
%replace(l1..ln,el,er)= [], if n=0
%                          er U replace(l2..ln,el,er), if l1=el
%                          l1 U replace(l2..ln,el,er), otherwise
%
%replace(L:list,EL:elem in list,ER:elem,R:result list)
%(i,i,i,o)
replace([],_,_,[]).
replace([H|T],EL,ER,R):- H =:= EL,
    !,
    replace(T,EL,ER,R1),
    R=[ER|R1].
replace([H|T],EL,ER,R):-
    replace(T,EL,ER,R1),
    R=[H|R1].
%
% b. For a heterogeneous list, formed from integer numbers and list of
% numbers, define a predicate to determine the maximum number of the
% list, and then to replace this value in sublists with the maximum
% value of sublist.
% Eg.: [1, [2, 5, 7], 4, 5, [1, 4], 3, [1, 3, 5, 8, 5, 4], 5, [5, 9, 1],2] =>
% [1, [2, 7, 7], 4, 5, [1, 4], 3, [1, 3, 8, 8, 8, 4], 5, [9, 9, 1], 2]
%
% i. Predicate to find the maximum number in a heterogeneous list.
%    maximum(l1..ln)= l1, if n=1
%                     maximum(l2..ln), if is_list(l1)
%                     maximum(l2..ln), if number(l1)
%                                      and l1<maximum(l2..ln)
%                     l1, if number(l1) and l1>=maximum(l2..ln)
%
%maximum(L:list,M:maximum integer value)
%maximum(i,o)
maximum([H],H).
maximum([H|T],M):-maximum(T,M),
    is_list(H),
    !.
maximum([H|T],M):-maximum(T,M),
    H<M,
    !.
maximum([H|_],H).
%
% ii. Main predicate to replace max value of each sublist with the max
% value from the entire list.
%
% main_aux(l1..ln, m)= [], if n=0
%                      replace(l1,m,maximum(l1)) U main_aux(l2..ln), if
%                          is_list(l1)
%                      l1 U main_aux(l2..ln), otherwise
%
%
%main_aux(L:list,M:max integer number,R:result list)
%(i,i,o)
main_aux([],_,[]).
main_aux([H|T],M,R):- is_list(H),
    !,
    maximum(H,MSub),
    replace(H,M,MSub,RSub),
    main_aux(T,M,R1),
    R=[RSub|R1].
main_aux([H|T],M,R):- main_aux(T,M,R1),
    R=[H|R1].
%
%main(l1..ln) = main_aux(l1..ln, maximum(l1..ln))
%
%main(L:list,R:result list)
%(i,o)
main(L,R):- maximum(L,M),
    main_aux(L,M,R).


%implemented during lab
%func(L:list, R:result)
%(i,o)
%
func([],[]).
func([H|T],R):-is_list(H),
    !,
    H=[H1|_],
    func(T,R1),
    R=[H1|R1].
func([_|T],R):-func(T,R).
