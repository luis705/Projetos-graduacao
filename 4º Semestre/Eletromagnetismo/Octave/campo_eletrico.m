function vetor_campo = campo_eletrico(r1, r2, q, epsr)
	eps0 = 8.85e-12;
	direcao = r1 - r2;
	modulo = sum(direcao .^2).^0.5;
	vetor_campo = q .* direcao / (4 * pi * eps0 * epsr * modulo .^3);
endfunction
