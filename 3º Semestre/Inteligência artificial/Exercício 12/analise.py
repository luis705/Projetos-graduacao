import os
from typing import List, Dict

import pandas as pd
import numpy as np


Vector = List[float]

def setup_data(data: List[int]) -> Dict[int, Vector]:
	"""
	Recebe uma lista com os arquivos na pasta data e os organiza para que as
	medidas estatísticas desejadas possam ser calculadas para cada topologia
	de rede neural utilizada.

	Args:
		data: lista com os nomes dos arquivos gerados pelo MBP

	Returns:
		topologies: dicionário com a taxa de acerto de cada uma das redes de cada
					topologia
	"""
	topologies = {0: list(), 1: list(), 2:list(), 3:list()}

	for i in range(len(data)):
		series = pd.read_csv(os.path.join('data', data[i]), sep='\t')
		series['Rounded'] = pd.Series(np.around(series["Network Output"], decimals=0))
		series['Right'] = pd.Series(
		[0 if series["Desired Output"][i] != series["Rounded"][i] else 1
		for i in range(series.shape[0])])

		counting = series['Right'].value_counts()
		topologies[i % 4].append(counting[1] / series['Right'].count() * 100)

	return topologies

def get_statistics(topologies: Dict[int, Vector]):
	"""
	Encontra as estatísticas de cada topologia e do conjunto de topologias

	Args:
		topologies: dicionario com as taxas de acerto de cada treino de cada topologia

	Returns:
		statistics_per_topology: dicionario contendo a média e o desvio padrão
								 dos acertos de cada topologia

		global_values: lista com a media e o desvio padrão global
	"""
	statistics_per_topology = dict()

	global_array = list()

	for i in range(len(topologies)):
		topology_array = np.array(topologies[i])
		statistics_per_topology[i] = {'max': np.max(topology_array),
									  'min': np.min(topology_array),
									  'median': np.median(topology_array),
									  'mean': np.mean(topology_array),
									  'standard deviation': np.std(topology_array),
									  'variance': np.var(topology_array)}

		global_array.append(topologies[i])

	global_array = np.array(global_array).flatten()
	global_values = [np.max(global_array), np.min(global_array), np.mean(global_array),
					 np.median(global_array), np.std(global_array), np.var(global_array)]

	return statistics_per_topology, global_values

def print_results(single_statistics: Dict[int, Dict[str, float]],
				  global_statistics: List[float], number_of_topologies: int) -> None:
	"""
	Imprime na tela as estatísticas calculadas de cada uma das topologias

	Args:
		single_statistics: estatisticas calculadas de cada topologia treinada
		global_statistics: estatisticas globais
		number_of_topologies: número de topologias treinadas
	"""
	for i in range(number_of_topologies):
		print(f'Topologia número {i+1}:')
		print(f"\t Máximo: {single_statistics[i]['max']}")
		print(f"\t Mínimo: {single_statistics[i]['min']}")
		print(f"\t Média: {single_statistics[i]['mean']}")
		print(f"\t Mediana: {single_statistics[i]['median']}")
		print(f"\t Desvio Padrão: {single_statistics[i]['standard deviation']}")
		print(f"\t Variância: {single_statistics[i]['variance']}\n")

	print('Estatistícas globais:')
	for nome, valor in zip(['Máximo', 'Mínimo', 'Média', 'Mediana', 'Desvio Padrão', 'Variância'], global_statistics):
		print(f'\t {nome}: {valor}')


if __name__ == '__main__':
	"""
	Programa que calcula a taxa de acerto de cada vez que a rede foi treinada
	para cada uma das topologias. Cada uma das topologias foi treinada e testada
	5 vezes com 10.000 épocas, obtendo assim resultados distintos cada uma delas
	. As topologias que foram utilizadas estão listadas abaixo:
		1: 4-2-1
		2: 4-2-2-1
		3: 4-4-1
		4: 4-4-4-1

	Com a análise desses valores, podemos perceber que, nesses poucos testes
	a topologia 2 foi a que obteve melhor performance já que sua taxa de acerto
	máxima e media foram as melhores.

	A parte de estatísticas globais informa a performance de todos os treinos
	independente da topologia.
	"""

	topologies = setup_data(os.listdir('data'))
	stats_per_topology, global_stats = get_statistics(topologies)
	print_results(stats_per_topology, global_stats, 4)
