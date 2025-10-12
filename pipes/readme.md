# Produtor-Consumidor com Pipes

#### Autores: Felipe Lacerda Fernandes de Assis, Gisele Núbia Santos Oliveira

## Requisitos sugeridos

| `Requisitos sugeridos`                                                       |
| :--------------------------------------------------------------------------- |
| `Bash no Ubuntu`                                                             |
| `GCC (compilador C): sudo apt update && sudo apt install -y build-essential` |

## Guia de execução

**1. Clonar o Repositório (Opcional, apenas necessário caso o repositório não tenha sido clonado)**

```bash
git clone https://github.com/gihNubia/IPC-Interprocess-Communication-.git
```

**2. Navegar até o Diretório do Código de Pipes**

```bash
cd IPC-Interprocess-Communication-/pipes
```

**3. Compilar o código index.c**

```bash
gcc index.c -o index
```

**4. Executar o Código de Pipes**

```bash
./index <VALOR_INTEIRO_INDICA_QTD_NUM_GERADOS_E_AVALIADOS>
```

## Scripts

**measure_index.sh**: Executa o binário ./index em 10 execuções sequenciais (de 100.000 a 1.000.000, passo 100.000), mede os tempos real/usuário/sistema e exibe as médias ao final.

**Guia de execução do script measure_index.sh**

**1. Fornecer permissão de execução ao arquivo measure_index.sh**

```bash
chmod +x measure_index.sh
```

**2. Executar o script measure_index.sh**

```bash
./measure_index.sh
```
