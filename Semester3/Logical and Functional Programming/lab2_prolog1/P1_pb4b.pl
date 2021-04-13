%b. Write a predicate to add value 1 after every even element from a list.
%
%add_1_even(l1..ln)= [], if n=0
%                    l1 U 1 U add_1_even(l2..ln), if l1%2=0
%                    l1 U add_1_even(l2..ln), if l1%2=1

%add_1_even(L:list,R:result list)
%(i,o)

add_1_even([],[]).
add_1_even([H|T],R):- 0 is mod(H,2),
    add_1_even(T,R1),
    R=[H,1|R1].
add_1_even([H|T],R):- 1 is mod(H,2),
    add_1_even(T,R1),
    R=[H|R1].
