typedef struct {
    void *node;
    struct UndirectedGraphNode *copy;
    UT_hash_handle hh;
} HashMap;
typedef struct UndirectedGraphNode graph;
graph* depthFirstClone(graph *node, HashMap **map) {
    HashMap *found, *elem;
    graph *key = node, *copy;
    HASH_FIND_PTR(*map, &key, found);
    if (found) {
        return found->copy;
    }
    elem = malloc(sizeof(HashMap));
    copy = (graph*)malloc(sizeof(graph));
    memset(copy, 0, sizeof(graph));
    copy->label = node->label;
    copy->neighborsCount = node->neighborsCount;
    elem->node = node;
    elem->copy = copy;
    HASH_ADD_PTR(*map, node, elem);
    for (int i = 0; i < NEIGHBORS_MAX_SIZE; i++) {
        if (node->neighbors[i] != NULL) {
            copy->neighbors[i] = depthFirstClone(node->neighbors[i], map);
        }
    }
    return copy;
}
graph *cloneGraph(graph *graph) {
    if (graph == NULL) return NULL;
    HashMap *map = NULL;
    return depthFirstClone(graph, &map);
}
