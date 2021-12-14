Q = 1;
a = 1;
L = 10;
eps0 = 8.85e-12;
%em quantos pontos ser� realizda a integra��o
npartes = 100;
x = a:L/(npartes-1):(a+L); # Uniformly spaced points
y = 1./(x.^2);
r1 = trapz(x, y);
%integra��o pelo m�todo dos trap�zios
r1 = Q*r1/((4*pi*eps0)*L)
%C�lculo exato integral
r2 = 1/(4*pi*eps0)*Q/L*(1/a-1/(L+a))
%erro de r1
erro = (r2-r1)/r1;
Erro_percentual = erro*100