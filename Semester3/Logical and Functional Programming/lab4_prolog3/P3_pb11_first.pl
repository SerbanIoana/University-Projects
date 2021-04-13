%11. “Colouring” a map. n countries are given; write a predicate to
% determine all possibilities of colouring n countries with m colours,
% such that two adjacent countries not having the same colour.
%
% colour(N,M,r1..rm,Pos,Clr)= r1..rm, pos=N
%                             colour(N,M,clr U r1..rm,pos+1,1), clr!=r1,
%                               pos<N
%                             colour(N,M,r1..rm,pos,clr+1), clr=r1,
%                               clr<M
%
%colour(N:Int,M:Int,Pos:Int,Clr:Int,R:collector,Rez:result)
%colour(i,i,i,i,i,o) nondeterministic

colour(N,M,Pos,Clr,[],R):- Pos1 is Pos+1,
    colour(N,M,Pos1,Clr,[Clr],R).
colour(N,M,Pos,Clr,[H|T],Rez):- Clr=\=H,
    Pos<N,
    Pos1 is Pos+1,
    R=[Clr,H|T],
    colour(N,M,Pos1,1,R,Rez).
colour(N,M,Pos,Clr,[H|T],Rez):- Clr=:=H,
    Clr<M,
    Clr1 is Clr+1,
    colour(N,M,Pos,Clr1,[H|T],Rez).
colour(N,_,N,_,R,R).

% 1. generate solution = all ways of colouring a map (candidate =number
% (1,M))
% 2. check consecutive positions for equal numbers

%colour_wrapper(N,M)= colour(N,M,1,1,[])
%colour_wrapper(N:Int,M:Int,R:result list)
%colour_wrapper(i,i,o) nondeterministic
colour_wrapper(N,M,R):-colour(N,M,1,1,[],R).

%colour_all(N,M)= U colour_wrapper(N,M)
%colour_all((N:Int,M:Int,R:result list)
%colour_all(i,i,o)
colour_all(N,M,R):- findall(Rez, colour_wrapper(N,M,Rez), R).


