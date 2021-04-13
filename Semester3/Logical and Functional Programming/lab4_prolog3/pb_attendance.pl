%write a predicate to compute all sublists of a list

% subset(l1..ln) =
%	[], n = 0
%	l1 + subset(l2..ln)
%	subset(l2..ln)

% subset(L:list, R:list)
% subset(i, o)
sublist([], []).
sublist([H|T],R):- R=[H|R1],
    sublist(T, R1).
sublist([_|T],R):- sublist(T,R).


allsublists(L, R):- findall(Rez, sublist(L, Rez), R).
