function res = Msombrero(s, Muestra)
	res = (Muestra.^s)'*arrayfun(@log, Muestra)  /  length(Muestra);