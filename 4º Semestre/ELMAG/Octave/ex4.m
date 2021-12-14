% Posição do observador
fflush(stdout);
x_obs = input('Entre com a componente x do observador: ');
fflush(stdout);
y_obs = input('Entre com a componente y do observador: ');
fflush(stdout);
z_obs = input('Entre com a componente z do observador: ');	
pos_observador = [x_obs, y_obs, z_obs]

% Posição da carga
fflush(stdout);
x_carga = input('Entre com a componente x da carga: ');
fflush(stdout);
y_carga = input('Entre com a componente y da carga: ');
fflush(stdout);
z_carga = input('Entre com a componente z da carga: ');	
pos_carga = [x_carga, y_carga, z_carga]

% Valor da carga e permeabilidade relativa
fflush(stdout);
q = input('Entre com o módulo da carga: ');
fflush(stdout);
epsr = input('Entre com a permeabilidade relativa do meio: ');
q
epsr

E = campo_eletrico(pos_observador, pos_carga, q, epsr);
printf('\nO campo elétrico observado é o vetor (%.4f, %.4f, %.4f)\n', E(1), E(2), E(3));
printf('O módulo do campo elétrico observado é %f\n', sum(E.^2));
