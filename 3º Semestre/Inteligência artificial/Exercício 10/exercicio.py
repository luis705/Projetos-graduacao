import numpy as np
import pandas as pd

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
dados = pd.read_csv('iris.csv')
# Entradas
X = np.array([
            [-1 for _ in range(dados.shape[0])],
            dados['sepal_length'].to_list(),
            dados['sepal_width'].to_list(), 
            dados['petal_length'].to_list(), 
            dados['petal_width'].to_list()]).transpose()

# Saídas desejadas
especies = np.array(dados['species'].to_list())
d = np.zeros(especies.shape)
for i in range(d.shape[0]):
    if especies[i] == 'setosa':
        d[i] = 1
    else:
        d[i] = 0

# Valores a serem obtidos
y = np.zeros(d.shape[0])
pesos = np.random.randn(X.shape[1])
eta = .2
epoca = 0
erro = 1
erros = [1 for i in range(d.shape[0])]


while erro:
    epoca += 1

    # Calcula o valor de ativação para a entrada
    u = np.dot(X, pesos)
    y = ativacao(u)

    # Calcula erro: d - y
    erros = d.transpose() - y
    pesos += eta * np.dot(erros, X)

    erro = max(abs(erros))
    if erro == 0:
        break
        
# Realizando as previsões
u = np.dot(X, pesos)
y = ativacao(u)

print('Saídas obtidas após o treino: ', end='')
print_valores(y, 'y')
print(f'Número de épocas: {epoca}')
print('Pesos finais: ', end='')
print_valores(pesos, 'w')
