%a. Write a predicate to determine the difference of two sets.
%
%set_diff(l1..ln,m1..mk)= [], if n=0
%                         l1 U
%                         set_diff(l2..ln,m1..mk),not(member(l1,m1..mk))
%                         set_diff(l2..ln,m1..mk), otherwise

%set_diff(L:set,M:set,R:result set)
%(i,i,o)
set_diff([],_,[]).
set_diff([H|T],M,R):-not(member(H,M)),
    set_diff(T,M,R1),
    R=[H|R1].
set_diff([H|T],M,R):-member(H,M),
    set_diff(T,M,R).
