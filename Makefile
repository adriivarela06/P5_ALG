# Targets principales:
#   make              -> compila aventura, generador, tiempos y reparto
#   make aventura     -> compila solo el solver
#   make generador    -> compila solo el generador de mapas
#   make tiempos      -> compila solo el medidor de tiempos
#   make reparto      -> compila el solver de reparto de raciones
#
# Targets de ejecucion:
#   make run          -> ejecuta aventura con ejemplo 1
#   make svg          -> genera mapa1.svg con el ejemplo 1
#   make ruta         -> genera mapa1.svg destacando la ruta 1 -> 3
#   make aleatorio    -> genera un mapa aleatorio de 6 nodos y lo resuelve
#   make ejemplos     -> ejecuta los 3 ejemplos generando SVG con ruta destacada
#
#   make clean        -> elimina archivos generados y objetos

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

SRC_DIR  = src
BIN_DIR  = bin
DATA_IN  = data/Entradas
DATA_TXT = data/Salidas_Texto
DATA_SVG = data/Salidas_Dibujo

AVENTURA      = $(BIN_DIR)/aventura
SRCS_AVENTURA = $(SRC_DIR)/main.cpp $(SRC_DIR)/camino_heroe.cpp $(SRC_DIR)/visualizacion.cpp

GENERADOR     = $(BIN_DIR)/generador
SRCS_GEN      = $(SRC_DIR)/generador.cpp

TIEMPOS       = $(BIN_DIR)/tiempos
SRCS_TIEMPOS  = $(SRC_DIR)/main_tiempos.cpp $(SRC_DIR)/camino_heroe.cpp

all: $(AVENTURA) $(GENERADOR) $(TIEMPOS) $(REPARTO)

$(AVENTURA): $(SRCS_AVENTURA)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS_AVENTURA) -o $@

$(GENERADOR): $(SRCS_GEN)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS_GEN) -o $@

$(TIEMPOS): $(SRCS_TIEMPOS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS_TIEMPOS) -o $@

run: $(AVENTURA)
	./$(AVENTURA) $(DATA_IN)/ejemplo1.txt

svg: $(AVENTURA)
	@mkdir -p $(DATA_TXT) $(DATA_SVG)
	./$(AVENTURA) $(DATA_IN)/ejemplo1.txt $(DATA_TXT)/salida1.txt $(DATA_SVG)/mapa1.svg
	@echo "Mapa generado: $(DATA_SVG)/mapa1.svg (abrir con un navegador)"

ruta: $(AVENTURA)
	@mkdir -p $(DATA_TXT) $(DATA_SVG)
	./$(AVENTURA) $(DATA_IN)/ejemplo1.txt $(DATA_TXT)/salida1.txt $(DATA_SVG)/mapa1.svg 1 3
	@echo "Mapa con ruta destacada generado: $(DATA_SVG)/mapa1.svg"

ejemplos: $(AVENTURA)
	@mkdir -p $(DATA_TXT) $(DATA_SVG)
	./$(AVENTURA) $(DATA_IN)/ejemplo1.txt $(DATA_TXT)/ejemplo1_salida.txt $(DATA_SVG)/ejemplo1_mapa.svg 1 3
	./$(AVENTURA) $(DATA_IN)/ejemplo2.txt $(DATA_TXT)/ejemplo2_salida.txt $(DATA_SVG)/ejemplo2_mapa.svg 1 5
	./$(AVENTURA) $(DATA_IN)/ejemplo3.txt $(DATA_TXT)/ejemplo3_salida.txt $(DATA_SVG)/ejemplo3_mapa.svg 1 7
	@echo "SVGs generados en la carpeta $(DATA_SVG)"

aleatorio: $(AVENTURA) $(GENERADOR)
	@mkdir -p $(DATA_IN) $(DATA_TXT) $(DATA_SVG)
	./$(GENERADOR) 6 $(DATA_IN)/aleatorio.txt 0.4
	./$(AVENTURA) $(DATA_IN)/aleatorio.txt $(DATA_TXT)/salida_aleatorio.txt $(DATA_SVG)/mapa_aleatorio.svg
	@echo "Mapa aleatorio generado: $(DATA_SVG)/mapa_aleatorio.svg"

clean:
	rm -f $(AVENTURA) $(GENERADOR) $(TIEMPOS) $(REPARTO)
	rm -f $(DATA_TXT)/*.txt $(DATA_IN)/aleatorio.txt $(DATA_SVG)/*.svg

.PHONY: all run svg ruta ejemplos aleatorio clean