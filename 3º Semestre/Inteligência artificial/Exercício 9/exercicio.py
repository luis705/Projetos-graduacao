import numpy as np
import time

def ativacao(x):
    y = x.copy()
    for i in range(len(y)):
        if y[i] <= 0:
            y[i] = 0
        else:
            y[i] = 1
    return y

def print_valores(valores, letra):
    for i in range(len(valores)):
        if i != len(valores) - 1:
            print(f'{letra}{i}: {valores[i]}', end=', ')
        else:
            print(f'{letra}{i}: {valores[i]}')

# Inicialização de variáveis
dados = np.loadtxt('data.txt')
X = dados[:,:3]
d = dados[:, 3:]
y = np.zeros(d.shape)
pesos = np.random.randn(3)
eta = .2
epoca = 0
erro = 1

# Escrevendo na tela os pesos iniciais
print('Pesos iniciais: ', end='')
print_valores(pesos, 'W')

inicio = time.time()
while erro:
    epoca += 1

    # Calcula o valor de ativação para essa entrada
    u = np.dot(X, pesos)
    y = ativacao(u)

    # Calcula o erro: d - y
    erros = d.transpose() - y
    erros = erros[0]
    pesos += eta * np.dot(erros, X)

    # Mostrando os valores da época atual
    print(f'\nÉpoca: {epoca}')
    print('\tPesos: ', end='')
    print_valores(pesos, 'W')
    print('\tErros: ', end='')
    print_valores(erros, 'E')
    print('\tSaídas: ', end='')
    print_valores(y, 'y')

    erro = max(abs(erros))
    if abs(erro) == 0:
        break
fim = time.time()

# Realizando as previsões
u = np.dot(X, pesos)
y = ativacao(u)

print('\n\nSaídas obtidas após o treino: ', end='')
print_valores(y, 'y')
print('\nValores do treino: ')
print(f'\tNúmero de épocas: {epoca}')
print(f'\tTempo de treino: {fim - inicio} segundos')
