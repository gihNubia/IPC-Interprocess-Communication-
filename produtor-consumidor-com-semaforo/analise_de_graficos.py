import pandas as pd
import matplotlib.pyplot as plt

# Lê o CSV
df = pd.read_csv('produtor-consumidor-com-semaforo\dados_produtor_consumidor_tempo_de_execucao.csv', sep=';')

# Corrige vírgula decimal → ponto
df['Tempo'] = df['Tempo'].str.replace(',', '.', regex=False).astype(float)
import pandas as pd
import matplotlib.pyplot as plt

# Garante que as colunas estão com tipos corretos
df["N"] = df["N"]
df["NP"] = df["NP"]
df["NC"] = df["NC"]
df["Tempo"] = df["Tempo"].astype(float)

# Cria um gráfico para cada tamanho de buffer
for n in sorted(df["N"].unique()):
    dados_n = df[df["N"] == n]
    plt.figure(figsize=(8,5))
    
    # Para cada número de consumidores, plota uma linha
    for nc in sorted(dados_n["NC"].unique()):
        subset = dados_n[dados_n["NC"] == nc]
        plt.plot(subset["NP"], subset["Tempo"], marker='o', label=f"NC = {nc}")
    
    plt.title(f"Tamanho do Buffer N = {n}")
    plt.xlabel("Número de Produtores (NP)")
    plt.ylabel("Tempo de Execução (s)")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()
