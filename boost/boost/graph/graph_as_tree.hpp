//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// This file is part of the Boost Graph Library
//
// You should have received a copy of the License Agreement for the
// Boost Graph Library along with the software; see the file LICENSE.
// If not, contact Office of Research, University of Notre Dame, Notre
// Dame, IN 46556.
//
// Permission to modify the code and to distribute modified code is
// granted, provided the text of this NOTICE is retained, a notice that
// the code was modified is included with the above COPYRIGHT NOTICE and
// with the COPYRIGHT NOTICE in the LICENSE file, and that the LICENSE
// file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//=======================================================================
//
#ifndef BOOST_GRAPH_GRAPH_AS_TREE_HPP
#define BOOST_GRAPH_GRAPH_AS_TREE_HPP

#include <vector>
#include <boost/config.hpp>
#include <boost/property_accessor.hpp>
#include <boost/tree_structure.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/breadth_first_search.hpp>
#include <boost/graph_search_visitors.hpp>

namespace boost {

  template <class Graph, class Node, class ChIt, class Derived>
  class graph_as_tree_base
  {
    typedef Derived Tree;
  public:
    typedef Node node_descriptor;
    typedef ChIt children_iterator;
    
    graph_as_tree_base(Graph& g, Node root) : _g(g), _root(root) { }
    
    friend Node root(const Tree& t) { return t._root; }
    
    template <class N>
    friend std::pair<ChIt,ChIt>
    children(N n, const Tree& t) { return adjacent_vertices(n, t._g);  }
    
    template<class N>
    friend Node parent(N n, const Tree& t) { 
      return boost::get(t.parent_pa(), n); 
    }
    
    Graph& _g;
    Node _root;
  };
  
  
  template <class Graph, class ParentPA
          , class Node 
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
             = typename graph_traits<Graph>::vertex_descriptor
#endif
          , class ChIt
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
              = typename graph_traits<Graph>::adjacency_iterator
#endif
           >
  class graph_as_tree
    : public graph_as_tree_base<Graph, Node, ChIt, 
	    graph_as_tree<Graph,ParentPA,Node,ChIt> >
  {
    typedef graph_as_tree self;
    typedef graph_as_tree_base<Graph, Node, ChIt, self> super;
  public:
    graph_as_tree(Graph& g, Node root) : super(g, root) {  }
    
    graph_as_tree(Graph& g, Node root, ParentPA p) : super(g, root), _p(p) { 
    std::vector<default_color_type> color(num_vertices(g));
    breadth_first_search(g, root, visit_predecessor(p), color.begin());
    }
    ParentPA parent_pa() const { return _p; }
  protected:
    ParentPA _p;
  };
  

} /* namespace boost */
