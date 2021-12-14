K = 8.9e9;
q = 7;
a = .1;
l = 8;
partes = 10000;

	
fprintf("Quantidade de partes = %d", partes);
disp("");

% Cálculos numéricos
x = [a : (l / partes) : a+l];
dQ = q / partes;
dE = K .* dQ ./ (x .^2);
SolNum = sum(dE)

% Cálculos analíticos
SolExata = K * q / (a * (a + l))

% Resultados finais
erro = abs(SolNum - SolExata) / SolExata * 100;
fprintf("Erro percentual = %d%%", erro);
disp("");
disp("");

