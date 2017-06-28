%+TODO: <Nicolescu> <Roxana-Elena> <321CA>

:- ensure_loaded('T3t.pl').
:- ensure_loaded('T3base.pl').
:- dynamic next_tile/2.


% initial_game_state(-GameState).
% Întoarce în GameState starea inițială a jocului.
initial_game_state(([], [], [])).


% get_game_tiles(+GameState, -PlacedTileList)
% Întoarce lista de cărți rotite plasate în joc.
% Lista este o listă de triplete conținând:
% - coordonatele (X, Y) ale spațiului unde este cartea
% - identificatorul cărții (#1..#10)
% - identificatorul rotației (R0..R3)
get_game_tiles(GameState, []) :- initial_game_state(GameState).
get_game_tiles((list1,_,_), list1).

% get_open_paths(+GameState, -Paths)
% Întoarce în Paths o listă de trasee care pornesc
% dintr-un punct de intrare și nu ajung într-un punct
% de ieșire. Elementele din fiecare traseu vor fi citite
% folosind predicatele get_path_*
get_open_paths(GameState, []) :- initial_game_state(GameState).
get_open_paths((_, list2, _), list2).

% get_closed_paths(+GameState, -ClosedPaths)
% Întoarce în ClosedPaths traseele care pornesc
% dintr-un punct de intrare și ajung într-un punct
% de ieșire. Elementele din fiecare traseu vor fi citite
% folosind predicatele get_path_*
get_closed_paths(GameState, []) :- initial_game_state(GameState).

get_closed_paths((_, _, list3), list3).


% get_path_entry(+Path, -Point)
% Întoarce în Point o pereche (X, Y) care este punctul
% de intrare pentru un traseu. Pentru X și Y întoarse
% trebuie ca entry_point(X, Y, _) să fie adevărat.
get_path_entry(((X, Y), _),(X, Y)) :- entry_point(X, Y, _).

% get_path_tiles(+Path, -IDs)
% Întoarce în IDs o listă de perechi (TID, RID)
% care conține, în ordinea în care sunt parcurse de traseu,
% pentru fiecare carte parcursă identificatorul cărții și
% identificatorul rotației acesteia.
% Este posibil ca o carte să apară în traseu de mai multe ori,
% dacă traseul trece de mai multe ori prin ea.
get_path_tiles((Entry, [(_, ID) | Tail]), IDs) :- IDs = [ID|Rest], get_path_tiles((Entry, Tail), Rest).

%% get_tile(+Id, +Rot, -Tiles)
%% intorace lista de conexiuni corespunzatoare rotatiei
get_tile(Id, Rot, (P0, P1, P2, P3)) :- tile(P0, P1, P2, P3, Id),
										rotation(0, Rot).
get_tile(Id, Rot, (P3, P0, P1, P2)) :- tile(P0, P1, P2, P3, Id),
										rotation(1, Rot).
get_tile(Id, Rot, (P2, P3, P0, P1)) :- tile(P0, P1, P2, P3, Id),
										rotation(2, Rot).
get_tile(Id, Rot, (P1, P2, P3, P0)) :- tile(P0, P1, P2, P3, Id),
										rotation(3, Rot).

%% bad_card(+Id, +Rot)
%% intoarce true pentru o carte care este rotita degeaba
bad_card(Id, Rot) :- (Id == '#1', \+ rotation(0, Rot)); 
					(Id == '#6', \+ rotation(0, Rot)); 
					(Id == '#9', \+ rotation(0, Rot)); 
					(Id == '#10', \+ rotation(0, Rot));
					(Id == '#4', \+ (rotation(0, Rot)), \+(rotation(1, Rot))); 
					(Id == '#8', \+ (rotation(0, Rot)), \+(rotation(1, Rot))).

%% isBorder(+X, +Y, +Weight, +Height)
%% intoarce true daca (X, Y) este margine
isBorder(X, Y, W, H) :- X == 1; Y == 1; X == W; Y == H. 

% available_move(+GameState, -Move)
% Predicatul leagă argumentul Move la o mutare disponibilă
% în starea GameState a jocului. Formatul pentru Move trebuie
% să fie același ca și în cazul utilizării predicatelor
% get_move_*.
% Dacă Move este legat, predicatul întoarce true dacă mutarea
% este disponibilă.
% Dacă Move nu este legat, soluții succesive (obținute folosind
% comanda ; la consolă, sau obținute cu findall) vor oferi
% diverse mutări valide în starea de joc dată.
% findall(Move, available_move(State, Move), Moves) trebuie să
% întoarcă în Moves toate mutările valide în starea dată, fără
% duplicate.
available_move(GameState,((X, Y), Id, Rot)) :- width(W), height(H),
	between(1, W, X), between(1, H, Y),
	get_game_tiles(GameState, Tiles),
	\+(member(((X, Y),_, _), Tiles)),
	\+(center_space(X, Y)),
	get_tile(Id, Rot, (P0, P1, P2, P3)),
	\+ (bad_card(Id, Rot)),
	((X == 1, Y == 1, P0 \= 0, P0 \= 3, P3 \= 0, P3 \= 1);
	(X == 1, Y == H, P0 \= 0, P0 \= 1, P1 \= 0, P1 \= 3);
	(X == W, Y == H, P2 \= 0, P2 \= 3, P1 \= 0, P1 \= 1);
	(X == W, Y == 1, P2 \= 0, P2 \= 1, P3\= 0, P3 \= 3);
	(X == 1, Y \= 1, Y \= H, P0 \= 0);
	(X == W, Y \= 1, Y \= H, P2 \= 0);
	(Y == 1, X \= 1, X \= W, P3 \= 0);
	(Y == H, X \= 1, X \= W, P1 \= 0);
	(\+ (isBorder(X, Y, W, H)), ((XUp is X, YUp is Y - 1, member(((XUp, YUp), _, _), Tiles));
	(XD is X, YD is Y + 1,  member(((XD, YD), _, _), Tiles));
	(XL is X - 1, YL is Y, member(((XL, YL), _, _), Tiles));
	(XR is X + 1, YR is Y, member(((XR, YR), _, _), Tiles))))).


% Atenție! Folosirea celor 3 predicate get_move_* pe aceeași
% variabilă neinstanțiată Move trebuie să rezulte în legarea
% lui Move la o descriere completă a mutării, astfel încât
% available_move(FS, Move) să dea adevărat dacă mutarea
% descrisă este validă în starea GS a jocului.

% get_move_space(?Move, ?Space)
% Predicatul este adevărat dacă Space corespunde spațiului
% (X, Y) de pe hartă unde a fost pusă o carte în urma
% mutării Move.
% Vezi și observația de mai sus.
get_move_space(((X, Y), _, _),(X, Y)).

% get_move_tile_id(?Move, ?TID)
% Predicatul este adevărat dacă TID corespunde
% identificatorului ('#1'..'#10') cărții care a fost plasată
% pe hartă în urma mutării Move.
% Vezi și observația de mai sus.
get_move_tile_id(((_, _),Id, _), Id).

% get_move_rotation_id(?Move, ?RotID)
% Predicatul este adevărat dacă RotID corespunde
% identificatorului rotației ('R0'..'R3') cărții care a fost
% plasată în urma mutării Move.
% Vezi și observația de mai sus.
get_move_rotation_id(((_, _), _, R), R).

%% % apply_move(+GameStateBefore, +Move, -GameStateAfter)
%% % Leagă al treilea argument la starea de joc care rezultă
%% % în urma aplicării mutării Move în starea GameStateBefore.
apply_move(_, _, _) :- fail.
% pick_move(+GameState, +TID, -Move)
% Alege o mutare care folosește cartea cu identificatorul TID,
% pentru a fi aplicată în starea GameState. Mutarea este
% întoarsă în Move.
pick_move(_,_,_) :- fail.


% play_game(-FinalGameState)
% Joacă un joc complet, pornind de la starea inițială a jocului
% și continuând până când nu se mai poate pune cartea care
% este la rând.
% Cărțile de plasat se obțin folosind
% predicatul next_tile(+Time, -TID), unde Time este legat la
% numărul de mutări realizate până în momentul curent, iar
% predicatul next_tile va lega TID la un identificator de carte.
play_game(_) :- fail.



















































