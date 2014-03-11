#include "StronglyConnectedComponents.h"

namespace ycg {

StronglyConnectedComponents::StronglyConnectedComponents(const DirectedGraphAdjList *graph) {
    int nVertex = graph->numberOfVertex();
    int nEdge = graph->numberOfEdge();
    color = new int[nVertex];
    order = new int[nVertex];
    componentLabel = new int[nVertex];
    this->graph_original = graph;
    this->graph_transpose = new DirectedGraphAdjList(nVertex, nEdge);
}

StronglyConnectedComponents::~StronglyConnectedComponents() {
    delete []color;
    delete []order;
    delete []componentLabel;
    delete graph_transpose;
}

void StronglyConnectedComponents::compute() {
    dfsFirstStage();
    createTransposeGraph();
    dfsSecondStage();
}

void StronglyConnectedComponents::dfsFirstStage() {
    for (int u = 0; u < graph_original->numberOfVertex(); ++u) {
        color[u] = WHITE;
    }
    norder = graph_original->numberOfVertex();
    for (int u = 0; u < graph_original->numberOfVertex(); ++u) {
        if (color[u] == WHITE) {
            visitFirstStage(u);
        }
    }
}

void StronglyConnectedComponents::visitFirstStage(int u) {
    color[u] = GRAY;
    DirectedGraphAdjList::EdgeIterator iterator = graph_original->edgeIterarorFromVertex(u);
    while (iterator.hasNext()) {
        int v = iterator.next();
        if (color[v] == WHITE) {
            visitFirstStage(v);
        }
    }
    order[--norder] = u;
}

void StronglyConnectedComponents::createTransposeGraph() {
    for (int u = 0; u < graph_original->numberOfVertex(); ++u) {
        DirectedGraphAdjList::EdgeIterator iterator = graph_original->edgeIterarorFromVertex(u);
        while (iterator.hasNext()) {
            int v = iterator.next();
            graph_transpose->insertEdge(Edge(v, u));
        }
    }
}

void StronglyConnectedComponents::dfsSecondStage() {
    for (int u = 0; u < graph_transpose->numberOfVertex(); ++u) {
        color[u] = WHITE;
    }
    countComponent = 0;
    for (int i = 0; i < graph_transpose->numberOfVertex(); ++i) {
        if (color[order[i]] == WHITE) {
            visitSecondStage(order[i]);
            ++countComponent;
        }
    }
}

void StronglyConnectedComponents::visitSecondStage(int u) {
    color[u] = GRAY;
    componentLabel[u] = countComponent;
    DirectedGraphAdjList::EdgeIterator iterator = graph_transpose->edgeIterarorFromVertex(u);
    while (iterator.hasNext()) {
        int v = iterator.next();
        if (color[v] == WHITE) {
            visitSecondStage(v);
        }
    }
}

DirectedGraphAdjList StronglyConnectedComponents::createComponentGraph() const {
    DirectedGraphAdjList component_graph(countComponent, graph_original->numberOfEdge());
    for (int u = 0; u < graph_original->numberOfVertex(); ++u) {
        DirectedGraphAdjList::EdgeIterator iterator = graph_original->edgeIterarorFromVertex(u);
        while (iterator.hasNext()) {
            int v = iterator.next();
            if (componentLabel[u] != componentLabel[v]) {
                component_graph.insertEdge(Edge(componentLabel[u], componentLabel[v]));
            }
        }
    }
    return component_graph;
}

int StronglyConnectedComponents::countNumberOfVertexInComponent(int label) {
    int count = 0;
    for (int u = 0; u < graph_original->numberOfVertex(); ++u) {
        if (componentLabel[u] == label) {
            ++count;
        }
    }
    return count;
}

} //~ namespace ycg
