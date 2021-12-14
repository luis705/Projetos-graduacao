import pandas as pd
from sklearn.model_selection import StratifiedKFold

import os

                
def generate_full_dataset():
    # Lê os arquivos baixados do UCI
    data = pd.read_csv('data_banknote_authentication.csv', header=None, sep=';')

    # Como no UCI está separado em conjunto de teste e treino, juntamos eles e nomeamos as colunas
    data.rename(columns={0:"Variância", 1: "Skewness", 2: "Curtosis", 3: "Entropy", 4: "Class"}, inplace=True)
    return data


def kfold(data, k):
    # Função de uma biblioteca externa que vair gerar o k-fold de uma forma equilibrada
    skf = StratifiedKFold(n_splits=k, random_state=None, shuffle=True)

    # Coloca o dataset no formato necessário para a função do k-fold
    y = data["Class"]
    X = data.drop("Class", axis=1)    
    X_arr = X.to_numpy()
    y_arr = y.to_numpy()

    # Realiza o k-fold
    for i, (train_index, test_index) in enumerate(skf.split(X_arr, y_arr)):
        X_train, X_test = X_arr[train_index], X_arr[test_index]
        y_train, y_test = y_arr[train_index], y_arr[test_index]


        # Gera um novo dataframe (tabela) para os dados de teste e de treino
        columns = ["Variance", "Skewness", "Curtosis", "Entropy", "Class"]
        train_df = pd.DataFrame(data=X_train)
        train_df["Class"] = y_train
        test_df = pd.DataFrame(data=X_test)
        test_df["Class"] = y_test

        # Salva os datasets na pasta (i + 1)
        save_data(i + 1, train_df, test_df)


def save_data(number, train, test):
    # Garante que os arquivos de salvamento existem
    if not os.path.exists('kfold_data'):
    	os.system('mkdir kfold_data')

    # Salva os dados
    train.to_csv(f'kfold_data/train{number}.csv', header=False, index=False, sep=';')
    test.to_csv(f'kfold_data/test{number}.csv', header=False, index=False, sep=';')


if __name__ == '__main__':
    data = generate_full_dataset()
    kfold(data, 5)

