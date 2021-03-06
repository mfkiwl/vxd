// This is lemsvxlsrc/brcv/shp/dbhg/bgrld_hg_graph.cxx
//:
// \file
// \author Based on original code by Ming-Ching Chang
// date:   Apr 04, 2005

#include <bgrld/bgrld_hg_graph.h>


////////////////////////////////////////////////////////////////////
//: ===== Internal Low-level Graph operation (without handling connectivity) =====
void bgrld_hg_graph::_internal_add_vertex (bgrld_hg_vertex* vertex) 
{
  assert (vertex->id() > 0);
  vertices_.insert (vcl_pair<int, bgrld_hg_vertex*> (vertex->id(), vertex));
}

bool bgrld_hg_graph::_internal_del_vertex (bgrld_hg_vertex* vertex) 
{
  assert (vertex->connecting_edges().size()==0);
  int n_removed = vertices_.erase (vertex->id());
  return (n_removed == 1);
}

void bgrld_hg_graph::_internal_add_edge (bgrld_hg_edge* edge) 
{
  assert (edge->id() > 0);
  edges_.insert (vcl_pair<int, bgrld_hg_edge*> (edge->id(), edge));
}

bool bgrld_hg_graph::_internal_del_edge (bgrld_hg_edge* edge)
{
  assert (edge->connecting_s_vertex() == NULL &&
          edge->connecting_e_vertex() == NULL);
  int n_removed = edges_.erase (edge->id());
  return (n_removed == 1);
}

////////////////////////////////////////////////////////////////////
//: ===== High-level Graph operation (handling connectivity) =====

bool bgrld_hg_graph::remove_vertex (bgrld_hg_vertex* vertex)
{
  vcl_vector<bgrld_hg_edge*>::iterator it = vertex->connecting_edges().begin();
  while (it != vertex->connecting_edges().end()) {
    bgrld_hg_edge* edge = (*it);
    _internal_disconnect_edge_vertex (edge, vertex);
  }

  return _internal_del_vertex (vertex);
}

bool bgrld_hg_graph::remove_vertex (int id)
{
  bgrld_hg_vertex* vertex = vertices (id);
  if (vertex)
    return remove_vertex (vertex);
  else
    return false;
}

bool bgrld_hg_graph::remove_edge (bgrld_hg_edge* edge)
{
  bgrld_hg_vertex* sv = edge->connecting_s_vertex();
  bgrld_hg_vertex* ev = edge->connecting_e_vertex();

  _internal_disconnect_edge_vertex (edge, sv);
  _internal_disconnect_edge_vertex (edge, ev);

  return _internal_del_edge (edge);
}

bool bgrld_hg_graph::remove_edge (int id)
{
  bgrld_hg_edge* edge = edges (id);
  if (edge)
    return remove_edge (edge);
  else
    return false;
}

////////////////////////////////////////////////////////////////////
//: ===== High-level Graph operation that the user should use =====

//: Only remove the svertex if it is an isolated vertex (no scaffold_curves connecting to it!).
bool bgrld_hg_graph::topo_remove_vertex (bgrld_hg_vertex* vertex)
{
  if (vertex->connecting_edges().size() == 0)
    return remove_vertex (vertex);
  else
    return false;
}

bool bgrld_hg_graph::topo_remove_vertex (int id)
{
  bgrld_hg_vertex* vertex = (bgrld_hg_vertex*) vertices (id);
  if (vertex)
    return topo_remove_vertex (vertex);
  else
    return false;
}

bool bgrld_hg_graph::topo_remove_edge (bgrld_hg_edge* edge)
{
  //: for scaffold_graph, can remove the graph edge directly.
  return remove_edge (edge);
}

bool bgrld_hg_graph::topo_remove_edge (int id)
{
  //: for scaffold_graph, can remove the graph edge directly.
  return remove_edge (id);
}

