#include <iostream>
#include <sstream>
#include "graphiso.h"

using namespace std;

// ================= Complete - Begin Graph class implementation ===================
Graph::Graph(std::istream& istr)
{
    string aline;
    while(getline(istr,aline))
    {
        istringstream iss(aline);
        string u, v;
        if(iss >> u){
            VERTEX_SET_T neighbors;
            while(iss >> v)
            {
                neighbors.insert(v);
            }
            adj_.insert(std::make_pair(u,neighbors));
        }
    }
}


bool Graph::edgeExists(const VERTEX_T& u, const VERTEX_T& v) const
{
    if((adj_.find(u) != adj_.end()) && (adj_.at(u).find(v) != adj_.at(u).end()))
    {
        return true;
    }
    return false;
}
const VERTEX_SET_T& Graph::neighbors(const VERTEX_T& v) const
{
    if(adj_.find(v) == adj_.end()){
        throw std::invalid_argument("Neighbors: invalid vertex - not in  map");
    }
    return adj_.at(v);
}
VERTEX_LIST_T Graph::vertices() const
{
    VERTEX_LIST_T verts;
    for(const auto& p : adj_)
    {
        verts.push_back(p.first);
    }
    return verts;
}
// ================= Complete - End Graph class implementation ===================

// Prototype and helper functions here

// To be completed
bool isConsistent(const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping){
    // Feel free to change or remove this starter code
    VERTEX_LIST_T g1verts = g1.vertices();
    for(const auto& g1u : g1verts)
    {
        // Check mappings for necessary vertices to see if there is any violation
        // and return false

        std::pair<VERTEX_T, VERTEX_T> * item = mapping.find(g1u);
        if(item == nullptr){  // no mapping exists
            continue;
        }

        VERTEX_T g2u = item->second;
        if(g1u.size() != g2u.size()){  // verticies are of uneven size
            return false;
        }

        const VERTEX_SET_T neighborSet = g1.neighbors(g1u);
        for(auto n: neighborSet){  // check all neighbors of vertex
            std::pair<VERTEX_T, VERTEX_T>* nMapping = mapping.find(n);  // if neighbor is in mapping
            if(nMapping == nullptr){  // no mapping exists
                continue;
            }

            VERTEX_T nVertex = nMapping->second;  // vertex that n is mapped two
            if(!g2.edgeExists(g2u, nVertex)){  // does edge exist btwn vertex mapping and neighbor mapping
                return false;
            }
        }
    }
    return true;
}

// Add any helper functions you deem useful
bool graphIsoHelper(const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping, VERTEX_LIST_T g1verts, VERTEX_LIST_T g2verts, long unsigned int g1Index){
    // check to see if you've reached the end of g1v
    if(g1Index == g1verts.size()){
        return true;
    }

    for(auto g2v = g2verts.begin(); g2v != g2verts.end(); g2v++){
        std::pair<VERTEX_T, VERTEX_T> item = std::make_pair(g1verts[g1Index], *g2v);

        mapping.insert(item);
        if(!isConsistent(g1, g2, mapping)){  // not valid so remove from mapping
            mapping.remove(item.first);
            continue;
        }
        // VERTEX_LIST_T g2vertsTemp = g2verts;
        // g2vertsTemp.erase(g2v);
        // graphIsoHelper(g1, g2, mapping, g1verts, g2vertsTemp, ++g1Index);
        g2verts.erase(g2v);
        graphIsoHelper(g1, g2, mapping, g1verts, g2verts, ++g1Index);
    }
    return true;
}

// To be completed
bool graphIso(const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping)
{
    VERTEX_LIST_T g1verts = g1.vertices();
    if(g1verts.size() != g2.vertices().size())
    {
        return false;
    }

    VERTEX_LIST_T g2verts = g2.vertices();
    graphIsoHelper(g1, g2, mapping, g1verts, g2verts, 0);
    if(mapping.size() == g1verts.size()){
        return true;
    }

    // Delete this and return the correct value...
    // This is just placeholder to allow compilation
    return false;
}

