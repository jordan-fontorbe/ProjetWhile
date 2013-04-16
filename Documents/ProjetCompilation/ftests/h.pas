program test;

var
	j, k : integer;
	l, m : real;
	Menteur, Verite, Tueur, Doute : boolean;

procedure proc(p1 : boolean ; var p2, p3 : integer);
	begin
		
	end;

begin
	j := 2;
	k := 5;
	l := 3;
	m := 6;

	{Tests d affectation pour des Operations}
	Menteur := false;
	Verite := true;
	Tueur := Verite XOR Menteur;
	Verite := Not Menteur;
	Doute := Verite OR Menteur;

	{Tests d affectation pour des comparaisons}
	Menteur := j < k;
	Verite :=  j > k;
	Menteur := j <= k;
	Verite := j >= k;
	
	Menteur := l < m;
	Verite :=  l > m;
	Menteur := l <= m;
	Verite := l >= m;
	
	Tueur := l < k;
	Doute :=  l > k;
	Tueur := l <= k;
	Doute := l >= k;

	j := k mod j;

	j := j div k;


end.

