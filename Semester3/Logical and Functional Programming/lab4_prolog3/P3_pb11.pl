%11. “Colouring” a map. n countries are given; write a predicate to
% determine all possibilities of colouring n countries with m colours,
% such that two adjacent countries not having the same colour.
%
% 1. generate solution = all ways of colouring a map (candidate =number
% (1,M))
% 2. check consecutive positions for equal numbers

%candidate(M)= 1.M
%              2.candidate(M-1) ,M>0
%
%candidate(M:Int, E:Int)
%candidate(i,o)
%candidate(0, 0):- !.
candidate(M, M).
candidate(M, E):- M1 is M - 1,
    M1>0,
    candidate(M1, E).

% colour(N,M,Pos,r1..rm)= r1..rm, pos=N
%                         colour(N,M,pos+1,e U r1..rm), where
%                          e=candidate(M), if pos<N, e!=r1

%colour(N:Int,M:Int,Pos:Int,R:collector,Rez:result)
%colour(i,i,i,i,o) nondeterministic
colour(N,_,N,[H|T],[H|T]).%:- H is 3.
colour(N,M,Pos,[H|T],Rez):-  Pos < N,
    candidate(M,E),
    E=\=H,
    Pos1 is Pos+1,
    colour(N,M,Pos1,[E,H|T],Rez).

% colour_wrapper(N,M)= colour(N,M,1,[e]), where e=candidate(M)
% colour_wrapper(N:Int,M:Int,R:result list)
% colour_wrapper(i,i,o) nondeterministic
colour_wrapper(N,M,R):- candidate(M,E),
    colour(N,M,1,[E],R).

%colour_all(N,M)= U colour_wrapper(N,M)
%colour_all((N:Int,M:Int,R:result list)
%colour_all(i,i,o)
colour_all(N,M,R):- findall(Rez, colour_wrapper(N,M,Rez), R).




