# ProjetoIoT - Participantes: Aparecida Lopes , Igor Chianca e José Pires

# Monitoramente do ambiente de uma cozinha de Restaurante 

# Objetivo
  Resolver o problema de manuseio e armazenagem inadequada de alimentos perecíveis em um restaurante, 
por meio da implementação de sistemas de monitoramento e controle de temperatura e umidade utilizando uma plataforma de IoT.

# Problema
  Em restaurantes, frequentemente ocorrem problemas de manuseio e armazenagem inadequada de alimentos perecíveis, resultando em condições de temperatura e umidade impróprias. Isso pode levar à rápida deterioração dos produtos, crescimento de microrganismos indesejáveis e comprometimento da segurança alimentar.

# Solução
  Para solucionar esse problema, propõe-se a implementação de sistemas de monitoramento e controle de temperatura e umidade em toda a cadeia de alimentos. 
  Essa solução será alcançada por meio da tecnologia IoT, utilizando sensores conectados a um microcontrolador Esp32, que coletará os dados e os publicará no broker Mosquitto. 
  Os dados serão então visualizados em uma interface gráfica desenvolvida no Node-Red. Solução mandará um alerta para o e-mail do usuário, caso a temperatura e umidade sejam maior ou menor que o normal, e quando houver mudanças de estados.
  Além disso, é essencial seguir todas as diretrizes e procedimentos operacionais padrão para garantir que os alimentos sejam manuseados e armazenados nas condições adequadas. 
  Isso inclui estabelecer faixas de temperatura e umidade aceitáveis, realizar inspeções regulares e fornecer treinamento aos funcionários para que possam manter esses parâmetros sob controle.

# Funcionalidades
- Monitoramento da Temperatura e Umidade do ambiente do Restaurante
- Alerta quando a temperatura/umidade estiverem fora do padrão estabelecido, via e-mail
- Alerta quando esses valores mudarem de estado
- Informes dos valores lidos e gráficos demonstrativos 

# Pré-requisitos
  - sensor dht11 (temperatura e umidade), esp32, docker-compose, node-red, mosquitto, máquina virtual na cloud

# Instalação
1. **Acessar Máquina Virtual:** 
- Por meio do IP 34.28.96.89
- A máquina virtual está sendo executada na cloud do Google.
- Foi realizado a configuração do firewal para as portas do mosquitto 1883 e node-red 1880

2. **Configuração do Ambiente:** 
- Arquivo Dockerfile com o node-red e as bibliotecas que vai ser utilizadas no projeto (e-mail e dashboard)
- Arquivo mosquitto.conf com as configurações do broken mosquitto
- arquivo docker-compose.yml com as configurações dos contêineres que vai ser usados no projeto.
- Serviço do Node-Red sendo executado na porta 80.
- Broken Mosquitto sendo executado na porta 1883.
- Criação de arquivos no volume data no node-red para armazenamentos dos dados.

3. **Compilar ou construir o projeto:** 
 - Criação do Dockerfile
 - Criação do docker-compose.yml
 - Considerando que já se tenha o docker-compose instalado, executar o arquivo docker-compose.yml onde vai ser construido e inicializado os serviçoes do  node-red de acordo com o buil do Docker file e o serviço do mosquito com a imagem disponível no hub do docker.
   > docker-compose up -d
  - Após inicializado os serviços, acessar o node-red, para visualizar os dados, via o MQTT (mosquitto), processado o dado em uma function e enviado um alerta para o usuário, caso seja maior oum menor do que o padrão. Também será salvo em arquivo esses dados, da forma que vem dos sensores.
  >  34.28.96.89:80
  - O processamento da leitura dos sensores foi realizado no esp32 e publicado no broken mosquitto
  - As informações estão sendo mostradas também em um dashboard com gráficos e medidores.
  - Para acessar o arquivo de log com os dados crus do dispositivo
  > docker exec -it nome_da_imagem bash
  - Após acesso, acessa os arquivos dataTemperatura.log e dataUmidade.log


# Vídeo Demonstrativo do Projeto
 - https://www.loom.com/share/204fef8bce824b8c8035c12f13972e6a

