Q = 1;
a = 1;
L = 10;
eps0 = 8.85e-12;
%em quantos pontos será realizda a integração
npartes = 100;
x = a:L/(npartes-1):(a+L); # Uniformly spaced points
y = 1./(x.^2);
r1 = trapz(x, y);
%integração pelo método dos trapézios
r1 = Q*r1/((4*pi*eps0)*L)
%Cálculo exato integral
r2 = 1/(4*pi*eps0)*Q/L*(1/a-1/(L+a))
%erro de r1
erro = (r2-r1)/r1;
Erro_percentual = erro*100