program test;

const
	cons1 = 11;
	cons2 = 'a';

type
	pse = ^integer;
	t0 = array [0] of string;
	t1 = array [5] of string;
	i0 = 1..5;
	e0 = (lundi, mardi, mercredi, jeudi, vendredi, samedi, dimanche);
	r0 = record r1, r2, r3 : integer; r4, r5 : string end;

var
	v32, v31, v23, v21, v22 : integer;
	v2 : boolean;
	v3 : string;
	v4 : t1;
	v5 : t0;
	v6 : e0;

procedure proc1(paramCt : boolean ; var param1, param2 : integer);
	var
		var2 : v5;
		testInt1, testInt2, testInt3 : integer;

	begin
        	testInt1 := 1;
        	testInt2 := 2;
        	testInt3 := 3 - testInt1;
        	testInt1 := testInt2 + testInt3;
	end;


procedure proAc1(paraAmCt : boolean ; var parAam1, parAam2 : integer);
	const Acons2 = true;
	var Avar2 : integer;

	begin
        parAam1 := 42 / 3 + 4;
        parAam2 := 23 mod 3 + 4 * 5 - 6;
	end;


procedure testTabulation(BparamCt : boolean ; var Bparam1, Bparam2 : t1);
	const Bcons2 = true;
	var Bvar2 : integer;

	begin

	end;

function tryIt(var Bparam1 : t1) : string;
	const blabla = 'aa';
	var Bvar45 : integer;

	begin
	end;


begin
	v32 := 2;
	v31 := 5;
	proAc3(true, v32 * v31, 4200);

end.

