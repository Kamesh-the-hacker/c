#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NODES 10
#define INFINITY INT_MAX

typedef struct {
    int routing_table[MAX_NODES][MAX_NODES];
} Router;

void initialize_router_and_network(int network[MAX_NODES][MAX_NODES], int nodes);
void simulate_OSPF(Router *routers, int network[MAX_NODES][MAX_NODES], int nodes);
void update_routing_table(Router *router, int network[MAX_NODES][MAX_NODES], int nodes);
void print_routing_table(Router *routers, int nodes);

int main() {
    int network[MAX_NODES][MAX_NODES];
    int nodes;

    printf("Enter the number of routers (max %d): ", MAX_NODES);
    scanf("%d", &nodes);

    if (nodes > MAX_NODES || nodes <= 0) {
        printf("Invalid number of routers!\n");
        return 1;
    }

    Router routers[MAX_NODES];

    initialize_router_and_network(network, nodes);
    simulate_OSPF(routers, network, nodes);

    printf("\nFinal Routing Tables:\n");
    print_routing_table(routers, nodes);

    return 0;
}

void initialize_router_and_network(int network[MAX_NODES][MAX_NODES], int nodes) {
    printf("Enter the network cost matrix (use %d for no direct link):\n", INFINITY);

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &network[i][j]);
            if (i == j)
                network[i][j] = 0;
        }
    }
}

void simulate_OSPF(Router *routers, int network[MAX_NODES][MAX_NODES], int nodes) {
    for (int i = 0; i < nodes; i++)
        update_routing_table(&routers[i], network, nodes);
}

void update_routing_table(Router *router, int network[MAX_NODES][MAX_NODES], int nodes) {
    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            router->routing_table[i][j] = network[i][j];
}

void print_routing_table(Router *routers, int nodes) {
    for (int i = 0; i < nodes; i++) {
        printf("\nRouting Table for Router %d:\n", i);
        printf("Destination\tCost\n");

        for (int j = 0; j < nodes; j++) {
            if (routers[i].routing_table[i][j] == INFINITY)
                printf("%d\t\tINFINITY\n", j);
            else
                printf("%d\t\t%d\n", j, routers[i].routing_table[i][j]);
        }
    }
}
