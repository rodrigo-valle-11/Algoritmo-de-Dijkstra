#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stdlib.h>

using namespace std;

#define MAX 10005 
#define Nodo pair<int, int>
#define INF 1 << 30 
struct cmp {
    bool operator()(const Nodo &a, const Nodo &b) {
        return a.second > b.second;
    }
};

vector<Nodo> ady[MAX]; 
int distancia[MAX];    
bool visitado[MAX];     
priority_queue<Nodo, vector<Nodo>, cmp> Q; 
int V; 
int previo[MAX]; 
void init() {
    for (int i = 0; i <= V; ++i) {
        distancia[i] = INF; 
        visitado[i] = false; 
        previo[i] = -1; 
    }
}

void minimizacion(int actual, int adyacente, int peso) {
    
    if (distancia[actual] + peso < distancia[adyacente]) {
        distancia[adyacente] = distancia[actual] + peso;
        previo[adyacente] = actual; 
        Q.push(Nodo(adyacente, distancia[adyacente])); 
    }
}

// Funcion para mostrar cual es el camino mas corto desde el nodo de  inicio al final
void print(int destino) {
    if (previo[destino] != -1) 
        print(previo[destino]);
    printf("%d ", destino); 
}

// Funcion ppara encontrar cual va a ser el camino con menor puntuacion
void corto(int inicial) {
    init(); 
    Q.push(Nodo(inicial, 0)); 
    distancia[inicial] = 0; 
    int actual, adyacente, peso; 
    while (!Q.empty()) { 
        actual = Q.top().first; 
        Q.pop(); 
        if (visitado[actual]) continue; 
        visitado[actual] = true; 

        for (int i = 0; i < ady[actual].size(); ++i) {
            adyacente = ady[actual][i].first; 
            peso = ady[actual][i].second; 
            if (!visitado[adyacente]) { 
                minimizacion(actual, adyacente, peso); 
            }
        }
    }

    printf("\tLa distancia mas corta desde el nodo %d\n", inicial);
    for (int i = 1; i <= V; ++i) {
        printf("\tNodo %d, distancia mas corta = %d\n", i, distancia[i]);
    }

    puts("\tPara encontrar el camino mas corto desde el nodo de inicio al vertice destino,");
    printf("\tIngrese el nodo de llegada: ");
    int destino;
    scanf("%d", &destino);
    print(destino);
    printf("\n");
}

int main() {
    int E, origen, destino, peso, inicial;
    cout << "\tALGORITMI DE DIJKSTRA Rodrigo Valle" << endl;
    cout << "\tIngrese la cantidad de nodos y aristas que contendra el grafo. " << endl;
    cout << "\tIngrese el numero de nodos: ";
    scanf("%d", &V);
    cout << "\tIngrese el numero de aristas: ";
    scanf("%d", &E);

    cout << "\tIngrese el nodo de inicio , su arista y la puntuacion de un nodo a otro de la siguiente manera: 1 2 5 " << endl;
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &origen, &destino, &peso);
        ady[origen].push_back(Nodo(destino, peso));
    }

    cout << "\tIngrese el nodo inicial: " << endl;
    scanf("%d", &inicial);
    corto(inicial);
    return 0;
}

