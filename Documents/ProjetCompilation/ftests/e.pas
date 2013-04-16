program test2;

var
	x, y, i : integer;

begin
	x := 333;
	y := 5;
	
	IF x + y - 1 = 7 THEN BEGIN
	  x := 42;
	END ELSE BEGIN
	  y := 53;
	END;
	
	IF x + y - 1 = 7 THEN BEGIN
	  x := 42;
	END;
	
	i := 0;

	IF 1 > 2 THEN BEGIN
	  x := 36;
	END;
	
	WHILE i = 3 DO BEGIN
		x := 6;
	END;
	
	i := 222;
	
	REPEAT 
		i := i + 1
	UNTIl i > 555;
	
end.

