//
// Copyright (c) 2017 ZJULearning. All rights reserved.
//
// This source code is licensed under the MIT license.
//

#include <efanna2e/index_graph.h>
#include <efanna2e/exceptions.h>
#include <efanna2e/parameters.h>
#include <omp.h>
#include <set>
#include <cfloat>
#include <efanna2e/neighbor.h>
#include<gperftools/profiler.h>

# define max(a,b) a>b?a:b
# define min(a,b) a<b?a:b
# define abs(a,b) a>b?a-b:b-a

namespace efanna2e {
#define _CONTROL_NUM 100
IndexGraph::IndexGraph(const size_t dimension, const size_t n, Metric m, Index *initializer)
    : Index(dimension, n, m),
      initializer_{initializer} {
  assert(dimension == initializer->GetDimension());
}
IndexGraph::~IndexGraph() {}

    void IndexGraph::join5(std::vector<float> &p_square, std::vector<float> &p_right_size) {
#pragma omp parallel for default(shared) schedule(dynamic, 100)
      for (unsigned n = 0; n < nd_; n++) {
        graph_[n].join([&](unsigned i, unsigned j) {
            if(i != j){
              float twice_pq_left = 2*distance_->compare2(data_ + i * dimension_, data_ + j * dimension_,div);
              float twice_pq_ub = twice_pq_left + 2*p_right_size[i]*p_right_size[j];
              float ub1 = -p_square[j]+twice_pq_ub;
              float ub2 = -p_square[i]+twice_pq_ub;

              float twice_ip = 0;
              ip_times+=2;
              if (ub1 > graph_[i].pool.front().distance) {
                twice_ip = twice_pq_left + 2*distance_->compare2(data_ + i * dimension_+div, data_ + j * dimension_+div,dimension_-div);
                float dist1 = twice_ip-p_square[j];
                  if (dist1 > graph_[i].pool.front().distance) {
                      graph_[i].insert3(j, dist1);
                  }
              } else purn_times++;
              if (ub2> graph_[j].pool.front().distance){
                if(twice_ip==0) twice_ip = twice_pq_left + 2*distance_->compare2(data_ + i * dimension_+div, data_ + j * dimension_+div,dimension_-div);
                float dist2 = twice_ip-p_square[i];
                  if (dist2> graph_[j].pool.front().distance){
                      graph_[j].insert3(i, dist2);
                  }
              }else purn_times++;


            }
        });
      }
    }

    void IndexGraph::join4_purn(std::vector<float> &p_square, std::vector<float> &p_size) {
//#pragma omp parallel for default(shared) schedule(dynamic, 100)
//      for (unsigned n = 0; n < nd_; n++) {
//        auto &nnhd = graph_[n];
//        auto &nn_new = nnhd.nn_new;
//        auto &nn_old = nnhd.nn_old;
//
//        square_heap2 myheap;
//        //在mynode里，按p_size排序，形成set
//        for (size_t j = 0; j < nn_new.size(); j++) {
//          unsigned id = nn_new[j];
//          id_and_square sq1(id, p_size[id]);
//          myheap.push_back(sq1);
//        }
//        for (size_t j = 0; j < nn_old.size(); j++) {
//          size_t id = nn_old[j];
//          id_and_square sq1(id, p_size[id]);
//          myheap.push_back(sq1);
//        }
//        std::sort(myheap.begin(),myheap.end(),greater<id_and_square>());
//
//
//
//        //原来的
//        for (unsigned const i: nn_new) {
//          for (unsigned const j: nn_new) {
//            if (i < j) {
//              callback(i, j);
//            }
//          }
//          for (unsigned j: nn_old) {
//            callback(i, j);
//          }
//        }
//
//        graph_[n].join([&](unsigned i, unsigned j) {
//            if(i != j){
//              float twice_pq_size = 2*p_size[i]*p_size[j];
//              float ub1 = -p_square[j]+twice_pq_size;
//              float ub2 = -p_square[i]+twice_pq_size;
//              float twice_ip = 0;
////              if(ub1 <= graph_[i].pool.front().distance)printf("~");
////              if(ub2 <= graph_[j].pool.front().distance)printf("~");
//              ip_times+=2;
//              if (ub1 > graph_[i].pool.front().distance) {
//                twice_ip = 2*distance_->compare(data_ + i * dimension_, data_ + j * dimension_,dimension_);
//                float dist1 = twice_ip-p_square[j];
//                graph_[i].insert3(j, dist1);
//              } else purn_times++;
//              if (ub2> graph_[j].pool.front().distance){
//                if(twice_ip==0) twice_ip = 2*distance_->compare(data_ + i * dimension_, data_ + j * dimension_,dimension_);
//                float dist2 = twice_ip-p_square[i];
//                graph_[j].insert3(i, dist2);
//              }else purn_times++;
//
//
//            }
//        });
//      }
    }

    void IndexGraph::join4_p(std::vector<float> &p_square, std::vector<float> &p_size) {
#pragma omp parallel for default(shared) schedule(dynamic, 100)
      for (unsigned n = 0; n < nd_; n++) {
        graph_[n].join([&](unsigned i, unsigned j) {
            if(i != j){
              float twice_pq_size = 2*p_size[i]*p_size[j];
              float ub1 = -p_square[j]+twice_pq_size;
              float ub2 = -p_square[i]+twice_pq_size;
              float twice_ip = 0;
//              if(ub1 <= graph_[i].pool.front().distance)printf("~");
//              if(ub2 <= graph_[j].pool.front().distance)printf("~");
              ip_times+=2;
              if (ub1 > graph_[i].pool.front().distance) {
                twice_ip = 2*distance_->compare(data_ + i * dimension_, data_ + j * dimension_,dimension_);
                float dist1 = twice_ip-p_square[j];
                  if (dist1 > graph_[i].pool.front().distance) {
                      graph_[i].insert3(j, dist1);
                  }
              } else purn_times++;
              if (ub2> graph_[j].pool.front().distance){
                if(twice_ip==0) twice_ip = 2*distance_->compare(data_ + i * dimension_, data_ + j * dimension_,dimension_);
                float dist2 = twice_ip-p_square[i];
                  if (dist2> graph_[j].pool.front().distance){
                      graph_[j].insert3(i, dist2);
                  }
              }else purn_times++;


            }
        });
      }
    }

    void IndexGraph::join3(std::vector<float> &p_square) {
#pragma omp parallel for default(shared) schedule(dynamic, 100)
  for (unsigned n = 0; n < nd_; n++) {
    graph_[n].join([&](unsigned i, unsigned j) {
      if(i != j){
        float twice_ip = 2*distance_->compare(data_ + i * dimension_, data_ + j * dimension_,dimension_);
        float dist1 = twice_ip-p_square[j];
        float dist2 = twice_ip-p_square[i];
        if (dist1 > graph_[i].pool.front().distance) {
          graph_[i].insert3(j, dist1);
        }
        if (dist2> graph_[j].pool.front().distance){
          graph_[j].insert3(i, dist2);
        }
      }
    });
  }
}

    void IndexGraph::join() {
#pragma omp parallel for default(shared) schedule(dynamic, 100)
      for (unsigned n = 0; n < nd_; n++) {
        graph_[n].join([&](unsigned i, unsigned j) {
            if(i != j){
              float dist = distance_->compare(data_ + i * dimension_, data_ + j * dimension_, dimension_);
                auto it = Euclid_dim.insert({dimension_,1});
                if(!it.second) it.first->second+=1;
                calcul_times[i]+=1;
                calcul_times[j]+=1;
              if (dist < graph_[i].pool.front().distance) {
                graph_[i].insert(j, dist);
              }
              if (dist< graph_[j].pool.front().distance){
                graph_[j].insert(i, dist);
              }
            }
        });
      }
    }

    void IndexGraph::join11(std::vector<vector<unsigned >> &rank) {
#pragma omp parallel for default(shared) schedule(dynamic, 100)
        for (unsigned n = 0; n < nd_; n++) {
            vector<unsigned> q_rank = rank[n];
            graph_[n].join([&](unsigned i, unsigned j) {

                if(i != j){
                    unsigned hasDim = 0;
                    float dist = 0;
                    float boundary1 = graph_[i].pool.front().distance;
                    float boundary2 = graph_[j].pool.front().distance;

//                    dist = distance_->compare3_rank(data_ + i * dimension_, data_ + j * dimension_,
//                                               dimension_,max(boundary1,boundary2),hasDim,dimension_/8,q_rank);
                    dist = distance_->compare3(data_ + i * dimension_, data_ + j * dimension_,
                                                    dimension_,max(boundary1,boundary2), hasDim,dimension_/16);
                    calcul_times[i]+=1;
                    calcul_times[j]+=1;
                    if (hasDim > dimension_) {
                        auto it = Euclid_dim.insert({dimension_,1});
                        if(!it.second) it.first->second+=1;
                        if (dist < boundary1) {
                            graph_[i].insert(j, dist);
                        }
                        if (dist < boundary2) {
                            graph_[j].insert(i, dist);
                        }
                    }
                    else {
                        printf("%u ",hasDim);
                        auto it = Euclid_dim.insert({hasDim,1});
                        if(!it.second) it.first->second+=1;
                    }


                }
            });
        }
    }



    void IndexGraph::join13() {
#pragma omp parallel for default(shared) schedule(dynamic, 100)
        for (unsigned n = 0; n < nd_; n++) {
            graph_[n].join12([&](id_distance i, id_distance j) {
                unsigned iid=i.id;
                unsigned jid=j.id;
                if(iid != jid){
                    float lowerbound = abs(i.distance,j.distance);
                    if (lowerbound>=graph_[iid].pool.front().distance&&lowerbound>=graph_[jid].pool.front().distance) purn_times++;
                    else{
                        float dist = distance_->compare(data_ + iid * dimension_, data_ + jid * dimension_, dimension_);
                        compare_times++;
                        if (dist < graph_[iid].pool.front().distance) {
                            graph_[iid].insert(jid, dist);
                        }
                        if (dist< graph_[jid].pool.front().distance){
                            graph_[jid].insert(iid, dist);
                        }
                    }
                }
            });
        }
    }

    void IndexGraph::join12() {
#pragma omp parallel for default(shared) schedule(dynamic, 100)
        for (unsigned n = 0; n < nd_; n++) {
            graph_[n].join12([&](id_distance i, id_distance j) {
                unsigned iid=i.id;
                unsigned jid=j.id;
                if(iid != jid){
                    float lowerbound = abs(i.distance,j.distance);
                    map_insert(iid,jid,lowerbound);

//                    auto it = graph_[iid].lowbound_map.insert({jid,lowerbound});
//                    if (!it.second && it.first->second<lowerbound) it.first->second=lowerbound;

                }
            });
        }
    }

    void IndexGraph::map_insert(unsigned iid, unsigned jid, float lowerbound) {
        auto &it = graph_[iid].lowbound_map[jid];
        it = max(it,lowerbound);
    }

    void IndexGraph::join12_2() {
#pragma omp parallel for default(shared) schedule(dynamic, 100)
        for (unsigned iid = 0; iid < nd_; iid++){
            auto &map_lb = graph_[iid].lowbound_map;
            float b1 = graph_[iid].pool.front().distance;
            //printf("%d ",nn_lb.size());fflush(stdout);
            for (auto it=map_lb.begin(); it!=map_lb.end();it++){
                unsigned jid=it->first;
                float lb=it->second;
                float b2 = graph_[jid].pool.front().distance;
                if (lb>=b1 && lb>=b2) ;
                else {
                    pool_insert(iid,jid,b1,b2);

            }

            }
            unordered_map<unsigned,float >().swap(map_lb);
        }
    }


    void IndexGraph::join14() {
#pragma omp parallel for default(shared) schedule(dynamic, 100)
        for (unsigned n = 0; n < nd_; n++) {
            graph_[n].join([&](unsigned i, unsigned j) {
                if(i != j){
                    float dist = distance_->compare(data_ + i * dimension_, data_ + j * dimension_, dimension_);
                    auto it = Euclid_dim.insert({dimension_,1});
                    if(!it.second) it.first->second+=1;
                    calcul_times[i]+=1;
                    calcul_times[j]+=1;
                    if (dist < graph_[i].pool.front().distance) {
                        graph_[i].insert(j, dist);
                    }
                    if (dist< graph_[j].pool.front().distance){
                        graph_[j].insert(i, dist);
                    }
                }
            });
        }
    }

    void IndexGraph::pool_insert(unsigned  iid,unsigned  jid,float b1, float b2){
        float dist = distance_->compare(data_ + iid * dimension_, data_ + jid * dimension_, dimension_);
        compare_times++;
        if(dist<b1) graph_[iid].insert(jid,dist);
        if(dist<b2) graph_[jid].insert(iid,dist);
    }



//        unsigned  count=0;
//        //#pragma omp parallel for default(shared) schedule(dynamic, 100)
//        for(auto it=lowbound_map.begin(); it!=lowbound_map.end();it++){
//            unsigned iid=it->first.first;
//            unsigned jid=it->first.second;
//            if (iid>=jid) printf("! ");
//            float lb=it->second;
//            float b1 = graph_[iid].pool.front().distance;
//            float b2 = graph_[jid].pool.front().distance;
//            if (lb>=b1 && lb>=b2) ;
//            else {
//                float dist = distance_->compare(data_ + iid * dimension_, data_ + jid * dimension_, dimension_);
//                compare_times++;
//                if(dist<b1) graph_[iid].insert(jid,dist);
//                if(dist<b2) graph_[jid].insert(iid,dist);
//            }
//            count++;
//        }
//        printf("lowbound map size:%u\n",count);
//        unordered_map<pair<unsigned ,unsigned >, float,mapHashFunc,EqualKey>().swap(lowbound_map);
//
//    }

    void IndexGraph::update3(const Parameters &parameters,std::vector<float> &p_square) {
  unsigned S = parameters.Get<unsigned>("S");
  unsigned R = parameters.Get<unsigned>("R");
  unsigned L = parameters.Get<unsigned>("L");
#pragma omp parallel for
  for (unsigned i = 0; i < nd_; i++) {
    std::vector<unsigned>().swap(graph_[i].nn_new);
    std::vector<unsigned>().swap(graph_[i].nn_old);
    //std::vector<unsigned>().swap(graph_[i].rnn_new);
    //std::vector<unsigned>().swap(graph_[i].rnn_old);
    //graph_[i].nn_new.clear();
    //graph_[i].nn_old.clear();
    //graph_[i].rnn_new.clear();
    //graph_[i].rnn_old.clear();
  }
#pragma omp parallel for
  for (unsigned n = 0; n < nd_; ++n) {
    auto &nn = graph_[n];
    std::sort(nn.pool.begin(), nn.pool.end(),greater<Neighbor>());
    if(nn.pool.size()>L)nn.pool.resize(L);
    nn.pool.reserve(L);
    unsigned maxl = min(nn.M + S, (unsigned) nn.pool.size());
    unsigned c = 0;
    unsigned l = 0;
    //std::sort(nn.pool.begin(), nn.pool.end());
    //if(n==0)std::cout << nn.pool[0].distance<<","<< nn.pool[1].distance<<","<< nn.pool[2].distance<< std::endl;
    while ((l < maxl) && (c < S)) {
      if (nn.pool[l].flag) ++c;
      ++l;
    }
    nn.M = l;
  }
#pragma omp parallel for
  for (unsigned n = 0; n < nd_; ++n) {//每个点
    auto &nnhd = graph_[n];
    auto &nn_new = nnhd.nn_new;
    auto &nn_old = nnhd.nn_old;
    for (unsigned l = 0; l < nnhd.M; ++l) {
      auto &nn = nnhd.pool[l];
      auto &nhood_o = graph_[nn.id];  // nn on the other side of the edge
      float comparable_dist = nn.distance+p_square[nn.id]-p_square[n];//换pq对象
      if (nn.flag) {
        nn_new.push_back(nn.id);
        if (comparable_dist < nhood_o.pool.back().distance) {
          LockGuard guard(nhood_o.lock);
          if(nhood_o.rnn_new.size() < R)nhood_o.rnn_new.push_back(n);
          else{
            unsigned int pos = rand() % R;
            nhood_o.rnn_new[pos] = n;
          }
        }
        nn.flag = false;
      } else {
        nn_old.push_back(nn.id);
        if (comparable_dist < nhood_o.pool.back().distance) {
          LockGuard guard(nhood_o.lock);
          if(nhood_o.rnn_old.size() < R)nhood_o.rnn_old.push_back(n);
          else{
            unsigned int pos = rand() % R;
            nhood_o.rnn_old[pos] = n;
          }
        }
      }
    }
    std::make_heap(nnhd.pool.begin(), nnhd.pool.end(),greater<Neighbor>());
  }
#pragma omp parallel for
  for (unsigned i = 0; i < nd_; ++i) {
    auto &nn_new = graph_[i].nn_new;
    auto &nn_old = graph_[i].nn_old;
    auto &rnn_new = graph_[i].rnn_new;
    auto &rnn_old = graph_[i].rnn_old;
    if (R && rnn_new.size() > R) {
      std::random_shuffle(rnn_new.begin(), rnn_new.end());
      rnn_new.resize(R);
    }
    nn_new.insert(nn_new.end(), rnn_new.begin(), rnn_new.end());
    if (R && rnn_old.size() > R) {
      std::random_shuffle(rnn_old.begin(), rnn_old.end());
      rnn_old.resize(R);
    }
    nn_old.insert(nn_old.end(), rnn_old.begin(), rnn_old.end());
    if(nn_old.size() > R * 2){nn_old.resize(R * 2);nn_old.reserve(R*2);}
    std::vector<unsigned>().swap(graph_[i].rnn_new);
    std::vector<unsigned>().swap(graph_[i].rnn_old);
  }
}


    void IndexGraph::update(const Parameters &parameters) {
      unsigned S = parameters.Get<unsigned>("S");
      unsigned R = parameters.Get<unsigned>("R");
      unsigned L = parameters.Get<unsigned>("L");
#pragma omp parallel for
      for (unsigned i = 0; i < nd_; i++) {
          graph_[i].count_rold=0;
          graph_[i].count_rnew=0;
        std::vector<unsigned>().swap(graph_[i].nn_new);
        std::vector<unsigned>().swap(graph_[i].nn_old);
        //std::vector<unsigned>().swap(graph_[i].rnn_new);
        //std::vector<unsigned>().swap(graph_[i].rnn_old);
        //graph_[i].nn_new.clear();
        //graph_[i].nn_old.clear();
        //graph_[i].rnn_new.clear();
        //graph_[i].rnn_old.clear();
      }
#pragma omp parallel for
      for (unsigned n = 0; n < nd_; ++n) {
        auto &nn = graph_[n];
        std::sort(nn.pool.begin(), nn.pool.end());
        if(nn.pool.size()>L)nn.pool.resize(L);
        nn.pool.reserve(L);
        unsigned maxl =min(nn.M + S, (unsigned) nn.pool.size());
        unsigned c = 0;
        unsigned l = 0;
        //std::sort(nn.pool.begin(), nn.pool.end());
        //if(n==0)std::cout << nn.pool[0].distance<<","<< nn.pool[1].distance<<","<< nn.pool[2].distance<< std::endl;
        while ((l < maxl) && (c < S)) {
          if (nn.pool[l].flag) ++c;
          ++l;
        }
        nn.M = l;
      }
#pragma omp parallel for
      for (unsigned n = 0; n < nd_; ++n) {
        auto &nnhd = graph_[n];
        auto &nn_new = nnhd.nn_new;
        auto &nn_old = nnhd.nn_old;
        for (unsigned l = 0; l < nnhd.M; ++l) {
          auto &nn = nnhd.pool[l];
          auto &nhood_o = graph_[nn.id];  // nn on the other side of the edge

          if (nn.flag) {
            nn_new.push_back(nn.id);
            if (nn.distance > nhood_o.pool.back().distance) {

              LockGuard guard(nhood_o.lock);
                nhood_o.count_rnew++;
              if(nhood_o.rnn_new.size() < R)nhood_o.rnn_new.push_back(n);
              else{
//                  if(rand()*nhood_o.count_rnew<R*RAND_MAX){
                      unsigned int pos = rand() % R;
                      nhood_o.rnn_new[pos] = n;
//                  }

              }
            }
            nn.flag = false;
          } else {
            nn_old.push_back(nn.id);
            if (nn.distance > nhood_o.pool.back().distance) {
              LockGuard guard(nhood_o.lock);
                nhood_o.count_rold++;
              if(nhood_o.rnn_old.size() < R)nhood_o.rnn_old.push_back(n);
              else{
//                  if(rand()*nhood_o.count_rold<R*RAND_MAX){
                      unsigned int pos = rand() % R;
                      nhood_o.rnn_old[pos] = n;
//                  }
              }
            }
          }
        }
        std::make_heap(nnhd.pool.begin(), nnhd.pool.end());
      }
#pragma omp parallel for
      for (unsigned i = 0; i < nd_; ++i) {
        auto &nn_new = graph_[i].nn_new;
        auto &nn_old = graph_[i].nn_old;
        auto &rnn_new = graph_[i].rnn_new;
        auto &rnn_old = graph_[i].rnn_old;
        if (R && rnn_new.size() > R) {
          std::random_shuffle(rnn_new.begin(), rnn_new.end());
          rnn_new.resize(R);
        }
        nn_new.insert(nn_new.end(), rnn_new.begin(), rnn_new.end());
        if (R && rnn_old.size() > R) {
          std::random_shuffle(rnn_old.begin(), rnn_old.end());
          rnn_old.resize(R);
        }
        nn_old.insert(nn_old.end(), rnn_old.begin(), rnn_old.end());
        if(nn_old.size() > R * 2){nn_old.resize(R * 2);nn_old.reserve(R*2);}
        std::vector<unsigned>().swap(graph_[i].rnn_new);
        std::vector<unsigned>().swap(graph_[i].rnn_old);
      }
    }

    void IndexGraph::update12(const Parameters &parameters) {
        unsigned S = parameters.Get<unsigned>("S");
        unsigned R = parameters.Get<unsigned>("R");
        unsigned L = parameters.Get<unsigned>("L");
#pragma omp parallel for
        for (unsigned i = 0; i < nd_; i++) {
            graph_[i].count_rold=0;
            graph_[i].count_rnew=0;
            std::vector<id_distance>().swap(graph_[i].nn_new2);
            std::vector<id_distance>().swap(graph_[i].nn_old2);

        }
#pragma omp parallel for
        for (unsigned n = 0; n < nd_; ++n) {
            auto &nn = graph_[n];
            std::sort(nn.pool.begin(), nn.pool.end());
            if(nn.pool.size()>L)nn.pool.resize(L);
            nn.pool.reserve(L);
            unsigned maxl = min(nn.M + S, (unsigned) nn.pool.size());
            unsigned c = 0;
            unsigned l = 0;
           while ((l < maxl) && (c < S)) {
                if (nn.pool[l].flag) ++c;
                ++l;
            }
            nn.M = l;
        }
#pragma omp parallel for
        for (unsigned n = 0; n < nd_; ++n) {
            auto &nnhd = graph_[n];
            auto &nn_new2 = nnhd.nn_new2;
            auto &nn_old2 = nnhd.nn_old2;
            for (unsigned l = 0; l < nnhd.M; ++l) {
                auto &nn = nnhd.pool[l];
                auto &nhood_o = graph_[nn.id];  // nn on the other side of the edge

                if (nn.flag) {
                    nn_new2.push_back(id_distance(nn.id, nn.distance));
                    if (nn.distance > nhood_o.pool.back().distance) {
                        LockGuard guard(nhood_o.lock);
                        nhood_o.count_rnew++;
                        if(nhood_o.rnn_new2.size() < R)nhood_o.rnn_new2.push_back(id_distance(n, nn.distance));
                        else{
                              if(rand()*nhood_o.count_rnew<R*RAND_MAX){
                                        unsigned int pos = rand() % R;
                                        nhood_o.rnn_new2[pos] = id_distance(n, nn.distance);
                          }

                        }
                    }
                    nn.flag = false;
                } else {
                    nn_old2.push_back(id_distance(nn.id, nn.distance));
                    if (nn.distance > nhood_o.pool.back().distance) {
                        LockGuard guard(nhood_o.lock);
                        nhood_o.count_rold++;
                        if(nhood_o.rnn_old2.size() < R)nhood_o.rnn_old2.push_back(id_distance(n, nn.distance));
                        else{
                          if(rand()*nhood_o.count_rold<R*RAND_MAX){
                                    unsigned int pos = rand() % R;
                                    nhood_o.rnn_old2[pos] = id_distance(n, nn.distance);
                          }
                        }
                    }
                }
            }
            std::make_heap(nnhd.pool.begin(), nnhd.pool.end());
        }

#pragma omp parallel for
        for (unsigned i = 0; i < nd_; ++i) {
            auto &nn_new2 = graph_[i].nn_new2;
            auto &nn_old2 = graph_[i].nn_old2;
            auto &rnn_new2 = graph_[i].rnn_new2;
            auto &rnn_old2 = graph_[i].rnn_old2;
            if (R && rnn_new2.size() > R) {
                std::random_shuffle(rnn_new2.begin(), rnn_new2.end());
                rnn_new2.resize(R);
            }
            nn_new2.insert(nn_new2.end(), rnn_new2.begin(), rnn_new2.end());
            if (R && rnn_old2.size() > R) {
                std::random_shuffle(rnn_old2.begin(), rnn_old2.end());
                rnn_old2.resize(R);
            }
            nn_old2.insert(nn_old2.end(), rnn_old2.begin(), rnn_old2.end());
            if(nn_old2.size() > R * 2){nn_old2.resize(R * 2);nn_old2.reserve(R*2);}
            std::vector<id_distance>().swap(graph_[i].rnn_new2);
            std::vector<id_distance>().swap(graph_[i].rnn_old2);
        }
    }


void IndexGraph::NNDescent(const Parameters &parameters) {
  unsigned iter = parameters.Get<unsigned>("iter");
  std::mt19937 rng(rand());
//  std::vector<unsigned> control_points(_CONTROL_NUM);
//  std::vector<std::vector<unsigned> > acc_eval_set(_CONTROL_NUM);
//  GenRandom(rng, &control_points[0], control_points.size(), nd_);
//  generate_control_set(control_points, acc_eval_set, nd_);
  for (unsigned it = 0; it < iter; it++) {
      update(parameters);
    join();

    //checkDup();
//    eval_recall(control_points, acc_eval_set);
    std::cout << "iter: " << it << std::endl;fflush(stdout);
      printf("compare_times:%lld\n",compare_times);
  }
}

    void IndexGraph::NNDescent11(const Parameters &parameters,std::vector<vector<unsigned >> &rank) {
        unsigned iter = parameters.Get<unsigned>("iter");
        std::mt19937 rng(rand());;
        for (unsigned it = 0; it < iter; it++) {
            update(parameters);
            join11(rank);

            std::cout << "iter: " << it << std::endl;
            printf("compare_times:%lld\n",compare_times);
        }
    }

    void IndexGraph::NNDescent12(const Parameters &parameters) {
        unsigned iter = parameters.Get<unsigned>("iter");
        std::mt19937 rng(rand());
        for (unsigned it = 0; it < iter; it++) {
            update12(parameters);
            join12();
            join12_2();

            std::cout << "iter: " << it << std::endl;
            printf("compare_times:%lld\n",compare_times);
        }
    }

    void IndexGraph::NNDescent13(const Parameters &parameters) {
        unsigned iter = parameters.Get<unsigned>("iter");
        std::mt19937 rng(rand());
        for (unsigned it = 0; it < iter; it++) {
            update12(parameters);
            join13();

            std::cout << "iter: " << it << std::endl;
            printf("compare_times:%lld\n",compare_times);
        }
    }

    void IndexGraph::NNDescent14(const Parameters &parameters) {
        unsigned iter = parameters.Get<unsigned>("iter");
        std::mt19937 rng(rand());
        for (unsigned it = 0; it < iter; it++) {
            update(parameters);
            join14();

            std::cout << "iter: " << it << std::endl;
            printf("compare_times:%lld\n",compare_times);
        }
    }

    void IndexGraph::NNDescent5(const Parameters &parameters, std:: vector<float > &p_square, std::vector<float> &p_right_size) {
      unsigned iter = parameters.Get<unsigned>("iter");
      std::mt19937 rng(rand());
      for (unsigned it = 0; it < iter; it++) {
        join5(p_square,p_right_size);
        update3(parameters,p_square);
        std::cout << "iter: " << it << std::endl;
          printf("compare_times:%lld\n",compare_times);
      }
    }

    void IndexGraph::NNDescent4_purn(const Parameters &parameters, std:: vector<float > &p_square, std::vector<float> &p_size) {
      unsigned iter = parameters.Get<unsigned>("iter");
      std::mt19937 rng(rand());
      for (unsigned it = 0; it < iter; it++) {
        join4_purn(p_square,p_size);
        update3(parameters,p_square);
        std::cout << "iter: " << it << std::endl;
          printf("compare_times:%lld\n",compare_times);
      }
    }

    void IndexGraph::NNDescent4_p(const Parameters &parameters, std:: vector<float > &p_square, std::vector<float> &p_size) {
      unsigned iter = parameters.Get<unsigned>("iter");
      std::mt19937 rng(rand());
      for (unsigned it = 0; it < iter; it++) {
        join4_p(p_square,p_size);
        update3(parameters,p_square);
        std::cout << "iter: " << it << std::endl;
          printf("compare_times:%lld\n",compare_times);
      }
    }

    void IndexGraph::NNDescent3(const Parameters &parameters, std:: vector<float > &p_square) {
      unsigned iter = parameters.Get<unsigned>("iter");
      std::mt19937 rng(rand());
//  std::vector<unsigned> control_points(_CONTROL_NUM);
//  std::vector<std::vector<unsigned> > acc_eval_set(_CONTROL_NUM);
//  GenRandom(rng, &control_points[0], control_points.size(), nd_);
//  generate_control_set(control_points, acc_eval_set, nd_);
      for (unsigned it = 0; it < iter; it++) {
        join3(p_square);
        update3(parameters,p_square);
        //checkDup();
//    eval_recall(control_points, acc_eval_set);
        std::cout << "iter: " << it << std::endl;
          printf("compare_times:%lld\n",compare_times);
      }
    }

void IndexGraph::generate_control_set(std::vector<unsigned> &c,
                                      std::vector<std::vector<unsigned> > &v,
                                      unsigned N){
#pragma omp parallel for
  for(unsigned i=0; i<c.size(); i++){
    std::vector<Neighbor> tmp;
    for(unsigned j=0; j<N; j++){
      float dist = distance_->compare(data_ + c[i] * dimension_, data_ + j * dimension_, dimension_);
      tmp.push_back(Neighbor(j, dist, true));
    }
    std::partial_sort(tmp.begin(), tmp.begin() + _CONTROL_NUM, tmp.end());
    for(unsigned j=0; j<_CONTROL_NUM; j++){
      v[i].push_back(tmp[j].id);
    }
  }
}

void IndexGraph::eval_recall(std::vector<unsigned>& ctrl_points, std::vector<std::vector<unsigned> > &acc_eval_set){
  float mean_acc=0;
  for(unsigned i=0; i<ctrl_points.size(); i++){
    float acc = 0;
    auto &g = graph_[ctrl_points[i]].pool;
    auto &v = acc_eval_set[i];
    for(unsigned j=0; j<g.size(); j++){
      for(unsigned k=0; k<v.size(); k++){
        if(g[j].id == v[k]){
          acc++;
          break;
        }
      }
    }
    mean_acc += acc / v.size();
  }
  std::cout<<"recall : "<<mean_acc / ctrl_points.size() <<std::endl;
}


void IndexGraph::InitializeGraph(const Parameters &parameters) {

  const unsigned L = parameters.Get<unsigned>("L");
  const unsigned S = parameters.Get<unsigned>("S");

  graph_.reserve(nd_);
  std::mt19937 rng(rand());
  for (unsigned i = 0; i < nd_; i++) {
    graph_.push_back(nhood(L, S, rng, (unsigned) nd_));
  }
#pragma omp parallel for
  for (unsigned i = 0; i < nd_; i++) {
    const float *query = data_ + i * dimension_;
    std::vector<unsigned> tmp(S + 1);
    initializer_->Search(query, data_, S + 1, parameters, tmp.data());

    for (unsigned j = 0; j < S; j++) {
      unsigned id = tmp[j];
      if (id == i)continue;
      float dist = distance_->compare(data_ + i * dimension_, data_ + id * dimension_, (unsigned) dimension_);

      graph_[i].pool.push_back(Neighbor(id, dist, true));
    }
    std::make_heap(graph_[i].pool.begin(), graph_[i].pool.end());
    graph_[i].pool.reserve(L);
  }
}

void IndexGraph::InitializeGraph_Refine(const Parameters &parameters) {
  assert(final_graph_.size() == nd_);

  const unsigned L = parameters.Get<unsigned>("L");
  const unsigned S = parameters.Get<unsigned>("S");

  graph_.reserve(nd_);
  std::mt19937 rng(rand());
  for (unsigned i = 0; i < nd_; i++) {
    graph_.push_back(nhood(L, S, rng, (unsigned) nd_));
  }
#pragma omp parallel for
  for (unsigned i = 0; i < nd_; i++) {
    auto& ids = final_graph_[i];
    std::sort(ids.begin(), ids.end());

    size_t K = ids.size();

    for (unsigned j = 0; j < K; j++) {
      unsigned id = ids[j];
      if (id == i || (j>0 &&id == ids[j-1]))continue;
      float dist = distance_->compare(data_ + i * dimension_, data_ + id * dimension_, (unsigned) dimension_);
      graph_[i].pool.push_back(Neighbor(id, dist, true));
    }
    std::make_heap(graph_[i].pool.begin(), graph_[i].pool.end());
    graph_[i].pool.reserve(L);
    std::vector<unsigned>().swap(ids);
  }
  CompactGraph().swap(final_graph_);
}

    void IndexGraph::InitializeGraph_Refine3(const Parameters &parameters, std::vector<float> &p_square) {
      assert(final_graph_.size() == nd_);

      const unsigned L = parameters.Get<unsigned>("L");
      const unsigned S = parameters.Get<unsigned>("S");

      graph_.reserve(nd_);
      std::mt19937 rng(rand());
      for (unsigned i = 0; i < nd_; i++) {
        graph_.push_back(nhood(L, S, rng, (unsigned) nd_));
      }
#pragma omp parallel for
      for (unsigned i = 0; i < nd_; i++) {//每个点i
        auto& ids = final_graph_[i];
        std::sort(ids.begin(), ids.end());

        size_t K = ids.size();

        for (unsigned j = 0; j < K; j++) {//每个点的邻居id
          unsigned id = ids[j];
          if (id == i || (j>0 &&id == ids[j-1]))continue;
          float dist = 2*distance_->compare(data_ + i * dimension_, data_ + id * dimension_, (unsigned) dimension_)-p_square[id];
          graph_[i].pool.push_back(Neighbor(id, dist, true));
        }
        std::make_heap(graph_[i].pool.begin(), graph_[i].pool.end(),greater<Neighbor>());
        graph_[i].pool.reserve(L);
        std::vector<unsigned>().swap(ids);
      }
      CompactGraph().swap(final_graph_);
    }

void IndexGraph::RefineGraph(const float* data, const Parameters &parameters) {
  data_ = data;
  assert(initializer_->HasBuilt());
  InitializeGraph_Refine(parameters);
  NNDescent(parameters);

  final_graph_.reserve(nd_);
  std::cout << nd_ << std::endl;
  unsigned K = parameters.Get<unsigned>("K");
  for (unsigned i = 0; i < nd_; i++) {
    std::vector<unsigned> tmp;
    std::sort(graph_[i].pool.begin(), graph_[i].pool.end());
    for (unsigned j = 0; j < K; j++) {
      tmp.push_back(graph_[i].pool[j].id);
    }
    tmp.reserve(K);
    final_graph_.push_back(tmp);
    std::vector<Neighbor>().swap(graph_[i].pool);
    std::vector<unsigned>().swap(graph_[i].nn_new);
    std::vector<unsigned>().swap(graph_[i].nn_old);
    std::vector<unsigned>().swap(graph_[i].rnn_new);
    std::vector<unsigned>().swap(graph_[i].rnn_new);
  }
  std::vector<nhood>().swap(graph_);
  has_built = true;

}

    void IndexGraph::RefineGraph11(const float* data, const Parameters &parameters,std::vector<vector<unsigned >> &rank) {
        data_ = data;
        assert(initializer_->HasBuilt());

        InitializeGraph_Refine(parameters);
        NNDescent11(parameters,rank);

        final_graph_.reserve(nd_);
        std::cout << nd_ << std::endl;
        unsigned K = parameters.Get<unsigned>("K");
        for (unsigned i = 0; i < nd_; i++) {
            std::vector<unsigned> tmp;
            std::sort(graph_[i].pool.begin(), graph_[i].pool.end());
            for (unsigned j = 0; j < K; j++) {
                tmp.push_back(graph_[i].pool[j].id);
            }
            tmp.reserve(K);
            final_graph_.push_back(tmp);
            std::vector<Neighbor>().swap(graph_[i].pool);
            std::vector<unsigned>().swap(graph_[i].nn_new);
            std::vector<unsigned>().swap(graph_[i].nn_old);
            std::vector<unsigned>().swap(graph_[i].rnn_new);
            std::vector<unsigned>().swap(graph_[i].rnn_new);
        }
        std::vector<nhood>().swap(graph_);
        has_built = true;

    }

    void IndexGraph::RefineGraph12(const float* data, const Parameters &parameters) {
        data_ = data;
        assert(initializer_->HasBuilt());

        InitializeGraph_Refine(parameters);

#ifdef linux
        ProfilerStart("nndescent");
#endif
        NNDescent12(parameters);

#ifdef linux
        ProfilerStop();
#endif

        final_graph_.reserve(nd_);
        std::cout << nd_ << std::endl;
        unsigned K = parameters.Get<unsigned>("K");
        for (unsigned i = 0; i < nd_; i++) {
            std::vector<unsigned> tmp;
            std::sort(graph_[i].pool.begin(), graph_[i].pool.end());
            for (unsigned j = 0; j < K; j++) {
                tmp.push_back(graph_[i].pool[j].id);
            }
            tmp.reserve(K);
            final_graph_.push_back(tmp);
            std::vector<Neighbor>().swap(graph_[i].pool);
           // std::set<id_lowbound>().swap(graph_[i].pool_lb);
            std::vector<id_distance>().swap(graph_[i].nn_new2);
            std::vector<id_distance>().swap(graph_[i].nn_old2);
            std::vector<id_distance>().swap(graph_[i].rnn_new2);
            std::vector<id_distance>().swap(graph_[i].rnn_new2);
        }
        std::vector<nhood>().swap(graph_);
        has_built = true;

    }

    void IndexGraph::RefineGraph13(const float* data, const Parameters &parameters) {
        data_ = data;
        assert(initializer_->HasBuilt());

        InitializeGraph_Refine(parameters);
        NNDescent13(parameters);

        final_graph_.reserve(nd_);
        std::cout << nd_ << std::endl;
        unsigned K = parameters.Get<unsigned>("K");
        for (unsigned i = 0; i < nd_; i++) {
            std::vector<unsigned> tmp;
            std::sort(graph_[i].pool.begin(), graph_[i].pool.end());
            for (unsigned j = 0; j < K; j++) {
                tmp.push_back(graph_[i].pool[j].id);
            }
            tmp.reserve(K);
            final_graph_.push_back(tmp);
            std::vector<Neighbor>().swap(graph_[i].pool);
            // std::set<id_lowbound>().swap(graph_[i].pool_lb);
            std::vector<id_distance>().swap(graph_[i].nn_new2);
            std::vector<id_distance>().swap(graph_[i].nn_old2);
            std::vector<id_distance>().swap(graph_[i].rnn_new2);
            std::vector<id_distance>().swap(graph_[i].rnn_new2);
        }
        std::vector<nhood>().swap(graph_);
        has_built = true;

    }

    void IndexGraph::RefineGraph14(const float* data, const Parameters &parameters) {
        data_ = data;
        assert(initializer_->HasBuilt());
        InitializeGraph_Refine(parameters);
        NNDescent14(parameters);

        final_graph_.reserve(nd_);
        std::cout << nd_ << std::endl;
        unsigned K = parameters.Get<unsigned>("K");
        for (unsigned i = 0; i < nd_; i++) {
            std::vector<unsigned> tmp;
            std::sort(graph_[i].pool.begin(), graph_[i].pool.end());
            for (unsigned j = 0; j < K; j++) {
                tmp.push_back(graph_[i].pool[j].id);
            }
            tmp.reserve(K);
            final_graph_.push_back(tmp);
            std::vector<Neighbor>().swap(graph_[i].pool);
            std::vector<unsigned>().swap(graph_[i].nn_new);
            std::vector<unsigned>().swap(graph_[i].nn_old);
            std::vector<unsigned>().swap(graph_[i].rnn_new);
            std::vector<unsigned>().swap(graph_[i].rnn_new);
        }
        std::vector<nhood>().swap(graph_);
        has_built = true;

    }

    void IndexGraph::RefineGraph5(const float* data, const Parameters &parameters, std::vector<float> &p_square, std::vector<float> &p_right_size) {
      data_ = data;
      assert(initializer_->HasBuilt());
      div = parameters.Get<unsigned>("div");

      InitializeGraph_Refine3(parameters,p_square);
      NNDescent5(parameters,p_square,p_right_size);

      final_graph_.reserve(nd_);
      std::cout << nd_ << std::endl;
      unsigned K = parameters.Get<unsigned>("K");
      for (unsigned i = 0; i < nd_; i++) {
        std::vector<unsigned> tmp;
        std::sort(graph_[i].pool.begin(), graph_[i].pool.end(),greater<Neighbor>());
        for (unsigned j = 0; j < K; j++) {
          tmp.push_back(graph_[i].pool[j].id);
        }
        tmp.reserve(K);
        final_graph_.push_back(tmp);
        std::vector<Neighbor>().swap(graph_[i].pool);
        std::vector<unsigned>().swap(graph_[i].nn_new);
        std::vector<unsigned>().swap(graph_[i].nn_old);
        std::vector<unsigned>().swap(graph_[i].rnn_new);
        std::vector<unsigned>().swap(graph_[i].rnn_new);
      }
      std::vector<nhood>().swap(graph_);
      has_built = true;

    }

    void IndexGraph::RefineGraph4_purn(const float* data, const Parameters &parameters, std::vector<float> &p_square, std::vector<float> &p_size) {
      data_ = data;
      assert(initializer_->HasBuilt());

      InitializeGraph_Refine3(parameters,p_square);
      NNDescent4_purn(parameters,p_square,p_size);

      final_graph_.reserve(nd_);
      std::cout << nd_ << std::endl;
      unsigned K = parameters.Get<unsigned>("K");
      for (unsigned i = 0; i < nd_; i++) {
        std::vector<unsigned> tmp;
        std::sort(graph_[i].pool.begin(), graph_[i].pool.end(),greater<Neighbor>());
        for (unsigned j = 0; j < K; j++) {
          tmp.push_back(graph_[i].pool[j].id);
        }
        tmp.reserve(K);
        final_graph_.push_back(tmp);
        std::vector<Neighbor>().swap(graph_[i].pool);
        std::vector<unsigned>().swap(graph_[i].nn_new);
        std::vector<unsigned>().swap(graph_[i].nn_old);
        std::vector<unsigned>().swap(graph_[i].rnn_new);
        std::vector<unsigned>().swap(graph_[i].rnn_new);
      }
      std::vector<nhood>().swap(graph_);
      has_built = true;

    }

    void IndexGraph::RefineGraph4_p(const float* data, const Parameters &parameters, std::vector<float> &p_square, std::vector<float> &p_size) {
      data_ = data;
      assert(initializer_->HasBuilt());

      InitializeGraph_Refine3(parameters,p_square);
      NNDescent4_p(parameters,p_square,p_size);

      final_graph_.reserve(nd_);
      std::cout << nd_ << std::endl;
      unsigned K = parameters.Get<unsigned>("K");
      for (unsigned i = 0; i < nd_; i++) {
        std::vector<unsigned> tmp;
        std::sort(graph_[i].pool.begin(), graph_[i].pool.end(),greater<Neighbor>());
        for (unsigned j = 0; j < K; j++) {
          tmp.push_back(graph_[i].pool[j].id);
        }
        tmp.reserve(K);
        final_graph_.push_back(tmp);
        std::vector<Neighbor>().swap(graph_[i].pool);
        std::vector<unsigned>().swap(graph_[i].nn_new);
        std::vector<unsigned>().swap(graph_[i].nn_old);
        std::vector<unsigned>().swap(graph_[i].rnn_new);
        std::vector<unsigned>().swap(graph_[i].rnn_new);
      }
      std::vector<nhood>().swap(graph_);
      has_built = true;

    }

    void IndexGraph::RefineGraph3(const float* data, const Parameters &parameters, std::vector<float> &p_square) {
      data_ = data;
      assert(initializer_->HasBuilt());

      InitializeGraph_Refine3(parameters,p_square);
      NNDescent3(parameters,p_square);

      final_graph_.reserve(nd_);
      std::cout << nd_ << std::endl;
      unsigned K = parameters.Get<unsigned>("K");
      for (unsigned i = 0; i < nd_; i++) {
        std::vector<unsigned> tmp;
        std::sort(graph_[i].pool.begin(), graph_[i].pool.end(),greater<Neighbor>());
        for (unsigned j = 0; j < K; j++) {
          tmp.push_back(graph_[i].pool[j].id);
        }
        tmp.reserve(K);
        final_graph_.push_back(tmp);
        std::vector<Neighbor>().swap(graph_[i].pool);
        std::vector<unsigned>().swap(graph_[i].nn_new);
        std::vector<unsigned>().swap(graph_[i].nn_old);
        std::vector<unsigned>().swap(graph_[i].rnn_new);
        std::vector<unsigned>().swap(graph_[i].rnn_new);
      }
      std::vector<nhood>().swap(graph_);
      has_built = true;

    }

void IndexGraph::Build(size_t n, const float *data, const Parameters &parameters) {

  //assert(initializer_->GetDataset() == data);
  data_ = data;
  assert(initializer_->HasBuilt());

  InitializeGraph(parameters);
  NNDescent(parameters);
  //RefineGraph(parameters);

  final_graph_.reserve(nd_);
  std::cout << nd_ << std::endl;
  unsigned K = parameters.Get<unsigned>("K");
  for (unsigned i = 0; i < nd_; i++) {
    std::vector<unsigned> tmp;
    std::sort(graph_[i].pool.begin(), graph_[i].pool.end());
    for (unsigned j = 0; j < K; j++) {
      tmp.push_back(graph_[i].pool[j].id);
    }
    tmp.reserve(K);
    final_graph_.push_back(tmp);
    std::vector<Neighbor>().swap(graph_[i].pool);
    std::vector<unsigned>().swap(graph_[i].nn_new);
    std::vector<unsigned>().swap(graph_[i].nn_old);
    std::vector<unsigned>().swap(graph_[i].rnn_new);
    std::vector<unsigned>().swap(graph_[i].rnn_new);
  }
  std::vector<nhood>().swap(graph_);
  has_built = true;
}

void IndexGraph::Search(
    const float *query,
    const float *x,
    size_t K,
    const Parameters &parameter,
    unsigned *indices) {
  const unsigned L = parameter.Get<unsigned>("L_search");

  std::vector<Neighbor> retset(L+1);
  std::vector<unsigned> init_ids(L);
  std::mt19937 rng(rand());
  GenRandom(rng, init_ids.data(), L, (unsigned)nd_);

  std::vector<char> flags(nd_);
  memset(flags.data(), 0, nd_ * sizeof(char));
  for(unsigned i=0; i<L; i++){
    unsigned id = init_ids[i];
    float dist = distance_->compare(data_ + dimension_*id, query, (unsigned)dimension_);
    retset[i]=Neighbor(id, dist, true);
  }

  std::sort(retset.begin(), retset.begin()+L);
  int k=0;
  while(k < (int)L) {
    int nk = L;

    if (retset[k].flag) {
      retset[k].flag = false;
      unsigned n = retset[k].id;

      for (unsigned m = 0; m < final_graph_[n].size(); ++m) {
        unsigned id = final_graph_[n][m];
        if(flags[id])continue;
        flags[id] = 1;
        float dist = distance_->compare(query, data_ + dimension_ * id, (unsigned)dimension_);
        if(dist >= retset[L-1].distance)continue;
        Neighbor nn(id, dist, true);
        int r = InsertIntoPool(retset.data(), L, nn);

        //if(L+1 < retset.size()) ++L;
        if(r < nk)nk=r;
      }
      //lock to here
    }
    if(nk <= k)k = nk;
    else ++k;
  }
  for(size_t i=0; i < K; i++){
    indices[i] = retset[i].id;
  }
}

void IndexGraph::Save(const char *filename) {
  std::ofstream out(filename, std::ios::binary | std::ios::out);
  assert(final_graph_.size() == nd_);
  unsigned GK = (unsigned) final_graph_[0].size();
  for (unsigned i = 0; i < nd_; i++) {
    out.write((char *) &GK, sizeof(unsigned));
    out.write((char *) final_graph_[i].data(), GK * sizeof(unsigned));
  }
  out.close();
}

void IndexGraph::Load(const char *filename) {
  std::ifstream in(filename, std::ios::binary);
  unsigned k;
  in.read((char*)&k,4);
  in.seekg(0,std::ios::end);
  std::ios::pos_type ss = in.tellg();
  size_t fsize = (size_t)ss;
  size_t num = fsize / ((size_t)k + 1) / 4;
  in.seekg(0,std::ios::beg);

  final_graph_.resize(num);
  for(size_t i = 0; i < num; i++){
    in.seekg(4,std::ios::cur);
    final_graph_[i].resize(k);
    final_graph_[i].reserve(k);
    in.read((char*)final_graph_[i].data(), k * sizeof(unsigned));
  }
  in.close();
}

void IndexGraph::parallel_graph_insert(unsigned id, Neighbor nn, LockGraph& g, size_t K){
  LockGuard guard(g[id].lock);
  size_t l = g[id].pool.size();
  if(l == 0)g[id].pool.push_back(nn);
  else{
    g[id].pool.resize(l+1);
    g[id].pool.reserve(l+1);
    InsertIntoPool(g[id].pool.data(), (unsigned)l, nn);
    if(g[id].pool.size() > K)g[id].pool.reserve(K);
  }

}

void IndexGraph::GraphAdd(const float* data, unsigned n_new, unsigned dim, const Parameters &parameters) {
  data_ = data;
  data += nd_ * dimension_;
  assert(final_graph_.size() == nd_);
  assert(dim == dimension_);
  unsigned total = n_new + (unsigned)nd_;
  LockGraph graph_tmp(total);
  size_t K = final_graph_[0].size();
  compact_to_Lockgraph(graph_tmp);
  unsigned seed = 19930808;
#pragma omp parallel
  {
    std::mt19937 rng(seed ^ omp_get_thread_num());
#pragma omp for
    for(unsigned i = 0; i < n_new; i++){
      std::vector<Neighbor> res;
      get_neighbor_to_add(data + i * dim, parameters, graph_tmp, rng, res, n_new);

      for(unsigned j=0; j<K; j++){
        parallel_graph_insert(i + (unsigned)nd_, res[j], graph_tmp, K);
        parallel_graph_insert(res[j].id, Neighbor(i + (unsigned)nd_, res[j].distance, true), graph_tmp, K);
      }

    }
  };


  std::cout<<"complete: "<<std::endl;
  nd_ = total;
  final_graph_.resize(total);
  for(unsigned i=0; i<total; i++){
    for(unsigned m=0; m<K; m++){
      final_graph_[i].push_back(graph_tmp[i].pool[m].id);
    }
  }

}

void IndexGraph::get_neighbor_to_add(const float* point,
                                     const Parameters &parameters,
                                     LockGraph& g,
                                     std::mt19937& rng,
                                     std::vector<Neighbor>& retset,
                                     unsigned n_new){
  const unsigned L = parameters.Get<unsigned>("L_ADD");

  retset.resize(L+1);
  std::vector<unsigned> init_ids(L);
  GenRandom(rng, init_ids.data(), L/2, n_new);
  for(unsigned i=0; i<L/2; i++)init_ids[i] += nd_;

  GenRandom(rng, init_ids.data() + L/2, L - L/2, (unsigned)nd_);

  unsigned n_total = (unsigned)nd_ + n_new;
  std::vector<char> flags(n_new + n_total);
  memset(flags.data(), 0, n_total * sizeof(char));
  for(unsigned i=0; i<L; i++){
    unsigned id = init_ids[i];
    float dist = distance_->compare(data_ + dimension_*id, point, (unsigned)dimension_);
    retset[i]=Neighbor(id, dist, true);
  }

  std::sort(retset.begin(), retset.begin()+L);
  int k=0;
  while(k < (int)L) {
    int nk = L;

    if (retset[k].flag) {
      retset[k].flag = false;
      unsigned n = retset[k].id;

      LockGuard guard(g[n].lock);//lock start
      for (unsigned m = 0; m < g[n].pool.size(); ++m) {
        unsigned id = g[n].pool[m].id;
        if(flags[id])continue;
        flags[id] = 1;
        float dist = distance_->compare(point, data_ + dimension_ * id, (unsigned)dimension_);
        if(dist >= retset[L-1].distance)continue;
        Neighbor nn(id, dist, true);
        int r = InsertIntoPool(retset.data(), L, nn);

        //if(L+1 < retset.size()) ++L;
        if(r < nk)nk=r;
      }
      //lock to here
    }
    if(nk <= k)k = nk;
    else ++k;
  }


}

void IndexGraph::compact_to_Lockgraph(LockGraph &g){

  //g.resize(final_graph_.size());
  for(unsigned i=0; i<final_graph_.size(); i++){
    g[i].pool.reserve(final_graph_[i].size()+1);
    for(unsigned j=0; j<final_graph_[i].size(); j++){
      float dist = distance_->compare(data_ + i*dimension_,
                                      data_ + final_graph_[i][j]*dimension_, (unsigned)dimension_);
      g[i].pool.push_back(Neighbor(final_graph_[i][j], dist, true));
    }
    std::vector<unsigned>().swap(final_graph_[i]);
  }
  CompactGraph().swap(final_graph_);
}


}
