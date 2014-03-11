#ifndef STRONGLYCONNECTEDCOMPONENTS_H
#define STRONGLYCONNECTEDCOMPONENTS_H

#include "DirectedGraphAdjList.h"

namespace ycg {

class StronglyConnectedComponents {
public:
    StronglyConnectedComponents(const DirectedGraphAdjList* graph);
    ~StronglyConnectedComponents();
    void compute();
    DirectedGraphAdjList createComponentGraph() const;
    int countNumberOfVertexInComponent(int label);
private:
    void dfsFirstStage();
    void visitFirstStage(int u);
    void dfsSecondStage();
    void visitSecondStage(int u);
    void createTransposeGraph();
private:
    enum COLOR {
        WHITE, BLACK, GRAY
    };
    const DirectedGraphAdjList *graph_original;
    DirectedGraphAdjList *graph_transpose;
    int *color;
    int *order, norder;
    int *componentLabel;
    int countComponent;
};


} //~ namespace ycg


#endif // STRONGLYCONNECTEDCOMPONENTS_H
