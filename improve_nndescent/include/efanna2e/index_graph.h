//
// Copyright (c) 2017 ZJULearning. All rights reserved.
//
// This source code is licensed under the MIT license.
//

#ifndef EFANNA2E_INDEX_GRAPH_H
#define EFANNA2E_INDEX_GRAPH_H

#include <cstddef>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include "util.h"
#include "parameters.h"
#include "neighbor.h"
#include "index.h"


namespace efanna2e {

class IndexGraph : public Index {
 public:
  explicit IndexGraph(const size_t dimension, const size_t n, Metric m, Index *initializer);


  virtual ~IndexGraph();

  virtual void Save(const char *filename)override;
  virtual void Load(const char *filename)override;

  virtual void Build(size_t n, const float *data, const Parameters &parameters) override;

  virtual void Search(
      const float *query,
      const float *x,
      size_t k,
      const Parameters &parameters,
      unsigned *indices) override;

  void GraphAdd(const float* data, unsigned n, unsigned dim, const Parameters &parameters);
  void RefineGraph(const float* data, const Parameters &parameters);
    void RefineGraph11(const float* data, const Parameters &parameters,std::vector<vector<unsigned >> &rank);
    void RefineGraph12(const float* data, const Parameters &parameters);
    void RefineGraph13(const float* data, const Parameters &parameters);
    void RefineGraph14(const float* data, const Parameters &parameters);
    void RefineGraph3(const float* data, const Parameters &parameters, std::vector<float> &p_square);
    void RefineGraph4_p(const float* data, const Parameters &parameters, std::vector<float> &p_square, std::vector<float> &p_size);
    void RefineGraph4_purn(const float* data, const Parameters &parameters, std::vector<float> &p_square, std::vector<float> &p_size);
    void RefineGraph5(const float* data, const Parameters &parameters, std::vector<float> &p_square, std::vector<float> &p_right_size);
//
//    struct mapHashFunc {
//        std::size_t operator()(const pair<unsigned ,unsigned > &key) const {
//          using std::size_t;
//          using std::hash;
//
//          return ((hash<unsigned>()(key.first) ^ (hash<unsigned >()(key.second) << 1)) >> 1);
//        }
//    };
//
//    struct EqualKey
//    {
//        bool operator () (const pair<unsigned ,unsigned > &lhs, const pair<unsigned ,unsigned > &rhs) const
//        {
//          return lhs.first  == rhs.first
//                 && lhs.second == rhs.second;
//        }
//    };

 protected:
  typedef std::vector<nhood> KNNGraph;
  typedef std::vector<LockNeighbor > LockGraph;
//    typedef std::vector<std::vector<unsigned > > CompactGraph;
//    CompactGraph final_graph_;
  Index *initializer_;
  KNNGraph graph_;
    typedef vector<id_and_square> square_heap2;
    unsigned div;
 //  map<pair<unsigned ,unsigned >, float > lowbound_map;
 //  unordered_map<pair<unsigned ,unsigned >, float, mapHashFunc, EqualKey> lowbound_map;




private:
  void InitializeGraph(const Parameters &parameters);
  void InitializeGraph_Refine(const Parameters &parameters);
    void InitializeGraph_Refine3(const Parameters &parameters, std::vector<float> &p_square);

  void NNDescent(const Parameters &parameters);
    void NNDescent11(const Parameters &parameters,std::vector<vector<unsigned >> &rank);
    void NNDescent12(const Parameters &parameters);
    void NNDescent13(const Parameters &parameters);
        void NNDescent14(const Parameters &parameters);
    void NNDescent3(const Parameters &parameters, std::vector<float> &p_square);
    void NNDescent4_p(const Parameters &parameters, std::vector<float> &p_square, std::vector<float> &p_size);
    void NNDescent4_purn(const Parameters &parameters, std::vector<float> &p_square, std::vector<float> &p_size);
    void NNDescent5(const Parameters &parameters, std::vector<float> &p_square, std::vector<float> &p_right_size);

  void join();
    void join11(std::vector<vector<unsigned >> &rank);
    void join12();void join12_2();void map_insert(unsigned iid, unsigned jid, float lowerbound);
        void pool_insert(unsigned  iid,unsigned  jid, float b1, float b2);
    void join13();
        void join14();
    void join3(std::vector<float> &p_square);
    void join4_p(std::vector<float> &p_square, std::vector<float> &p_size);
    void join4_purn(std::vector<float> &p_square, std::vector<float> &p_size);
    void join5(std::vector<float> &p_square, std::vector<float> &p_right_size);

  void update(const Parameters &parameters);
    void update12(const Parameters &parameters);
    void update3(const Parameters &parameters,std::vector<float> &p_square);
  void generate_control_set(std::vector<unsigned> &c,
                                      std::vector<std::vector<unsigned> > &v,
                                      unsigned N);
  void eval_recall(std::vector<unsigned>& ctrl_points, std::vector<std::vector<unsigned> > &acc_eval_set);
  void get_neighbor_to_add(const float* point, const Parameters &parameters, LockGraph& g,
                           std::mt19937& rng, std::vector<Neighbor>& retset, unsigned n_total);
  void compact_to_Lockgraph(LockGraph &g);
  void parallel_graph_insert(unsigned id, Neighbor nn, LockGraph& g, size_t K);

};

}

#endif //EFANNA2E_INDEX_GRAPH_H
