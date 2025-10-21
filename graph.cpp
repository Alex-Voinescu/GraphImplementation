#include "graph.h"
#include <fstream>


Graph::Graph() {}

Graph::~Graph(){
    for (auto n : m_nodes) delete n;
    for (auto e : m_edges) delete e;
}

void Graph::addNode(QPoint p){
    int index=m_nodes.size()+1;
    Node *n=new Node(index,p);
    m_nodes.push_back(n);
}

void Graph::addEdge(Node *first, Node *second){
    if(first==nullptr || second==nullptr)
        return;
    Edge* e=new Edge(first,second);
    for(auto edge:m_edges){
        if(edge->getFirst()->getIndex()==e->getFirst()->getIndex()
            && edge->getSecond()->getIndex()==e->getSecond()->getIndex()){
            return;
        }
    }
    m_edges.push_back(e);
}

std::vector<Node*> Graph::getNodes(){
    return m_nodes;
}

std::vector<Edge*> Graph::getEdges(){
    return m_edges;
}

bool Graph::isOriented(){
    return m_oriented;
}

void Graph::changeState(){
    m_oriented=!m_oriented;
}

void Graph::saveMatrix(){

    std::ofstream out("matrix.txt");
    if(!out.is_open()){
        return;
    }
    out<<m_nodes.size()<<"\n";
    std::vector<std::vector<int>> mat(m_nodes.size(),
                                      std::vector<int>(m_nodes.size(), 0));

    for(auto& ed:m_edges){
        int i=ed->getFirst()->getIndex()-1;
        int j=ed->getSecond()->getIndex()-1;
        mat[i][j]=1;

        if(m_oriented==false){
            mat[j][i]=1;
        }
    }

    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat.size(); ++j) {
            out << mat[i][j] << " ";
        }
        out << "\n";
    }
    out.close();

}
